#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//4.3寸电容触摸屏-GT9147 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/12/28
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved		 
////////////////////////////////////////////////////////////////////////////////// 
_m_tp_dev tp_dev;
//GT9147配置参数表
//第一个字节为版本号(0X60),必须保证新的版本号大于等于GT9147内部
//flash原有版本号,才会更新配置.
//控制I2C速度的延时

//ÑÓÊ±nus
//nusÎªÒªÑÓÊ±µÄusÊý.	
//×¢Òâ:nusµÄÖµ²»Òª´óÓÚ1000us
void delay_us(INT32U nus)
{		
	INT32U ticks;
	INT32U told,tnow,tcnt=0;
	INT32U reload=SysTick->LOAD;				//LOADµÄÖµ	    	 
	ticks=nus*216; 						//ÐèÒªµÄ½ÚÅÄÊý 
	told=SysTick->VAL;        				//¸Õ½øÈëÊ±µÄ¼ÆÊýÆ÷Öµ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;	//ÕâÀï×¢ÒâÒ»ÏÂSYSTICKÊÇÒ»¸öµÝ¼õµÄ¼ÆÊýÆ÷¾Í¿ÉÒÔÁË.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;			//Ê±¼ä³¬¹ý/µÈÓÚÒªÑÓ³ÙµÄÊ±¼ä,ÔòÍË³ö.
		}  
	};
}

