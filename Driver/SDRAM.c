#include "includes.h"
#if SDRAM_EN>0
//发送SDRAM初始化序列
void SDRAMInit(SDRAM_HandleTypeDef *hsdram)
{
	FMC_SDRAM_TimingTypeDef SDRAM_Timing;
                                                     
    hsdram->Instance=FMC_SDRAM_DEVICE;                                  //SDRAMÔÚBANK5,6  
    hsdram->Init.SDBank=FMC_SDRAM_BANK1;                           //SDRAM½ÓÔÚBANK5ÉÏ
    hsdram->Init.ColumnBitsNumber=FMC_SDRAM_COLUMN_BITS_NUM_9;     //ÁÐÊýÁ¿
    hsdram->Init.RowBitsNumber=FMC_SDRAM_ROW_BITS_NUM_13;          //ÐÐÊýÁ¿
    hsdram->Init.MemoryDataWidth=FMC_SDRAM_MEM_BUS_WIDTH_16;       //Êý¾Ý¿í¶ÈÎª16Î»
    hsdram->Init.InternalBankNumber=FMC_SDRAM_INTERN_BANKS_NUM_4;  //Ò»¹²4¸öBANK
    hsdram->Init.CASLatency=FMC_SDRAM_CAS_LATENCY_3;               //CASÎª3
    hsdram->Init.WriteProtection=FMC_SDRAM_WRITE_PROTECTION_DISABLE;//Ê§ÄÜÐ´±£»¤
    hsdram->Init.SDClockPeriod=FMC_SDRAM_CLOCK_PERIOD_2;           //SDRAMÊ±ÖÓÎªHCLK/2=216M/2=108M=9.3ns
    hsdram->Init.ReadBurst=FMC_SDRAM_RBURST_ENABLE;                //Ê¹ÄÜÍ»·¢
    hsdram->Init.ReadPipeDelay=FMC_SDRAM_RPIPE_DELAY_1;            //¶ÁÍ¨µÀÑÓÊ±
    
    SDRAM_Timing.LoadToActiveDelay=2;                                   //¼ÓÔØÄ£Ê½¼Ä´æÆ÷µ½¼¤»îÊ±¼äµÄÑÓ³ÙÎª2¸öÊ±ÖÓÖÜÆÚ
    SDRAM_Timing.ExitSelfRefreshDelay=8;                                //ÍË³ö×ÔË¢ÐÂÑÓ³ÙÎª8¸öÊ±ÖÓÖÜÆÚ
    SDRAM_Timing.SelfRefreshTime=6;                                     //×ÔË¢ÐÂÊ±¼äÎª6¸öÊ±ÖÓÖÜÆÚ                                 
    SDRAM_Timing.RowCycleDelay=6;                                       //ÐÐÑ­»·ÑÓ³ÙÎª6¸öÊ±ÖÓÖÜÆÚ
    SDRAM_Timing.WriteRecoveryTime=2;                                   //»Ö¸´ÑÓ³ÙÎª2¸öÊ±ÖÓÖÜÆÚ
    SDRAM_Timing.RPDelay=2;                                             //ÐÐÔ¤³äµçÑÓ³ÙÎª2¸öÊ±ÖÓÖÜÆÚ
    SDRAM_Timing.RCDDelay=2;                                            //ÐÐµ½ÁÐÑÓ³ÙÎª2¸öÊ±ÖÓÖÜÆÚ
    HAL_SDRAM_Init(hsdram,&SDRAM_Timing);  

	INT32U temp=0;
    //SDRAM控制器初始化完成以后还需要按照如下顺序初始化SDRAM
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_CLK_ENABLE,1,0,hsdram); //时钟配置使能
    HAL_Delay(1);                                  //至少延时200us
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_PALL,1,0,hsdram);       //对所有存储区预充电
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_AUTOREFRESH_MODE,8,0,hsdram);//设置自刷新次数 
    //配置模式寄存器,SDRAM的bit0~bit2为指定突发访问的长度，
	//bit3为指定突发访问的类型，bit4~bit6为CAS值，bit7和bit8为运行模式
	//bit9为指定的写突发模式，bit10和bit11位保留位
	temp=(INT32U)SDRAM_MODEREG_BURST_LENGTH_1          |	//设置突发长度:1(可以是1/2/4/8)
              SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |	//设置突发类型:连续(可以是连续/交错)
              SDRAM_MODEREG_CAS_LATENCY_3           |	//设置CAS值:3(可以是2/3)
              SDRAM_MODEREG_OPERATING_MODE_STANDARD |   //设置操作模式:0,标准模式
              SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;     //设置突发写模式:1,单点访问
    SDRAM_Send_Cmd(0,FMC_SDRAM_CMD_LOAD_MODE,1,temp,hsdram);   //设置SDRAM的模式寄存器
    
    //刷新频率计数器(以SDCLK频率计数),计算方法:
	//COUNT=SDRAM刷新周期/行数-20=SDRAM刷新周期(us)*SDCLK频率(Mhz)/行数
    //我们使用的SDRAM刷新周期为64ms,SDCLK=216/2=108Mhz,行数为8192(2^13).
	//所以,COUNT=64*1000*108/8192-20=823
	HAL_SDRAM_ProgramRefreshRate(hsdram,823);	

}	
//向SDRAM发送命令
//bankx:0,向BANK5上面的SDRAM发送指令
//      1,向BANK6上面的SDRAM发送指令
//cmd:指令(0,正常模式/1,时钟配置使能/2,预充电所有存储区/3,自动刷新/4,加载模式寄存器/5,自刷新/6,掉电)
//refresh:自刷新次数
//regval:模式寄存器的定义
//返回值:0,正常;1,失败.
INT8U SDRAM_Send_Cmd(INT8U bankx,INT8U cmd,INT8U refresh,INT16U regval,SDRAM_HandleTypeDef *hsdram)
{
    INT32U target_bank=0;
    FMC_SDRAM_CommandTypeDef Command;
    
    if(bankx==0) target_bank=FMC_SDRAM_CMD_TARGET_BANK1;       
    else if(bankx==1) target_bank=FMC_SDRAM_CMD_TARGET_BANK2;   
    Command.CommandMode=cmd;                //命令
    Command.CommandTarget=target_bank;      //目标SDRAM存储区域
    Command.AutoRefreshNumber=refresh;      //自刷新次数
    Command.ModeRegisterDefinition=regval;  //要写入模式寄存器的值
    if(HAL_SDRAM_SendCommand(hsdram,&Command,0X1000)==HAL_OK) //向SDRAM发送命令
    {
        return 0;  
    }
    else return 1;    
}
#endif
