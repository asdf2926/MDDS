#include "includes.h"
#if HSPI_EN>0
extern SPI_HandleTypeDef HSPI_INTERFACE;
#endif
extern RTC_HandleTypeDef RTC_INTERFACE;
extern TIM_HandleTypeDef TIM_INTERFACE;
void AdapterInit()
{
//	hspi_handler=hspi;
	#ifdef STM32F7
		SCB->CACR|=1<<2;   //强制D-Cache透写,如不开启,实际使用中可能遇到各种问题	
	#endif
	#ifdef TIM_INTERFACE
	__HAL_TIM_MOE_ENABLE(&TIM_INTERFACE);
	#endif
	DriverInit();
	
	MiddlewareInit();
	
}
void AdapterDeInit()
{
	DriverDeInit();
}
void GPIOWrite(GPIO_TypeDef* Group,INT16U data)
{
	Group->ODR=data;
}

void GPIOWritePin(GPIO_TypeDef* Group,INT16U PinMask,BL Statu)
{
	HAL_GPIO_WritePin(Group,PinMask, (GPIO_PinState)Statu);
}

INT16U GPIORead(GPIO_TypeDef* Group)
{
	return Group->IDR;
}

BL GPIOReadPin(GPIO_TypeDef* Group,INT16U PinMask)
{
	return HAL_GPIO_ReadPin(Group,PinMask);
	
}
void (*HSPICallBack)();
void HSPIWaitTransmit()
{
	//while(__HAL_SPI_GET_FLAG(&HSPI_INTERFACE, SPI_FLAG_TXE)==0);
}
//void HSPISetTxCallBack(void (*pFunc)())
//{
	
//}
#if HSPI_EN>0

void HSPIWriteByte(INT8U dat)
{
	//HSPI_INTERFACE.Instance->DR=dat;
	while(HAL_SPI_Transmit(&HSPI_INTERFACE,&dat,1,HAL_MAX_DELAY)==HAL_BUSY);
}

void HSPISetCallBack(void (*pCallBack)())
{
	HSPICallBack=pCallBack;
}
void HSPIWriteBlock_DMA(const INT8U *dat,INT16U Len)
{
	HAL_SPI_Transmit_DMA(&HSPI_INTERFACE,(INT8U *)dat,Len);
}
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if(HSPICallBack)(*HSPICallBack)();
}
#endif
void IdleProcess()
{
#if BTIMER_COUNT>0
    BasicTimerProcess();
#endif
#if APPE_EN>0
    AppEPendSolve();
	
#endif
}

#if 0
INT8S pBasicTimer;
s_BasicTimer BasicTimer[BTIMER_COUNT];
//???
void BasicTimerInit()
{
    for(pBasicTimer=BTIMER_COUNT-1;pBasicTimer>=0;pBasicTimer--)
    {
        BasicTimer[pBasicTimer].CallBack=0;
    }
    pBasicTimer=0;
}
//???????
//??:
//  INT32U TimeUS:??(礢)
//  BL SingleShot:??
//  void (*pCallBack)():????
//??:
//  INT8S:????,-1????
    #if BT_EXT_CALLBACK>0
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)(INT8U index))
    #else
INT8S BasicTimerAdd(INT32U TimeUS,BL SingleShot,void (*pCallBack)())
    #endif
{
    INT8U i;
    for(i=0;i<BTIMER_COUNT;i++)
        if(BasicTimer[i].CallBack==0)
			{
					BasicTimer[i].CallBack=pCallBack;
					BasicTimer[i].CurTime=BasicTimer[i].TimeTick=TimeUS/1000;
					BasicTimer[i].CallCount=-SingleShot;
					return i;
			}
    return -1;
}
//???????
//??:
//  INT8U index:??

void BasicTimerDel(INT8U index)
{
	BasicTimer[index].CallBack=0;
}

void BasicTimerTick()
{
    INT8U i;
    for(i=0;i<BTIMER_COUNT;i++)
    {
        if(BasicTimer[i].CallBack)
        {
            if(BasicTimer[i].CurTime==0)continue;
            BasicTimer[i].CurTime-=1;
            if(BasicTimer[i].CurTime)continue;
            //(*BasicTimer[i].CallBack)();
            //if(BasicTimer[i].CallCount==-1)BasicTimer[i].CallBack=0;
            if(BasicTimer[i].CallCount!=-1)
            {
                BasicTimer[i].CurTime=BasicTimer[i].TimeTick;
				if(BasicTimer[i].CallCount!=-2)
					BasicTimer[i].CallCount++;
            }


        }
    }
}
#endif
#ifdef STM32F1

/**
  * @brief  Read the time counter available in RTC_CNT registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval Time counter
  */
