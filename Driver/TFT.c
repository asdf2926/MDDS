#include "includes.h"
#if TFT_EN>0				 
//TFT的画笔颜色和背景色	   
INT16U POINT_COLOR=0x0000;	//画笔颜色
INT16U BACK_COLOR=0xFFFF;  //背景色 

//管理TFT重要参数
//默认为竖屏
_TFT_dev TFTdev;
	
		   
//写寄存器函数
//regval:寄存器值
void TFT_WR_REG(INT16U regval)
{ 
	TFT->TFT_REG=regval;//写入要写的寄存器序号	 
}
//写TFT数据
//data:要写入的值
void TFT_WR_DATA(INT16U data)
{										    	   
	TFT->TFT_RAM=data;		 
}
//读TFT数据
//返回值:读到的值
INT16U TFT_RD_DATA(void)
{										    	   
	return TFT->TFT_RAM;		 
}					   
//写寄存器
//TFT_Reg:寄存器地址
//TFT_RegValue:要写入的数据
void TFT_WriteReg(INT8U TFT_Reg, INT16U TFT_RegValue)
{	
	TFT->TFT_REG = TFT_Reg;		//写入要写的寄存器序号	 
	TFT->TFT_RAM = TFT_RegValue;//写入数据	    		 
}	   
//读寄存器
//TFT_Reg:寄存器地址
//返回值:读到的数据
INT16U TFT_ReadReg(INT8U TFT_Reg)
{										   
	TFT_WR_REG(TFT_Reg);		//写入要读的寄存器序号
	HAL_Delay(1);		  
	return TFT_RD_DATA();		//返回读到的值
}   
//开始写GRAM
void TFT_WriteRAM_Prepare(void)
{
 	TFT->TFT_REG=TFTdev.wramcmd;	  
}	 
//TFT写GRAM
//RGB_Code:颜色值
void TFT_WriteRAM(INT16U RGB_Code)
{							    
	TFT->TFT_RAM = RGB_Code;//写十六位GRAM
}
//从ILI93xx读出的数据为GBR格式，而我们写入的时候为RGB格式。
//通过该函数转换
//c:GBR格式的颜色值
//返回值：RGB格式的颜色值
INT16U TFT_BGR2RGB(INT16U c)
{
	INT16U  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//当mdk -O1时间优化时需要设置
//延时i
void opt_delay(INT8U i)
{
	while(i--);
}
//读取个某点的颜色值	 
//x,y:坐标
//返回值:此点的颜色
INT16U TFT_ReadPoint(INT16U x,INT16U y)
{
 	INT16U r=0,g=0,b=0;
	if(x>=TFTdev.width||y>=TFTdev.height)return 0;	//超过了范围,直接返回		   
	TFT_SetCursor(x,y);	    
	if(TFTdev.id==0X9341||TFTdev.id==0X6804)TFT_WR_REG(0X2E);//9341/6804 发送读GRAM指令
	else TFT_WR_REG(R34);      		 				//其他IC发送读GRAM指令
 	if(TFTdev.id==0X9320)opt_delay(2);				//FOR 9320,延时2us	    
	if(TFT->TFT_RAM)r=0;							//dummy Read	   
	opt_delay(2);	  
 	r=TFT->TFT_RAM;  		  						//实际坐标颜色
 	if(TFTdev.id==0X9341)//9341要分2次读出
 	{
		opt_delay(2);	  
		b=TFT->TFT_RAM; 
		g=r&0XFF;//对于9341,第一次读取的是RG的值,R在前,G在后,各占8位
		g<<=8;
	}else if(TFTdev.id==0X6804)r=TFT->TFT_RAM;//6804第二次读取的才是真实值
	if(TFTdev.id==0X9325||TFTdev.id==0X4535||TFTdev.id==0X4531||TFTdev.id==0X8989||TFTdev.id==0XB505)return r;//这几种IC直接返回颜色值
	else if(TFTdev.id==0X9341)return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));	//ILI9341需要公式转换一下
	else return TFT_BGR2RGB(r);												//其他IC
}			 
//TFT开启显示
void TFT_DisplayOn(void)
{					   
	if(TFTdev.id==0X9341||TFTdev.id==0X6804)TFT_WR_REG(0X29);	//开启显示
	else TFT_WriteReg(R7,0x0173); 			//开启显示
}	 
//TFT关闭显示
void TFT_DisplayOff(void)
{	   
	if(TFTdev.id==0X9341||TFTdev.id==0X6804)TFT_WR_REG(0X28);	//关闭显示
	else TFT_WriteReg(R7,0x0);//关闭显示 
}   
//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void TFT_SetCursor(INT16U Xpos, INT16U Ypos)
{	 
 	if(TFTdev.id==0X9341||TFTdev.id==0X6804)
	{		    
		TFT_WR_REG(TFTdev.setxcmd); 
		TFT_WR_DATA(Xpos>>8); 
		TFT_WR_DATA(Xpos&0XFF);	 
		TFT_WR_REG(TFTdev.setycmd); 
		TFT_WR_DATA(Ypos>>8); 
		TFT_WR_DATA(Ypos&0XFF);
	}else
	{
		if(TFTdev.dir==1)Xpos=TFTdev.width-1-Xpos;//横屏其实就是调转x,y坐标
		TFT_WriteReg(TFTdev.setxcmd, Xpos);
		TFT_WriteReg(TFTdev.setycmd, Ypos);
	}	 
} 		 
//设置TFT的自动扫描方向
//注意:其他函数可能会受到此函数设置的影响(尤其是9341/6804这两个奇葩),
//所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
//dir:0~7,代表8个方向(具体定义见TFT.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341等IC已经实际测试	   	   
void TFT_Scan_Dir(INT8U dir)
{
	INT16U regval=0;
	INT8U dirreg=0;
	INT16U temp;  
	if(TFTdev.dir==1&&TFTdev.id!=0X6804)//横屏时，对6804不改变扫描方向！
	{			   
		switch(dir)//方向转换
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	}
	if(TFTdev.id==0x9341||TFTdev.id==0X6804)//9341/6804,很特殊
	{
		switch(dir)
		{
			case L2R_U2D://从左到右,从上到下
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://从左到右,从下到上
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://从右到左,从上到下
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://从右到左,从下到上
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://从上到下,从左到右
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://从上到下,从右到左
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://从下到上,从左到右
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://从下到上,从右到左
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		dirreg=0X36;
 		regval|=0X08;//BGR   
		if(TFTdev.id==0X6804)regval|=0x02;//6804的BIT6和9341的反了	   
		TFT_WriteReg(dirreg,regval);
 		if(regval&0X20)
		{
			if(TFTdev.width<TFTdev.height)//交换X,Y
			{
				temp=TFTdev.width;
				TFTdev.width=TFTdev.height;
				TFTdev.height=temp;
 			}
		}else  
		{
			if(TFTdev.width>TFTdev.height)//交换X,Y
			{
				temp=TFTdev.width;
				TFTdev.width=TFTdev.height;
				TFTdev.height=temp;
 			}
		}  
		TFT_WR_REG(TFTdev.setxcmd); 
		TFT_WR_DATA(0);TFT_WR_DATA(0);
		TFT_WR_DATA((TFTdev.width-1)>>8);TFT_WR_DATA((TFTdev.width-1)&0XFF);
		TFT_WR_REG(TFTdev.setycmd); 
		TFT_WR_DATA(0);TFT_WR_DATA(0);
		TFT_WR_DATA((TFTdev.height-1)>>8);TFT_WR_DATA((TFTdev.height-1)&0XFF);  
  	}else 
	{
		switch(dir)
		{
			case L2R_U2D://从左到右,从上到下
				regval|=(1<<5)|(1<<4)|(0<<3); 
				break;
			case L2R_D2U://从左到右,从下到上
				regval|=(0<<5)|(1<<4)|(0<<3); 
				break;
			case R2L_U2D://从右到左,从上到下
				regval|=(1<<5)|(0<<4)|(0<<3);
				break;
			case R2L_D2U://从右到左,从下到上
				regval|=(0<<5)|(0<<4)|(0<<3); 
				break;	 
			case U2D_L2R://从上到下,从左到右
				regval|=(1<<5)|(1<<4)|(1<<3); 
				break;
			case U2D_R2L://从上到下,从右到左
				regval|=(1<<5)|(0<<4)|(1<<3); 
				break;
			case D2U_L2R://从下到上,从左到右
				regval|=(0<<5)|(1<<4)|(1<<3); 
				break;
			case D2U_R2L://从下到上,从右到左
				regval|=(0<<5)|(0<<4)|(1<<3); 
				break;	 
		}
		if(TFTdev.id==0x8989)//8989 IC
		{
			dirreg=0X11;
			regval|=0X6040;	//65K   
	 	}else//其他驱动IC		  
		{
			dirreg=0X03;
			regval|=1<<12;  
		}
		TFT_WriteReg(dirreg,regval);
	}
}   
//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void TFT_DrawPoint(INT16U x,INT16U y)
{
	TFT_SetCursor(x,y);		//设置光标位置 
	TFT_WriteRAM_Prepare();	//开始写入GRAM
	TFT->TFT_RAM=POINT_COLOR; 
}
//快速画点
//x,y:坐标
//color:颜色
void TFT_Fast_DrawPoint(INT16U x,INT16U y,INT16U color)
{	   
	if(TFTdev.id==0X9341||TFTdev.id==0X6804)
	{		    
		TFT_WR_REG(TFTdev.setxcmd); 
		TFT_WR_DATA(x>>8); 
		TFT_WR_DATA(x&0XFF);	 
		TFT_WR_REG(TFTdev.setycmd); 
		TFT_WR_DATA(y>>8); 
		TFT_WR_DATA(y&0XFF);
	}else
	{
 		if(TFTdev.dir==1)x=TFTdev.width-1-x;//横屏其实就是调转x,y坐标
		TFT_WriteReg(TFTdev.setxcmd,x);
		TFT_WriteReg(TFTdev.setycmd,y);
	}			 
	TFT->TFT_REG=TFTdev.wramcmd; 
	TFT->TFT_RAM=color; 
}	 


//设置TFT显示方向（6804不支持横屏显示）
//dir:0,竖屏；1,横屏
void TFT_Display_Dir(INT8U dir)
{
	if(dir==0)//竖屏
	{
		TFTdev.dir=0;//竖屏
		TFTdev.width=240;
		TFTdev.height=320;
		if(TFTdev.id==0X9341||TFTdev.id==0X6804)
		{
			TFTdev.wramcmd=0X2C;
	 		TFTdev.setxcmd=0X2A;
			TFTdev.setycmd=0X2B;  	 
			if(TFTdev.id==0X6804)
			{
				TFTdev.width=320;
				TFTdev.height=480;
			}
		}else if(TFTdev.id==0X8989)
		{
			TFTdev.wramcmd=R34;
	 		TFTdev.setxcmd=0X4E;
			TFTdev.setycmd=0X4F;  
		}else
		{
			TFTdev.wramcmd=R34;
	 		TFTdev.setxcmd=R32;
			TFTdev.setycmd=R33; 
			TFTdev.setxscmd=R80;
			TFTdev.setxecmd=R81;
			TFTdev.setyscmd=R82;
			TFTdev.setyecmd=R83;
		}
	}else if(TFTdev.id!=0X6804)//6804不支持横屏显示	
	{	  
		TFTdev.dir=1;//横屏
		TFTdev.width=320;
		TFTdev.height=240;
		if(TFTdev.id==0X9341)
		{
			TFTdev.wramcmd=0X2C;
	 		TFTdev.setxcmd=0X2A;
			TFTdev.setycmd=0X2B;  	 
		}else if(TFTdev.id==0X8989)
		{
			TFTdev.wramcmd=R34;
	 		TFTdev.setxcmd=0X4F;
			TFTdev.setycmd=0X4E;  
		}else
		{
			TFTdev.wramcmd=R34;
	 		TFTdev.setxcmd=R33;
			TFTdev.setycmd=R32;  
			TFTdev.setyscmd=R80;
			TFTdev.setyecmd=R81;
			TFTdev.setxscmd=R82;
			TFTdev.setxecmd=R83;
		}
	} 
	TFT_Scan_Dir(DFT_SCAN_DIR);	//默认扫描方向
}	

void TFT_SetBackLight(int16_t dat)
{
	TIM2->CCR2=dat;
}
//SRAM_HandleTypeDef hsram1;

//初始化TFT
//该初始化函数可以初始化各种ILI93XX液晶,但是其他函数是基于ILI9320的!!!
//在其他型号的驱动芯片上没有测试! 
void TFT_Init(void)
{ 										  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
//	FSMC_NORSRAMTimingInitTypeDef  writeTiming;


//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//使能FSMC时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);//使能PORTB,D,E,G以及AFIO复用功能时钟

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 //PB0 推挽输出 背光
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_Pin_1);

// 	//PORTD复用推挽输出  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
//	  
//	//PORTE复用推挽输出  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
//	  
//   	//	//PORTG12复用推挽输出 A0	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOG, &GPIO_InitStructure); 

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	 //	//PORTD复用推挽输出  
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //复用推挽输出   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOF, &GPIO_InitStructure); 
// 		  
//	readWriteTiming.FSMC_AddressSetupTime = 0x01;	 //地址建立时间（ADDSET）为2个HCLK 1/36M=27ns
//    readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（ADDHLD）模式A未用到	
//    readWriteTiming.FSMC_DataSetupTime = 0x0f;		 // 数据保存时间为16个HCLK,因为液晶驱动IC的读数据的时候，速度不能太快，尤其对1289这个IC。
//    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//    readWriteTiming.FSMC_CLKDivision = 0x00;
//    readWriteTiming.FSMC_DataLatency = 0x00;
//    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
//    
//		 
//	writeTiming.FSMC_AddressSetupTime = 0x00;	 //地址建立时间（ADDSET）为1个HCLK  
//    writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间（A		
//    writeTiming.FSMC_DataSetupTime = 0x03;		 ////数据保存时间为4个HCLK	
//    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
//    writeTiming.FSMC_CLKDivision = 0x00;
//    writeTiming.FSMC_DataLatency = 0x00;
//    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
//		  
//	   
// 
//    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
//    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
//    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
//    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit   
//    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
//    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
//	  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
//    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
//    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
//    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
//    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
//    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
//    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
//    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
//    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序
//	



//    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

//   	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
//			 
#if 0
 	  FSMC_NORSRAM_TimingTypeDef Timing;
  FSMC_NORSRAM_TimingTypeDef ExtTiming;

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK4;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 1;
  Timing.AddressHoldTime = 0;
  Timing.DataSetupTime = 0x0f;
  Timing.BusTurnAroundDuration = 0;
  Timing.CLKDivision = 0;
  Timing.DataLatency = 0;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */
  ExtTiming.AddressSetupTime = 0;
  ExtTiming.AddressHoldTime = 0;
  ExtTiming.DataSetupTime = 3;
  ExtTiming.BusTurnAroundDuration = 0;
  ExtTiming.CLKDivision = 0;
  ExtTiming.DataLatency = 0;
  ExtTiming.AccessMode = FSMC_ACCESS_MODE_A;

  HAL_SRAM_Init(&hsram1, &Timing, &ExtTiming);
#endif
  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

	__HAL_RCC_TIM2_CLK_ENABLE();//|= RCC_APB1ENR_TIM2EN;
	HAL_Delay(50); // delay 50 ms 
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	
	TIM2->CCMR1=0x7000;
	TIM2->CCER=0x30;
	TIM2->CCR2=0xFFFF;
	TIM2->ARR=0xFFFF;

 	TFT_WriteReg(0x0000,0x0001);
	HAL_Delay(50); // delay 50 ms 
	TIM2->CR1=0x81;
  	TFTdev.id = TFT_ReadReg(0x0000);   
  	if(TFTdev.id<0XFF||TFTdev.id==0XFFFF||TFTdev.id==0X9300)//读到ID不正确,新增TFTdev.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
	{		
 		//尝试9341 ID的读取		
		TFT_WR_REG(0XD3);				   
		TFT_RD_DATA(); 				//dummy read 	
 		TFT_RD_DATA();   	    	//读到0X00
  		TFTdev.id=TFT_RD_DATA();   	//读取93								   
 		TFTdev.id<<=8;
		TFTdev.id|=TFT_RD_DATA();  	//读取41 	   			   
 		if(TFTdev.id!=0X9341)		//非9341,尝试是不是6804
		{	
 			TFT_WR_REG(0XBF);				   
			TFT_RD_DATA(); 			//dummy read 	 
	 		TFT_RD_DATA();   	    //读回0X01			   
	 		TFT_RD_DATA(); 			//读回0XD0 			  	
	  		TFTdev.id=TFT_RD_DATA();//这里读回0X68 
			TFTdev.id<<=8;
	  		TFTdev.id|=TFT_RD_DATA();//这里读回0X04	   	  
 		} 
		if(TFTdev.id!=0X9341&&TFTdev.id!=0X6804)TFTdev.id=0x9341;//新增，用于识别9341 	     
	}
	if(TFTdev.id==0X9341)	//9341初始化
	{	 
		TFT_WR_REG(0xCF);  
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0xC1); 
		TFT_WR_DATA(0X30); 
		TFT_WR_REG(0xED);  
		TFT_WR_DATA(0x64); 
		TFT_WR_DATA(0x03); 
		TFT_WR_DATA(0X12); 
		TFT_WR_DATA(0X81); 
		TFT_WR_REG(0xE8);  
		TFT_WR_DATA(0x85); 
		TFT_WR_DATA(0x10); 
		TFT_WR_DATA(0x7A); 
		TFT_WR_REG(0xCB);  
		TFT_WR_DATA(0x39); 
		TFT_WR_DATA(0x2C); 
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0x34); 
		TFT_WR_DATA(0x02); 
		TFT_WR_REG(0xF7);  
		TFT_WR_DATA(0x20); 
		TFT_WR_REG(0xEA);  
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0x00); 
		TFT_WR_REG(0xC0);    //Power control 
		TFT_WR_DATA(0x1B);   //VRH[5:0] 
		TFT_WR_REG(0xC1);    //Power control 
		TFT_WR_DATA(0x01);   //SAP[2:0];BT[3:0] 
		TFT_WR_REG(0xC5);    //VCM control 
		TFT_WR_DATA(0x30); 	 //3F
		TFT_WR_DATA(0x30); 	 //3C
		TFT_WR_REG(0xC7);    //VCM control2 
		TFT_WR_DATA(0XB7); 
		TFT_WR_REG(0x36);    // Memory Access Control 
		TFT_WR_DATA(0x48); 
		TFT_WR_REG(0x3A);   
		TFT_WR_DATA(0x55); 
		TFT_WR_REG(0xB1);   
		TFT_WR_DATA(0x00);   
		TFT_WR_DATA(0x1A); 
		TFT_WR_REG(0xB6);    // Display Function Control 
		TFT_WR_DATA(0x0A); 
		TFT_WR_DATA(0xA2); 
		TFT_WR_REG(0xF2);    // 3Gamma Function Disable 
		TFT_WR_DATA(0x00); 
		TFT_WR_REG(0x26);    //Gamma curve selected 
		TFT_WR_DATA(0x01); 
		TFT_WR_REG(0xE0);    //Set Gamma 
		TFT_WR_DATA(0x0F); 
		TFT_WR_DATA(0x2A); 
		TFT_WR_DATA(0x28); 
		TFT_WR_DATA(0x08); 
		TFT_WR_DATA(0x0E); 
		TFT_WR_DATA(0x08); 
		TFT_WR_DATA(0x54); 
		TFT_WR_DATA(0XA9); 
		TFT_WR_DATA(0x43); 
		TFT_WR_DATA(0x0A); 
		TFT_WR_DATA(0x0F); 
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0x00); 		 
		TFT_WR_REG(0XE1);    //Set Gamma 
		TFT_WR_DATA(0x00); 
		TFT_WR_DATA(0x15); 
		TFT_WR_DATA(0x17); 
		TFT_WR_DATA(0x07); 
		TFT_WR_DATA(0x11); 
		TFT_WR_DATA(0x06); 
		TFT_WR_DATA(0x2B); 
		TFT_WR_DATA(0x56); 
		TFT_WR_DATA(0x3C); 
		TFT_WR_DATA(0x05); 
		TFT_WR_DATA(0x10); 
		TFT_WR_DATA(0x0F); 
		TFT_WR_DATA(0x3F); 
		TFT_WR_DATA(0x3F); 
		TFT_WR_DATA(0x0F); 
		TFT_WR_REG(0x2B); 
		TFT_WR_DATA(0x00);
		TFT_WR_DATA(0x00);
		TFT_WR_DATA(0x01);
		TFT_WR_DATA(0x3f);
		TFT_WR_REG(0x2A); 
		TFT_WR_DATA(0x00);
		TFT_WR_DATA(0x00);
		TFT_WR_DATA(0x00);
		TFT_WR_DATA(0xef);	 
		TFT_WR_REG(0x11); //Exit Sleep
		HAL_Delay(120);
		TFT_WR_REG(0x29); //display on	
	}else if(TFTdev.id==0x6804) //6804初始化
	{
		TFT_WR_REG(0X11);
		HAL_Delay(20);
		TFT_WR_REG(0XD0);//VCI1  VCL  VGH  VGL DDVDH VREG1OUT power amplitude setting
		TFT_WR_DATA(0X07); 
		TFT_WR_DATA(0X42); 
		TFT_WR_DATA(0X1D); 
		TFT_WR_REG(0XD1);//VCOMH VCOM_AC amplitude setting
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X1a);
		TFT_WR_DATA(0X09); 
		TFT_WR_REG(0XD2);//Operational Amplifier Circuit Constant Current Adjust , charge pump frequency setting
		TFT_WR_DATA(0X01);
		TFT_WR_DATA(0X22);
		TFT_WR_REG(0XC0);//REV SM GS 
		TFT_WR_DATA(0X10);
		TFT_WR_DATA(0X3B);
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X02);
		TFT_WR_DATA(0X11);
		
		TFT_WR_REG(0XC5);// Frame rate setting = 72HZ  when setting 0x03
		TFT_WR_DATA(0X03);
		
		TFT_WR_REG(0XC8);//Gamma setting
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X25);
		TFT_WR_DATA(0X21);
		TFT_WR_DATA(0X05);
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X0a);
		TFT_WR_DATA(0X65);
		TFT_WR_DATA(0X25);
		TFT_WR_DATA(0X77);
		TFT_WR_DATA(0X50);
		TFT_WR_DATA(0X0f);
		TFT_WR_DATA(0X00);	  
						  
   		TFT_WR_REG(0XF8);
		TFT_WR_DATA(0X01);	  

 		TFT_WR_REG(0XFE);
 		TFT_WR_DATA(0X00);
 		TFT_WR_DATA(0X02);
		
		TFT_WR_REG(0X20);//Exit invert mode

		TFT_WR_REG(0X36);
		TFT_WR_DATA(0X08);//原来是a
		
		TFT_WR_REG(0X3A);
		TFT_WR_DATA(0X55);//16位模式	  
		TFT_WR_REG(0X2B);
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X01);
		TFT_WR_DATA(0X3F);
		
		TFT_WR_REG(0X2A);
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X00);
		TFT_WR_DATA(0X01);
		TFT_WR_DATA(0XDF);
		HAL_Delay(120);
		TFT_WR_REG(0X29); 	 
 	}else if(TFTdev.id==0x9325)//9325
	{
		TFT_WriteReg(0x00E5,0x78F0); 
		TFT_WriteReg(0x0001,0x0100); 
		TFT_WriteReg(0x0002,0x0700); 
		TFT_WriteReg(0x0003,0x1030); 
		TFT_WriteReg(0x0004,0x0000); 
		TFT_WriteReg(0x0008,0x0202);  
		TFT_WriteReg(0x0009,0x0000);
		TFT_WriteReg(0x000A,0x0000); 
		TFT_WriteReg(0x000C,0x0000); 
		TFT_WriteReg(0x000D,0x0000);
		TFT_WriteReg(0x000F,0x0000);
		//power on sequence VGHVGL
		TFT_WriteReg(0x0010,0x0000);   
		TFT_WriteReg(0x0011,0x0007);  
		TFT_WriteReg(0x0012,0x0000);  
		TFT_WriteReg(0x0013,0x0000); 
		TFT_WriteReg(0x0007,0x0000); 
		//vgh 
		TFT_WriteReg(0x0010,0x1690);   
		TFT_WriteReg(0x0011,0x0227);
		//delayms(100);
		//vregiout 
		TFT_WriteReg(0x0012,0x009D); //0x001b
		//delayms(100); 
		//vom amplitude
		TFT_WriteReg(0x0013,0x1900);
		//delayms(100); 
		//vom H
		TFT_WriteReg(0x0029,0x0025); 
		TFT_WriteReg(0x002B,0x000D); 
		//gamma
		TFT_WriteReg(0x0030,0x0007);
		TFT_WriteReg(0x0031,0x0303);
		TFT_WriteReg(0x0032,0x0003);// 0006
		TFT_WriteReg(0x0035,0x0206);
		TFT_WriteReg(0x0036,0x0008);
		TFT_WriteReg(0x0037,0x0406); 
		TFT_WriteReg(0x0038,0x0304);//0200
		TFT_WriteReg(0x0039,0x0007); 
		TFT_WriteReg(0x003C,0x0602);// 0504
		TFT_WriteReg(0x003D,0x0008); 
		//ram
		TFT_WriteReg(0x0050,0x0000); 
		TFT_WriteReg(0x0051,0x00EF);
		TFT_WriteReg(0x0052,0x0000); 
		TFT_WriteReg(0x0053,0x013F);  
		TFT_WriteReg(0x0060,0xA700); 
		TFT_WriteReg(0x0061,0x0001); 
		TFT_WriteReg(0x006A,0x0000); 
		//
		TFT_WriteReg(0x0080,0x0000); 
		TFT_WriteReg(0x0081,0x0000); 
		TFT_WriteReg(0x0082,0x0000); 
		TFT_WriteReg(0x0083,0x0000); 
		TFT_WriteReg(0x0084,0x0000); 
		TFT_WriteReg(0x0085,0x0000); 
		//
		TFT_WriteReg(0x0090,0x0010); 
		TFT_WriteReg(0x0092,0x0600); 
		
		TFT_WriteReg(0x0007,0x0133);
		TFT_WriteReg(0x00,0x0022);//
	}else if(TFTdev.id==0x9328)//ILI9328   OK  
	{
  		TFT_WriteReg(0x00EC,0x108F);// internal timeing      
 		TFT_WriteReg(0x00EF,0x1234);// ADD        
		//TFT_WriteReg(0x00e7,0x0010);      
        //TFT_WriteReg(0x0000,0x0001);//开启内部时钟
        TFT_WriteReg(0x0001,0x0100);     
        TFT_WriteReg(0x0002,0x0700);//电源开启                    
		//TFT_WriteReg(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(寄存器 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D 正常就用这个.
		// 1  1   1	   U->D	L->R
        TFT_WriteReg(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
        TFT_WriteReg(0x0004,0x0000);                                   
        TFT_WriteReg(0x0008,0x0202);	           
        TFT_WriteReg(0x0009,0x0000);         
        TFT_WriteReg(0x000a,0x0000);//display setting         
        TFT_WriteReg(0x000c,0x0001);//display setting          
        TFT_WriteReg(0x000d,0x0000);//0f3c          
        TFT_WriteReg(0x000f,0x0000);
		//电源配置
        TFT_WriteReg(0x0010,0x0000);   
        TFT_WriteReg(0x0011,0x0007);
        TFT_WriteReg(0x0012,0x0000);                                                                 
        TFT_WriteReg(0x0013,0x0000);                 
     	TFT_WriteReg(0x0007,0x0001);                 
       	HAL_Delay(50); 
        TFT_WriteReg(0x0010,0x1490);   
        TFT_WriteReg(0x0011,0x0227);
        HAL_Delay(50); 
        TFT_WriteReg(0x0012,0x008A);                  
        HAL_Delay(50); 
        TFT_WriteReg(0x0013,0x1a00);   
        TFT_WriteReg(0x0029,0x0006);
        TFT_WriteReg(0x002b,0x000d);
        HAL_Delay(50); 
        TFT_WriteReg(0x0020,0x0000);                                                            
        TFT_WriteReg(0x0021,0x0000);           
		HAL_Delay(50); 
		//伽马校正
        TFT_WriteReg(0x0030,0x0000); 
        TFT_WriteReg(0x0031,0x0604);   
        TFT_WriteReg(0x0032,0x0305);
        TFT_WriteReg(0x0035,0x0000);
        TFT_WriteReg(0x0036,0x0C09); 
        TFT_WriteReg(0x0037,0x0204);
        TFT_WriteReg(0x0038,0x0301);        
        TFT_WriteReg(0x0039,0x0707);     
        TFT_WriteReg(0x003c,0x0000);
        TFT_WriteReg(0x003d,0x0a0a);
        HAL_Delay(50); 
        TFT_WriteReg(0x0050,0x0000); //水平GRAM起始位置 
        TFT_WriteReg(0x0051,0x00ef); //水平GRAM终止位置                    
        TFT_WriteReg(0x0052,0x0000); //垂直GRAM起始位置                    
        TFT_WriteReg(0x0053,0x013f); //垂直GRAM终止位置  
 
         TFT_WriteReg(0x0060,0xa700);        
        TFT_WriteReg(0x0061,0x0001); 
        TFT_WriteReg(0x006a,0x0000);
        TFT_WriteReg(0x0080,0x0000);
        TFT_WriteReg(0x0081,0x0000);
        TFT_WriteReg(0x0082,0x0000);
        TFT_WriteReg(0x0083,0x0000);
        TFT_WriteReg(0x0084,0x0000);
        TFT_WriteReg(0x0085,0x0000);
      
        TFT_WriteReg(0x0090,0x0010);     
        TFT_WriteReg(0x0092,0x0600);  
        //开启显示设置    
        TFT_WriteReg(0x0007,0x0133); 
	}else if(TFTdev.id==0x9320)//测试OK.
	{
		TFT_WriteReg(0x00,0x0000);
		TFT_WriteReg(0x01,0x0100);	//Driver Output Contral.
		TFT_WriteReg(0x02,0x0700);	//TFT Driver Waveform Contral.
		TFT_WriteReg(0x03,0x1030);//Entry Mode Set.
		//TFT_WriteReg(0x03,0x1018);	//Entry Mode Set.
	
		TFT_WriteReg(0x04,0x0000);	//Scalling Contral.
		TFT_WriteReg(0x08,0x0202);	//Display Contral 2.(0x0207)
		TFT_WriteReg(0x09,0x0000);	//Display Contral 3.(0x0000)
		TFT_WriteReg(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		TFT_WriteReg(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		TFT_WriteReg(0x0d,0x0000);	//Frame Maker Position.
		TFT_WriteReg(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		HAL_Delay(50); 
		TFT_WriteReg(0x07,0x0101);	//Display Contral.
		HAL_Delay(50); 								  
		TFT_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		TFT_WriteReg(0x11,0x0007);								//Power Control 2.(0x0001)
		TFT_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		TFT_WriteReg(0x13,0x0b00);								//Power Control 4.
		TFT_WriteReg(0x29,0x0000);								//Power Control 7.
	
		TFT_WriteReg(0x2b,(1<<14)|(1<<4));	    
		TFT_WriteReg(0x50,0);	//Set X Star
		//水平GRAM终止位置Set X End.
		TFT_WriteReg(0x51,239);	//Set Y Star
		TFT_WriteReg(0x52,0);	//Set Y End.t.
		TFT_WriteReg(0x53,319);	//
	
		TFT_WriteReg(0x60,0x2700);	//Driver Output Control.
		TFT_WriteReg(0x61,0x0001);	//Driver Output Control.
		TFT_WriteReg(0x6a,0x0000);	//Vertical Srcoll Control.
	
		TFT_WriteReg(0x80,0x0000);	//Display Position? Partial Display 1.
		TFT_WriteReg(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		TFT_WriteReg(0x82,0x0000);	//RAM Address End-Partial Display 1.
		TFT_WriteReg(0x83,0x0000);	//Displsy Position? Partial Display 2.
		TFT_WriteReg(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		TFT_WriteReg(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		TFT_WriteReg(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		TFT_WriteReg(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		TFT_WriteReg(0x93,0x0001);	//Panel Interface Contral 3.
		TFT_WriteReg(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		TFT_WriteReg(0x97,(0<<8));	//
		TFT_WriteReg(0x98,0x0000);	//Frame Cycle Contral.	   
		TFT_WriteReg(0x07,0x0173);	//(0x0173)
	}else if(TFTdev.id==0X9331)//OK |/|/|			 
	{
		TFT_WriteReg(0x00E7, 0x1014);
		TFT_WriteReg(0x0001, 0x0100); // set SS and SM bit
		TFT_WriteReg(0x0002, 0x0200); // set 1 line inversion
        TFT_WriteReg(0x0003,(1<<12)|(3<<4)|(1<<3));//65K    
		//TFT_WriteReg(0x0003, 0x1030); // set GRAM write direction and BGR=1.
		TFT_WriteReg(0x0008, 0x0202); // set the back porch and front porch
		TFT_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		TFT_WriteReg(0x000A, 0x0000); // FMARK function
		TFT_WriteReg(0x000C, 0x0000); // RGB interface setting
		TFT_WriteReg(0x000D, 0x0000); // Frame marker Position
		TFT_WriteReg(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		TFT_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		TFT_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		TFT_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
		TFT_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		HAL_Delay(200); // Dis-charge capacitor power voltage
		TFT_WriteReg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		TFT_WriteReg(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		HAL_Delay(50); // Delay 50ms
		TFT_WriteReg(0x0012, 0x000C); // Internal reference voltage= Vci;
		HAL_Delay(50); // Delay 50ms
		TFT_WriteReg(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		TFT_WriteReg(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		TFT_WriteReg(0x002B, 0x000B); // Set Frame Rate
		HAL_Delay(50); // Delay 50ms
		TFT_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
		TFT_WriteReg(0x0021, 0x013f); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		TFT_WriteReg(0x0030, 0x0000);
		TFT_WriteReg(0x0031, 0x0106);
		TFT_WriteReg(0x0032, 0x0000);
		TFT_WriteReg(0x0035, 0x0204);
		TFT_WriteReg(0x0036, 0x160A);
		TFT_WriteReg(0x0037, 0x0707);
		TFT_WriteReg(0x0038, 0x0106);
		TFT_WriteReg(0x0039, 0x0707);
		TFT_WriteReg(0x003C, 0x0402);
		TFT_WriteReg(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		TFT_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
		TFT_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
		TFT_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
		TFT_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
		TFT_WriteReg(0x0060, 0x2700); // Gate Scan Line
		TFT_WriteReg(0x0061, 0x0001); // NDL,VLE, REV 
		TFT_WriteReg(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		TFT_WriteReg(0x0080, 0x0000);
		TFT_WriteReg(0x0081, 0x0000);
		TFT_WriteReg(0x0082, 0x0000);
		TFT_WriteReg(0x0083, 0x0000);
		TFT_WriteReg(0x0084, 0x0000);
		TFT_WriteReg(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		TFT_WriteReg(0x0090, 0x0010);
		TFT_WriteReg(0x0092, 0x0600);
		TFT_WriteReg(0x0007, 0x0133); // 262K color and display ON
	}else if(TFTdev.id==0x5408)
	{
		TFT_WriteReg(0x01,0x0100);								  
		TFT_WriteReg(0x02,0x0700);//TFT Driving Waveform Contral 
		TFT_WriteReg(0x03,0x1030);//Entry Mode设置 	   
		//指针从左至右自上而下的自动增模式
		//Normal Mode(Window Mode disable)
		//RGB格式
		//16位数据2次传输的8总线设置
		TFT_WriteReg(0x04,0x0000); //Scalling Control register     
		TFT_WriteReg(0x08,0x0207); //Display Control 2 
		TFT_WriteReg(0x09,0x0000); //Display Control 3	 
		TFT_WriteReg(0x0A,0x0000); //Frame Cycle Control	 
		TFT_WriteReg(0x0C,0x0000); //External Display Interface Control 1 
		TFT_WriteReg(0x0D,0x0000); //Frame Maker Position		 
		TFT_WriteReg(0x0F,0x0000); //External Display Interface Control 2 
 		HAL_Delay(20);
		//TFT 液晶彩色图像显示方法14
		TFT_WriteReg(0x10,0x16B0); //0x14B0 //Power Control 1
		TFT_WriteReg(0x11,0x0001); //0x0007 //Power Control 2
		TFT_WriteReg(0x17,0x0001); //0x0000 //Power Control 3
		TFT_WriteReg(0x12,0x0138); //0x013B //Power Control 4
		TFT_WriteReg(0x13,0x0800); //0x0800 //Power Control 5
		TFT_WriteReg(0x29,0x0009); //NVM read data 2
		TFT_WriteReg(0x2a,0x0009); //NVM read data 3
		TFT_WriteReg(0xa4,0x0000);	 
		TFT_WriteReg(0x50,0x0000); //设置操作窗口的X轴开始列
		TFT_WriteReg(0x51,0x00EF); //设置操作窗口的X轴结束列
		TFT_WriteReg(0x52,0x0000); //设置操作窗口的Y轴开始行
		TFT_WriteReg(0x53,0x013F); //设置操作窗口的Y轴结束行
		TFT_WriteReg(0x60,0x2700); //Driver Output Control
		//设置屏幕的点数以及扫描的起始行
		TFT_WriteReg(0x61,0x0001); //Driver Output Control
		TFT_WriteReg(0x6A,0x0000); //Vertical Scroll Control
		TFT_WriteReg(0x80,0x0000); //Display Position – Partial Display 1
		TFT_WriteReg(0x81,0x0000); //RAM Address Start – Partial Display 1
		TFT_WriteReg(0x82,0x0000); //RAM address End - Partial Display 1
		TFT_WriteReg(0x83,0x0000); //Display Position – Partial Display 2
		TFT_WriteReg(0x84,0x0000); //RAM Address Start – Partial Display 2
		TFT_WriteReg(0x85,0x0000); //RAM address End – Partail Display2
		TFT_WriteReg(0x90,0x0013); //Frame Cycle Control
		TFT_WriteReg(0x92,0x0000);  //Panel Interface Control 2
		TFT_WriteReg(0x93,0x0003); //Panel Interface control 3
		TFT_WriteReg(0x95,0x0110);  //Frame Cycle Control
		TFT_WriteReg(0x07,0x0173);		 
		HAL_Delay(50);
	}	
	else if(TFTdev.id==0x1505)//OK
	{
		// second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        TFT_WriteReg(0x0007,0x0000);
        HAL_Delay(50); 
        TFT_WriteReg(0x0012,0x011C);//0x011A   why need to set several times?
        TFT_WriteReg(0x00A4,0x0001);//NVM	 
        TFT_WriteReg(0x0008,0x000F);
        TFT_WriteReg(0x000A,0x0008);
        TFT_WriteReg(0x000D,0x0008);	    
  		//伽马校正
        TFT_WriteReg(0x0030,0x0707);
        TFT_WriteReg(0x0031,0x0007); //0x0707
        TFT_WriteReg(0x0032,0x0603); 
        TFT_WriteReg(0x0033,0x0700); 
        TFT_WriteReg(0x0034,0x0202); 
        TFT_WriteReg(0x0035,0x0002); //?0x0606
        TFT_WriteReg(0x0036,0x1F0F);
        TFT_WriteReg(0x0037,0x0707); //0x0f0f  0x0105
        TFT_WriteReg(0x0038,0x0000); 
        TFT_WriteReg(0x0039,0x0000); 
        TFT_WriteReg(0x003A,0x0707); 
        TFT_WriteReg(0x003B,0x0000); //0x0303
        TFT_WriteReg(0x003C,0x0007); //?0x0707
        TFT_WriteReg(0x003D,0x0000); //0x1313//0x1f08
        HAL_Delay(50); 
        TFT_WriteReg(0x0007,0x0001);
        TFT_WriteReg(0x0017,0x0001);//开启电源
        HAL_Delay(50); 
  		//电源配置
        TFT_WriteReg(0x0010,0x17A0); 
        TFT_WriteReg(0x0011,0x0217);//reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        TFT_WriteReg(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        TFT_WriteReg(0x0013,0x0F00);//VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        TFT_WriteReg(0x002A,0x0000);  
        TFT_WriteReg(0x0029,0x000A);//0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        TFT_WriteReg(0x0012,0x013E);// 0x013C  power supply on
        //Coordinates Control//
        TFT_WriteReg(0x0050,0x0000);//0x0e00
        TFT_WriteReg(0x0051,0x00EF); 
        TFT_WriteReg(0x0052,0x0000); 
        TFT_WriteReg(0x0053,0x013F); 
    	//Pannel Image Control//
        TFT_WriteReg(0x0060,0x2700); 
        TFT_WriteReg(0x0061,0x0001); 
        TFT_WriteReg(0x006A,0x0000); 
        TFT_WriteReg(0x0080,0x0000); 
    	//Partial Image Control//
        TFT_WriteReg(0x0081,0x0000); 
        TFT_WriteReg(0x0082,0x0000); 
        TFT_WriteReg(0x0083,0x0000); 
        TFT_WriteReg(0x0084,0x0000); 
        TFT_WriteReg(0x0085,0x0000); 
  		//Panel Interface Control//
        TFT_WriteReg(0x0090,0x0013);//0x0010 frenqucy
        TFT_WriteReg(0x0092,0x0300); 
        TFT_WriteReg(0x0093,0x0005); 
        TFT_WriteReg(0x0095,0x0000); 
        TFT_WriteReg(0x0097,0x0000); 
        TFT_WriteReg(0x0098,0x0000); 
  
        TFT_WriteReg(0x0001,0x0100); 
        TFT_WriteReg(0x0002,0x0700); 
        TFT_WriteReg(0x0003,0x1038);//扫描方向 上->下  左->右 
        TFT_WriteReg(0x0004,0x0000); 
        TFT_WriteReg(0x000C,0x0000); 
        TFT_WriteReg(0x000F,0x0000); 
        TFT_WriteReg(0x0020,0x0000); 
        TFT_WriteReg(0x0021,0x0000); 
        TFT_WriteReg(0x0007,0x0021); 
        HAL_Delay(20);
        TFT_WriteReg(0x0007,0x0061); 
        HAL_Delay(20);
        TFT_WriteReg(0x0007,0x0173); 
        HAL_Delay(20);
	}else if(TFTdev.id==0xB505)
	{
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
		
		TFT_WriteReg(0x00a4,0x0001);
		HAL_Delay(20);		  
		TFT_WriteReg(0x0060,0x2700);
		TFT_WriteReg(0x0008,0x0202);
		
		TFT_WriteReg(0x0030,0x0214);
		TFT_WriteReg(0x0031,0x3715);
		TFT_WriteReg(0x0032,0x0604);
		TFT_WriteReg(0x0033,0x0e16);
		TFT_WriteReg(0x0034,0x2211);
		TFT_WriteReg(0x0035,0x1500);
		TFT_WriteReg(0x0036,0x8507);
		TFT_WriteReg(0x0037,0x1407);
		TFT_WriteReg(0x0038,0x1403);
		TFT_WriteReg(0x0039,0x0020);
		
		TFT_WriteReg(0x0090,0x001a);
		TFT_WriteReg(0x0010,0x0000);
		TFT_WriteReg(0x0011,0x0007);
		TFT_WriteReg(0x0012,0x0000);
		TFT_WriteReg(0x0013,0x0000);
		HAL_Delay(20);
		
		TFT_WriteReg(0x0010,0x0730);
		TFT_WriteReg(0x0011,0x0137);
		HAL_Delay(20);
		
		TFT_WriteReg(0x0012,0x01b8);
		HAL_Delay(20);
		
		TFT_WriteReg(0x0013,0x0f00);
		TFT_WriteReg(0x002a,0x0080);
		TFT_WriteReg(0x0029,0x0048);
		HAL_Delay(20);
		
		TFT_WriteReg(0x0001,0x0100);
		TFT_WriteReg(0x0002,0x0700);
        TFT_WriteReg(0x0003,0x1038);//扫描方向 上->下  左->右 
		TFT_WriteReg(0x0008,0x0202);
		TFT_WriteReg(0x000a,0x0000);
		TFT_WriteReg(0x000c,0x0000);
		TFT_WriteReg(0x000d,0x0000);
		TFT_WriteReg(0x000e,0x0030);
		TFT_WriteReg(0x0050,0x0000);
		TFT_WriteReg(0x0051,0x00ef);
		TFT_WriteReg(0x0052,0x0000);
		TFT_WriteReg(0x0053,0x013f);
		TFT_WriteReg(0x0060,0x2700);
		TFT_WriteReg(0x0061,0x0001);
		TFT_WriteReg(0x006a,0x0000);
		//TFT_WriteReg(0x0080,0x0000);
		//TFT_WriteReg(0x0081,0x0000);
		TFT_WriteReg(0x0090,0X0011);
		TFT_WriteReg(0x0092,0x0600);
		TFT_WriteReg(0x0093,0x0402);
		TFT_WriteReg(0x0094,0x0002);
		HAL_Delay(20);
		
		TFT_WriteReg(0x0007,0x0001);
		HAL_Delay(20);
		TFT_WriteReg(0x0007,0x0061);
		TFT_WriteReg(0x0007,0x0173);
		
		TFT_WriteReg(0x0020,0x0000);
		TFT_WriteReg(0x0021,0x0000);	  
		TFT_WriteReg(0x00,0x22);  
	}else if(TFTdev.id==0xC505)
	{
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
		HAL_Delay(20);		  
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
		TFT_WriteReg(0x0000,0x0000);
 		TFT_WriteReg(0x00a4,0x0001);
		HAL_Delay(20);		  
		TFT_WriteReg(0x0060,0x2700);
		TFT_WriteReg(0x0008,0x0806);
		
		TFT_WriteReg(0x0030,0x0703);//gamma setting
		TFT_WriteReg(0x0031,0x0001);
		TFT_WriteReg(0x0032,0x0004);
		TFT_WriteReg(0x0033,0x0102);
		TFT_WriteReg(0x0034,0x0300);
		TFT_WriteReg(0x0035,0x0103);
		TFT_WriteReg(0x0036,0x001F);
		TFT_WriteReg(0x0037,0x0703);
		TFT_WriteReg(0x0038,0x0001);
		TFT_WriteReg(0x0039,0x0004);
		
		
		
		TFT_WriteReg(0x0090, 0x0015);	//80Hz
		TFT_WriteReg(0x0010, 0X0410);	//BT,AP
		TFT_WriteReg(0x0011,0x0247);	//DC1,DC0,VC
		TFT_WriteReg(0x0012, 0x01BC);
		TFT_WriteReg(0x0013, 0x0e00);
		HAL_Delay(120);
		TFT_WriteReg(0x0001, 0x0100);
		TFT_WriteReg(0x0002, 0x0200);
		TFT_WriteReg(0x0003, 0x1030);
		
		TFT_WriteReg(0x000A, 0x0008);
		TFT_WriteReg(0x000C, 0x0000);
		
		TFT_WriteReg(0x000E, 0x0020);
		TFT_WriteReg(0x000F, 0x0000);
		TFT_WriteReg(0x0020, 0x0000);	//H Start
		TFT_WriteReg(0x0021, 0x0000);	//V Start
		TFT_WriteReg(0x002A,0x003D);	//vcom2
		HAL_Delay(20);
		TFT_WriteReg(0x0029, 0x002d);
		TFT_WriteReg(0x0050, 0x0000);
		TFT_WriteReg(0x0051, 0xD0EF);
		TFT_WriteReg(0x0052, 0x0000);
		TFT_WriteReg(0x0053, 0x013F);
		TFT_WriteReg(0x0061, 0x0000);
		TFT_WriteReg(0x006A, 0x0000);
		TFT_WriteReg(0x0092,0x0300); 
 
 		TFT_WriteReg(0x0093, 0x0005);
		TFT_WriteReg(0x0007, 0x0100);
	}else if(TFTdev.id==0x8989)//OK |/|/|
	{	   
		TFT_WriteReg(0x0000,0x0001);//打开晶振
    	TFT_WriteReg(0x0003,0xA8A4);//0xA8A4
    	TFT_WriteReg(0x000C,0x0000);    
    	TFT_WriteReg(0x000D,0x080C);   
    	TFT_WriteReg(0x000E,0x2B00);    
    	TFT_WriteReg(0x001E,0x00B0);    
    	TFT_WriteReg(0x0001,0x2B3F);//驱动输出控制320*240  0x6B3F
    	TFT_WriteReg(0x0002,0x0600);
    	TFT_WriteReg(0x0010,0x0000);  
    	TFT_WriteReg(0x0011,0x6078); //定义数据格式  16位色 		横屏 0x6058
    	TFT_WriteReg(0x0005,0x0000);  
    	TFT_WriteReg(0x0006,0x0000);  
    	TFT_WriteReg(0x0016,0xEF1C);  
    	TFT_WriteReg(0x0017,0x0003);  
    	TFT_WriteReg(0x0007,0x0233); //0x0233       
    	TFT_WriteReg(0x000B,0x0000);  
    	TFT_WriteReg(0x000F,0x0000); //扫描开始地址
    	TFT_WriteReg(0x0041,0x0000);  
    	TFT_WriteReg(0x0042,0x0000);  
    	TFT_WriteReg(0x0048,0x0000);  
    	TFT_WriteReg(0x0049,0x013F);  
    	TFT_WriteReg(0x004A,0x0000);  
    	TFT_WriteReg(0x004B,0x0000);  
    	TFT_WriteReg(0x0044,0xEF00);  
    	TFT_WriteReg(0x0045,0x0000);  
    	TFT_WriteReg(0x0046,0x013F);  
    	TFT_WriteReg(0x0030,0x0707);  
    	TFT_WriteReg(0x0031,0x0204);  
    	TFT_WriteReg(0x0032,0x0204);  
    	TFT_WriteReg(0x0033,0x0502);  
    	TFT_WriteReg(0x0034,0x0507);  
    	TFT_WriteReg(0x0035,0x0204);  
    	TFT_WriteReg(0x0036,0x0204);  
    	TFT_WriteReg(0x0037,0x0502);  
    	TFT_WriteReg(0x003A,0x0302);  
    	TFT_WriteReg(0x003B,0x0302);  
    	TFT_WriteReg(0x0023,0x0000);  
    	TFT_WriteReg(0x0024,0x0000);  
    	TFT_WriteReg(0x0025,0x8000);  
    	TFT_WriteReg(0x004f,0);        //行首址0
    	TFT_WriteReg(0x004e,0);        //列首址0
	}else if(TFTdev.id==0x4531)//OK |/|/|
	{
		TFT_WriteReg(0X00,0X0001);   
		HAL_Delay(10);   
		TFT_WriteReg(0X10,0X1628);   
		TFT_WriteReg(0X12,0X000e);//0x0006    
		TFT_WriteReg(0X13,0X0A39);   
		HAL_Delay(10);   
		TFT_WriteReg(0X11,0X0040);   
		TFT_WriteReg(0X15,0X0050);   
		HAL_Delay(10);   
		TFT_WriteReg(0X12,0X001e);//16    
		HAL_Delay(10);   
		TFT_WriteReg(0X10,0X1620);   
		TFT_WriteReg(0X13,0X2A39);   
		HAL_Delay(10);   
		TFT_WriteReg(0X01,0X0100);   
		TFT_WriteReg(0X02,0X0300);   
		TFT_WriteReg(0X03,0X1038);//改变方向的   
		TFT_WriteReg(0X08,0X0202);   
		TFT_WriteReg(0X0A,0X0008);   
		TFT_WriteReg(0X30,0X0000);   
		TFT_WriteReg(0X31,0X0402);   
		TFT_WriteReg(0X32,0X0106);   
		TFT_WriteReg(0X33,0X0503);   
		TFT_WriteReg(0X34,0X0104);   
		TFT_WriteReg(0X35,0X0301);   
		TFT_WriteReg(0X36,0X0707);   
		TFT_WriteReg(0X37,0X0305);   
		TFT_WriteReg(0X38,0X0208);   
		TFT_WriteReg(0X39,0X0F0B);   
		TFT_WriteReg(0X41,0X0002);   
		TFT_WriteReg(0X60,0X2700);   
		TFT_WriteReg(0X61,0X0001);   
		TFT_WriteReg(0X90,0X0210);   
		TFT_WriteReg(0X92,0X010A);   
		TFT_WriteReg(0X93,0X0004);   
		TFT_WriteReg(0XA0,0X0100);   
		TFT_WriteReg(0X07,0X0001);   
		TFT_WriteReg(0X07,0X0021);   
		TFT_WriteReg(0X07,0X0023);   
		TFT_WriteReg(0X07,0X0033);   
		TFT_WriteReg(0X07,0X0133);   
		TFT_WriteReg(0XA0,0X0000); 
	}else if(TFTdev.id==0x4535)
	{			      
		TFT_WriteReg(0X15,0X0030);   
		TFT_WriteReg(0X9A,0X0010);   
 		TFT_WriteReg(0X11,0X0020);   
 		TFT_WriteReg(0X10,0X3428);   
		TFT_WriteReg(0X12,0X0002);//16    
 		TFT_WriteReg(0X13,0X1038);   
		HAL_Delay(40);   
		TFT_WriteReg(0X12,0X0012);//16    
		HAL_Delay(40);   
  		TFT_WriteReg(0X10,0X3420);   
 		TFT_WriteReg(0X13,0X3038);   
		HAL_Delay(70);   
		TFT_WriteReg(0X30,0X0000);   
		TFT_WriteReg(0X31,0X0402);   
		TFT_WriteReg(0X32,0X0307);   
		TFT_WriteReg(0X33,0X0304);   
		TFT_WriteReg(0X34,0X0004);   
		TFT_WriteReg(0X35,0X0401);   
		TFT_WriteReg(0X36,0X0707);   
		TFT_WriteReg(0X37,0X0305);   
		TFT_WriteReg(0X38,0X0610);   
		TFT_WriteReg(0X39,0X0610); 
		  
		TFT_WriteReg(0X01,0X0100);   
		TFT_WriteReg(0X02,0X0300);   
		TFT_WriteReg(0X03,0X1030);//改变方向的   
		TFT_WriteReg(0X08,0X0808);   
		TFT_WriteReg(0X0A,0X0008);   
 		TFT_WriteReg(0X60,0X2700);   
		TFT_WriteReg(0X61,0X0001);   
		TFT_WriteReg(0X90,0X013E);   
		TFT_WriteReg(0X92,0X0100);   
		TFT_WriteReg(0X93,0X0100);   
 		TFT_WriteReg(0XA0,0X3000);   
 		TFT_WriteReg(0XA3,0X0010);   
		TFT_WriteReg(0X07,0X0001);   
		TFT_WriteReg(0X07,0X0021);   
		TFT_WriteReg(0X07,0X0023);   
		TFT_WriteReg(0X07,0X0033);   
		TFT_WriteReg(0X07,0X0133);   
	}		
	TFT_Display_Dir(1);		 	
//	TFT_LED=1;
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
						//点亮背光
	TFT_Clear(WHITE);
}  
//清屏函数
//color:要清屏的填充色
void TFT_Clear(INT16U color)
{
	INT32U index=0;      
	INT32U totalpoint=TFTdev.width;
	totalpoint*=TFTdev.height; 	//得到总点数		  
	TFT_SetCursor(0x00,0x0000);	//设置光标位置 
	TFT_WriteRAM_Prepare();     //开始写入GRAM	
	for(index=0;index<totalpoint;index++)
	{
		TFT->TFT_RAM=color;		   			  
	}
	 //printf("colo=%d  ram=%d\n",color,TFT->TFT_RAM)	;
}  	  	
//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void TFT_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,INT16U color)
{          
	INT16U i,j;
	INT16U xlen=0;
	xlen=ex-sx+1;	   
	for(i=sy;i<=ey;i++)
	{
	 	TFT_SetCursor(sx,i);      				//设置光标位置 
		TFT_WriteRAM_Prepare();     			//开始写入GRAM	  
		for(j=0;j<xlen;j++)TFT_WR_DATA(color);	//设置光标位置 	    
	}
}  
//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void TFT_Color_Fill(INT16U sx,INT16U sy,INT16U ex,INT16U ey,INT16U *color)
{  
	INT16U height,width;
	INT16U i,j;
	width=ex-sx+1; 		//得到填充的宽度
	height=ey-sy+1;		//高度
 	for(i=0;i<height;i++)
	{
 		TFT_SetCursor(sx,sy+i);   	//设置光标位置 
		TFT_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)TFT->TFT_RAM=color[i*height+j];//写入数据 
	}	  
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void TFT_DrawLine(INT16U x1, INT16U y1, INT16U x2, INT16U y2)
{
	INT16U t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		TFT_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//画矩形	  
//(x1,y1),(x2,y2):矩形的对角坐标
void TFT_DrawRectangle(INT16U x1, INT16U y1, INT16U x2, INT16U y2)
{
	TFT_DrawLine(x1,y1,x2,y1);
	TFT_DrawLine(x1,y1,x1,y2);
	TFT_DrawLine(x1,y2,x2,y2);
	TFT_DrawLine(x2,y1,x2,y2);
}
//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(INT16U x0,INT16U y0,INT8U r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		TFT_DrawPoint(x0+a,y0-b);             //5
 		TFT_DrawPoint(x0+b,y0-a);             //0           
		TFT_DrawPoint(x0+b,y0+a);             //4               
		TFT_DrawPoint(x0+a,y0+b);             //6 
		TFT_DrawPoint(x0-a,y0+b);             //1       
 		TFT_DrawPoint(x0-b,y0+a);             
		TFT_DrawPoint(x0-a,y0-b);             //2             
  		TFT_DrawPoint(x0-b,y0-a);             //7     	         
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)
void TFT_ShowChar(INT16U x,INT16U y,INT8U num,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,INT8U mode)
{  							  
    INT8U temp,t1=y,t,t2;
	INT16U x1=0;
	INT16U colortemp=POINT_COLOR;      			     
	//设置窗口		   
	if(num<' ')return;
	//num=num-' ';//得到偏移后的值
	fontdat+=(num-' ')*fontsize;
	    for(t=0;t<fontsize;t++)
	    {   
			temp=*(fontdat++);
	        for(t2=0;t2<8;t2++)
			{			    
		        if(temp&0x01)POINT_COLOR=colortemp;
				else if(!mode)POINT_COLOR=BACK_COLOR;
				if(y+t1>=TFTdev.width){POINT_COLOR=colortemp;return;}//超区域了
				TFT_DrawPoint(x+x1,y++);	
				temp>>=1;
			}  	 
			if(x>=TFTdev.width){POINT_COLOR=colortemp;return;}//超区域了
			x1++;
			if(x1>=fontwidth)
			{
				x1=0;
				t1+=8;
				
			}
			y=t1;
			
	    }    
	POINT_COLOR=colortemp;
	return;
}
//m^n函数
//返回值:m^n次方.
INT32U TFT_Pow(INT8U m,INT8U n)
{
	INT32U result=1;	 
	while(n--)result*=m;    
	return result;
}			 
//显示数字,高位为0,则不显示
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//color:颜色 
//num:数值(0~4294967295);	 
void TFT_ShowNum(INT16U x,INT16U y,INT32U num,INT8U len,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat)
{         	
	INT8U t,temp;
	INT8U enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/TFT_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				TFT_ShowChar(x+fontwidth*t,y,' ',fontwidth,fontsize,fontdat,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	TFT_ShowChar(x+fontwidth*t,y,temp+'0',fontwidth,fontsize,fontdat,0); 
	}
} 
//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);	 
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void TFT_ShowxNum(INT16U x,INT16U y,INT32U num,INT8U len,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,INT8U mode)
{  
	INT8U t,temp;
	INT8U enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/TFT_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)TFT_ShowChar(x+fontwidth*t,y,'0',fontwidth,fontsize,fontdat,mode&0X01);  
				else TFT_ShowChar(x+fontwidth*t,y,' ',fontwidth,fontsize,fontdat,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	TFT_ShowChar(x+fontwidth*t,y,temp+'0',fontwidth,fontsize,fontdat,mode&0X01); 
	}
} 
//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void TFT_ShowString(INT16U x,INT16U y,INT16U width,INT16U height,INT8U fontwidth,INT16U fontsize,const INT8U *fontdat,const char *p)
{         
	INT8U x0=x;
	width+=x;
	height+=y;

    while((*p<='~')&&(*p>'\000'))//判断是不是非法字符!
    {       
        if((x>=width)||(*p=='\n')){x=x0;y+=fontsize/fontwidth;continue;}
        if(y>=height)break;//退出
        TFT_ShowChar(x,y,*p,fontwidth,fontsize,fontdat,0);
        x+=fontwidth;
        p++;
    }  
}
#endif