void CT_Delay(void)
{
	delay_us(2);
} 
//电容触摸芯片IIC接口初始化
void CT_IIC_Init(void)
{					     
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
	__HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟
    
    GPIO_Initure.Pin=GPIO_PIN_6;            //PH6
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
	
    GPIO_Initure.Pin=GPIO_PIN_3;            //PI3
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //初始化
}
//产生IIC起始信号
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda线输出
	CT_IIC_SDA(1);	  	  
	CT_IIC_SCL(1);
	delay_us(30);
 	CT_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	CT_Delay();
	CT_IIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda线输出
	CT_IIC_SCL(1);
	delay_us(30);
	CT_IIC_SDA(0);//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA(1);//发送I2C总线结束信号  
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
INT8U CT_IIC_Wait_Ack(void)
{
	INT8U ucErrTime=0;
	CT_SDA_IN();      //SDA设置为输入  
	CT_IIC_SDA(1);	   
	CT_IIC_SCL(1);
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void CT_IIC_Ack(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA(0);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}
//不产生ACK应答		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA(1);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void CT_IIC_Send_Byte(INT8U txd)
{                        
    INT8U t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL(0);//拉低时钟开始数据传输
	CT_Delay();
	for(t=0;t<8;t++)
    {              
        CT_IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	      
		CT_IIC_SCL(1); 
		CT_Delay();
		CT_IIC_SCL(0);	
		CT_Delay();
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
INT8U CT_IIC_Read_Byte(unsigned char ack)
{
	INT8U i,receive=0;
 	CT_SDA_IN();//SDA设置为输入
	delay_us(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL(0); 	    	   
		CT_Delay();
		CT_IIC_SCL(1);	 
		receive<<=1;
		if(CT_READ_SDA)receive++;   
	}	  				 
	if (!ack)CT_IIC_NAck();//发送nACK
	else CT_IIC_Ack(); //发送ACK   
 	return receive;
}

const INT8U GT9147_CFG_TBL[]=
{ 
	0X60,0XE0,0X01,0X20,0X03,0X05,0X35,0X00,0X02,0X08,
	0X1E,0X08,0X50,0X3C,0X0F,0X05,0X00,0X00,0XFF,0X67,
	0X50,0X00,0X00,0X18,0X1A,0X1E,0X14,0X89,0X28,0X0A,
	0X30,0X2E,0XBB,0X0A,0X03,0X00,0X00,0X02,0X33,0X1D,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X32,0X00,0X00,
	0X2A,0X1C,0X5A,0X94,0XC5,0X02,0X07,0X00,0X00,0X00,
	0XB5,0X1F,0X00,0X90,0X28,0X00,0X77,0X32,0X00,0X62,
	0X3F,0X00,0X52,0X50,0X00,0X52,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
	0X0F,0X03,0X06,0X10,0X42,0XF8,0X0F,0X14,0X00,0X00,
	0X00,0X00,0X1A,0X18,0X16,0X14,0X12,0X10,0X0E,0X0C,
	0X0A,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0X00,0X29,0X28,0X24,0X22,0X20,0X1F,0X1E,0X1D,
	0X0E,0X0C,0X0A,0X08,0X06,0X05,0X04,0X02,0X00,0XFF,
	0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
	0X00,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
	0XFF,0XFF,0XFF,0XFF,
};  
//发送GT9147配置参数
//mode:0,参数不保存到flash
//     1,参数保存到flash
INT8U GT9147_Send_Cfg(INT8U mode)
{
	INT8U buf[2];
	INT8U i=0;
	buf[0]=0;
	buf[1]=mode;	//是否写入到GT9147 FLASH?  即是否掉电保存
	for(i=0;i<sizeof(GT9147_CFG_TBL);i++)buf[0]+=GT9147_CFG_TBL[i];//计算校验和
    buf[0]=(~buf[0])+1;
	GT9147_WR_Reg(GT_CFGS_REG,(INT8U*)GT9147_CFG_TBL,sizeof(GT9147_CFG_TBL));//发送寄存器配置
	GT9147_WR_Reg(GT_CHECK_REG,buf,2);//写入校验和,和配置更新标记
	return 0;
} 
//向GT9147写入一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:写数据长度
//返回值:0,成功;1,失败.
INT8U GT9147_WR_Reg(INT16U reg,INT8U *buf,INT8U len)
{
	INT8U i;
	INT8U ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//发送写命令 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//发送高8位地址
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    	CT_IIC_Send_Byte(buf[i]);  	//发数据
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//产生一个停止条件	    
	return ret; 
}
//从GT9147读出一次数据
//reg:起始寄存器地址
//buf:数据缓缓存区
//len:读数据长度			  
void GT9147_RD_Reg(INT16U reg,INT8U *buf,INT8U len)
{
	INT8U i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   //发送写命令 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//发送高8位地址
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//发送低8位地址
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT_CMD_RD);   //发送读命令		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
    	buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //发数据	  
	} 
    CT_IIC_Stop();//产生一个停止条件    
} 
//初始化GT9147触摸屏
//返回值:0,初始化成功;1,初始化失败 
INT8U GT9147_Init(void)
{
	INT8U temp[5]; 
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
    __HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟
                
    //PH7
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
            
    //PI8
    GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //初始化
	CT_IIC_Init();      	//初始化电容屏的I2C总线  
	GT_RST(0);				//复位
	HAL_Delay(10);
 	GT_RST(1);				//释放复位		    
	HAL_Delay(10); 
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉，浮空输入
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
	HAL_Delay(100);  
	GT9147_RD_Reg(GT_PID_REG,temp,4);//读取产品ID
	temp[4]=0;
//	printf("CTP ID:%s\r\n",temp);	//打印ID
	temp[0]=0X02;			
	GT9147_WR_Reg(GT_CTRL_REG,temp,1);//软复位GT9147
	GT9147_RD_Reg(GT_CFGS_REG,temp,1);//读取GT_CFGS_REG寄存器
	if(temp[0]<0X60)//默认版本比较低,需要更新flash配置
	{
       if(LTDC_TYPE==0X5510)GT9147_Send_Cfg(1);//更新并保存配置
	}
	HAL_Delay(10);
	temp[0]=0X00;	 
	GT9147_WR_Reg(GT_CTRL_REG,temp,1);//结束复位   
	return 0;
}
const INT16U GT9147_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};
//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
void AInput2DRefreshHook()
{   
    INT8U mode;
	INT8U buf[5];
	INT8U i=0,j;
//	INT8U res=0;
	INT8U temp;
//	INT8U tempsta;
	static INT8U trackid[5];
	BL ava[5]={0};
    GT9147_RD_Reg(GT_GSTID_REG,&mode,1);	//读取触摸点的状态  
    if(mode&0X80&&((mode&0XF)<6))
    {
        temp=0;
        GT9147_WR_Reg(GT_GSTID_REG,&temp,1);//清标志 		
    }		
    if((mode&0XF)&&((mode&0XF)<6))
    {
       // temp=0XFF<<(mode&0XF);		//将点的个数转换为1的位数,匹配tp_dev.sta定义 
       // tempsta=tp_dev.sta;			//保存当前的tp_dev.sta值
       // tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
       // tp_dev.x[4]=tp_dev.x[0];	//保存触点0的数据
       // tp_dev.y[4]=tp_dev.y[0];
        for(i=0;i<(mode&0XF);i++)
        {
            //if(tp_dev.sta&(1<<i))	//触摸有效?
            //{
                GT9147_RD_Reg(GT9147_TPX_TBL[i],buf,5);	//读取XY坐标值
/*                if(LTDC_TYPE==0X5510)   //4.3寸800*480 MCU屏
                {
                    if(tp_dev.touchtype&0X01)//横屏
                    {
                        tp_dev.y[i]=((INT16U)buf[1]<<8)+buf[0];
                        tp_dev.x[i]=800-(((INT16U)buf[3]<<8)+buf[2]);
                    }else
                    {
                        tp_dev.x[i]=((INT16U)buf[1]<<8)+buf[0];
                        tp_dev.y[i]=((INT16U)buf[3]<<8)+buf[2];
                    }  
                }else if(LTDC_TYPE==0X4342) //4.3寸480*272 RGB屏
                {
 */					
			for(j=0;j<5;j++)
			{
				if(trackid[j]==buf[0])break;
			}
			if(j==5)
				for(j=0;j<5;j++)
					if(AInput2DAvailable[j]==0){trackid[j]=buf[0];break;}
			if(j==5)
				trackid[j=buf[0]]=buf[0];	
                   if(lcdltdc.dir)//横屏
                    {
                        AInput2DInput[j][0]=(((INT16U)buf[2]<<8)+buf[1]);
                        AInput2DInput[j][1]=(((INT16U)buf[4]<<8)+buf[3]);
                    }else
                    {
                        AInput2DInput[j][1]=((INT16U)buf[2]<<8)+buf[1];
                        AInput2DInput[j][0]=272-(((INT16U)buf[4]<<8)+buf[3]);
                    }
 //               }
                ava[j]=1;
            //}			
        }  
        for(i=0;i<5;i++)
        {
            AInput2DAvailable[i]=ava[i];
        }
		}
        #if 0
        res=1;
        if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//非法数据(坐标超出了)
        { 
            if((mode&0XF)>1)		//有其他点有数据,则复第二个触点的数据到第一个触点.
            {
                tp_dev.x[0]=tp_dev.x[1];
                tp_dev.y[0]=tp_dev.y[1];
                t=0;				//触发一次,则会最少连续监测10次,从而提高命中率
            }else					//非法数据,则忽略此次数据(还原原来的)  
            {
                tp_dev.x[0]=tp_dev.x[4];
                tp_dev.y[0]=tp_dev.y[4];
                mode=0X80;		
                tp_dev.sta=tempsta;	//恢复tp_dev.sta
            }
        }else t=0;					//触发一次,则会最少连续监测10次,从而提高命中率
	#endif
	if((mode&0X8F)==0X80)//无触摸点按下
	{ 
        for(i=0;i<5;i++)
        {
            AInput2DAvailable[i]=0;
        
//		if(tp_dev.sta&TP_PRES_DOWN)	//之前是被按下的
//		{
//			tp_dev.sta&=~(1<<7);	//标记按键松开
//		}else						//之前就没有被按下
//		{ 
//			tp_dev.x[0]=0xffff;
//			tp_dev.y[0]=0xffff;
//			tp_dev.sta&=0XE0;	//清除点有效标记	
		}	 
	} 	
}
 



