static uint32_t RTC_ReadTimeCounter(RTC_HandleTypeDef* hrtc)
{
  uint16_t high1 = 0U, high2 = 0U, low = 0U;
  uint32_t timecounter = 0U;

  high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
  low   = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
  high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);

  if (high1 != high2)
  { /* In this case the counter roll over during reading of CNTL and CNTH registers, 
       read again CNTL register then return the counter value */
    timecounter = (((uint32_t) high2 << 16U) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
  }
  else
  { /* No counter roll over during reading of CNTL and CNTH registers, counter 
       value is equal to first value of CNTL and CNTH */
    timecounter = (((uint32_t) high1 << 16U) | low);
  }

  return timecounter;
}
#endif
Time RTCTimeRGet(void)
{
	#ifdef STM32F1
	return ConventTimestampToTime((UTime)RTC_ReadTimeCounter(&RTC_INTERFACE)*1000);
	#else
	RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;
  Time t;
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RTC_INTERFACE, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RTC_INTERFACE, &sdatestructureget, RTC_FORMAT_BIN);
	#ifdef STM32F0
	t.MSec=(499-stimestructureget.SubSeconds)<<1;
	#else
	t.MSec=0;
	#endif
	t.Sec=stimestructureget.Seconds;
	t.Min=stimestructureget.Minutes;
	t.Hour=stimestructureget.Hours;
	t.Day=sdatestructureget.WeekDay%7;
	t.Date=sdatestructureget.Date;
	t.Month=sdatestructureget.Month;
	t.Year=sdatestructureget.Year+2000;
	return t;
	#endif
}
/**
  * @brief  Enters the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
#ifdef STM32F1

static HAL_StatusTypeDef RTC_EnterInitMode(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0U;
  
  tickstart = HAL_GetTick();
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
    } 
  }

  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);
  
  
  return HAL_OK;  
}
/**
  * @brief  Exit the RTC Initialization mode.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_ExitInitMode(RTC_HandleTypeDef* hrtc)
{
  uint32_t tickstart = 0U;
  
  /* Disable the write protection for RTC registers */
  __HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  
  tickstart = HAL_GetTick();
  /* Wait till RTC is in INIT state and if Time out is reached exit */
  while((hrtc->Instance->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET)
  {
    if((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
    {       
      return HAL_TIMEOUT;
    } 
  }
  
  return HAL_OK;  
}

/**
  * @brief  Write the time counter in RTC_CNT registers.
  * @param  hrtc   pointer to a RTC_HandleTypeDef structure that contains
  *                the configuration information for RTC.
  * @param  TimeCounter: Counter to write in RTC_CNT registers
  * @retval HAL status
  */
static HAL_StatusTypeDef RTC_WriteTimeCounter(RTC_HandleTypeDef* hrtc, uint32_t TimeCounter)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  /* Set Initialization mode */
  if(RTC_EnterInitMode(hrtc) != HAL_OK)
  {
    status = HAL_ERROR;
  } 
  else
  {
    /* Set RTC COUNTER MSB word */
    WRITE_REG(hrtc->Instance->CNTH, (TimeCounter >> 16U));
    /* Set RTC COUNTER LSB word */
    WRITE_REG(hrtc->Instance->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));
    
    /* Wait for synchro */
    if(RTC_ExitInitMode(hrtc) != HAL_OK)
    {       
      status = HAL_ERROR;
    }
  }

  return status;
}
#endif
#define __HAL_LOCK_M(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while (0U)

void RTCTimeRSet(Time t)
{
	#ifdef STM32F1
	assert_param(IS_RTC_FORMAT(Format));
	  __HAL_LOCK_M(&RTC_INTERFACE);
	//hrtc->State = HAL_RTC_STATE_BUSY;
  if (RTC_WriteTimeCounter(&RTC_INTERFACE, ConventTimeToTimestamp(t)/1000) != HAL_OK)
  {
    /* Set RTC state */
    RTC_INTERFACE.State = HAL_RTC_STATE_ERROR; 
    /* Process Unlocked */ 
    __HAL_UNLOCK(&RTC_INTERFACE);
    return;
  }
  else
  {
    /* Clear Second and overflow flags */
    CLEAR_BIT(RTC_INTERFACE.Instance->CRL, (RTC_FLAG_SEC | RTC_FLAG_OW));   
    RTC_INTERFACE.State = HAL_RTC_STATE_READY;  
   __HAL_UNLOCK(&RTC_INTERFACE); 
  }
	#else
	RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;
	stimestructureget.Seconds=t.Sec;
	stimestructureget.Minutes=t.Min;
	stimestructureget.Hours=t.Hour;
	sdatestructureget.WeekDay=t.Day?t.Day:7;
	sdatestructureget.Date=t.Date;
	sdatestructureget.Month=t.Month;
	sdatestructureget.Year=t.Year%100;	
  HAL_RTC_SetTime(&RTC_INTERFACE, &stimestructureget, RTC_FORMAT_BIN);
  HAL_RTC_SetDate(&RTC_INTERFACE, &sdatestructureget, RTC_FORMAT_BIN);
	#endif
}
#ifdef STM32F0
#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
#define VREFINT_CAL ((uint16_t*) ((uint32_t) 0x1FFFF7BA))
#define VDD_CALIB ((uint16_t) (330))
#else
#ifdef STM32F7
#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FF0F44E))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FF0F44C))
#define VREFINT_CAL ((uint16_t*) ((uint32_t) 0x1FF0F44A))

#endif
#endif
//
INT16U GetTemp(INT16U vtemp)
{
//	u32 adcx;
	INT16U result;
 	double temperate;
	temperate=(float)vtemp*(3.3/4096);		//电压值
	temperate=(temperate-0.76)/0.0025 + 25; //转换为温度值 
	result=temperate*=100;					//扩大100倍.
	return result;
}

