+conf.h
-CRYSTAL1_ENABLE
--Description:外部振荡器使能

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-CRYSTAL1_FREQ
--Description:外部振荡器频率

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:32768
-CRYSTAL1_CAP
--Description:外部振荡器电容

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:C12P
-DCOCLK_FREQ
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:F16000K
-LFXT1CLK_SEL
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:FVLOCLK
-MCLK_SEL
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:DTOCLK
-MCLK_FREQ
--Description:不用于初始化

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:16000000
-ACLK_SEL
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:LFXT1CLK
-SMCLK_SEL
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:DTOCLK
-SMCLK_DIV
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:DIV1
-SMCLK_FREQ
--Description:不用于初始化

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:16000000
-P1_0_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P1_1_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_INPUT
-P1_2_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P1_3_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P1_4_MODE
--Description:SCLK

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:(PINMODE_OUTPUT|PINMODE_SELECT2)
-P1_5_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_INPUT
-P1_6_MODE
--Description:SCL

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:(PINMODE_OUTPUT|PINMODE_SELECT2)
-P1_7_MODE
--Description:SDA

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:(PINMODE_INPUT|PINMODE_SELECT2)
-P2_0_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_INPUT
-P2_1_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P2_2_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P2_3_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_INPUT
-P2_4_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P2_5_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_INPUT
-P2_6_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P2_7_MODE
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:PINMODE_OUTPUT
-P1_OUTPUT
--Description:初始化时P1口输出状态

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0xff
-P2_OUTPUT
--Description:初始化时P2口输出状态

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0xff
-TIMER_0A_EN
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-TIMER_0A_SOURCE
--Description:源

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:T_SMCLK
-TIMER_0A_SOURCE_DIV
--Description:分配

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:DIV1
-TIMER_0A_BASE_INTR_EN
--Description:中断使能

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TIMER_0A_BASE_MODE
--Description:计数模式

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:UpMode
-TIMER_0A_BASE_FREQ
--Description:溢出频率（已经不用于初始化）

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1000
-TIMER_0A_BASE_MAX_COUNT
--Description:时基最大计数

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:12000
-TIMER_0A_BASE_INTR_CALLBACK
--Description:启动时基回调函数

--Platform:MSP430G2
--Parent:TIMER_0A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TIMER_1A_EN
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TIMER_1A_SOURCE
--Description:源

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:T_SMCLK
-TIMER_1A_SOURCE_DIV
--Description:分配

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:DIV1
-TIMER_1A_BASE_INTR_EN
--Description:中断使能

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TIMER_1A_BASE_MODE
--Description:计数模式

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:UpMode
-TIMER_1A_BASE_CLK_FREQ_KHZ
--Description:时基频率（已经不用于初始化）小于1的填0

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:16
-TIMER_1A_BASE_FREQ
--Description:溢出频率（已经不用于初始化）

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1000
-TIMER_1A_BASE_MAX_COUNT
--Description:时基最大计数

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:16000
-TIMER_1A_BASE_INTR_CALLBACK
--Description:启动时基回调函数

--Platform:MSP430G2
--Parent:TIMER_1A_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-HSPI_EN
--Description:使能HSPI

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-HSPI_INTERFACE
--Description:选择使用模块：0->UCA0或1->UCB0

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-HSPI_CLK_SEL
--Description:时钟选择：USCI_NA（无）或USCI_ACLK（ACLK）或USCI_SMCLK（SMCLK）

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:USCI_SMCLK
-HSPI_CLK_DIV
--Description:时钟分频：1~65535

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:2
-HSPI_MSB_F
--Description:MSP在前

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-HSPI_CPOL
--Description:CPOL

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-HSPI_CPHA
--Description:CPHA

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-HSPI_TX_INTERRUPT_EN
--Description:使能发送中断

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-HSPI_RX_INTERRUPT_EN
--Description:

--Platform:MSP430G2
--Parent:HSPI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-UART_EN
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-UART_INTERFACE
--Description:选择使用模块：0->UCA0

--Platform:MSP430G2
--Parent:UART_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-UART_CLK_SEL
--Description:时钟选择：USCI_NA（无）或USCI_ACLK（ACLK）或USCI_SMCLK（SMCLK）

--Platform:MSP430G2
--Parent:UART_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:USCI_SMCLK
-UART_CLK_DIV
--Description:时钟分频：1~65535

--Platform:MSP430G2
--Parent:UART_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:104
-UART_MSB_F
--Description:MSP在前

--Platform:MSP430G2
--Parent:UART_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-UART_TX_INTERRUPT_EN
--Description:使能发送中断

--Platform:MSP430G2
--Parent:UART_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-UART_RX_INTERRUPT_EN
--Description:

--Platform:MSP430G2
--Parent:UART_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-IIC_EN
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-IIC_INTERFACE
--Description:选择使用模块：1->UCB0

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-IIC_BAUDRATE_DIV
--Description:

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:(SMCLK_FREQ*3/250000)
-IIC_SLAVE_ADDR
--Description:

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0x20
-IIC_TX_STATE
--Description:

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-IIC_RX_STATE
--Description:

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-IIC_TX_INTERRUPT_EN
--Description:使能发送中断

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-IIC_RX_INTERRUPT_EN
--Description:

--Platform:MSP430G2
--Parent:IIC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-BTIMER_COUNT
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:3
-BTIMER_INTERFACE
--Description:

--Platform:MSP430G2
--Parent:BTIMER_COUNT
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:Timer1A
-RTC_EN
--Description:使能RTC

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-RTC_MODE
--Description:RTC_Internal/RTC_External(Don't use)

--Platform:MSP430G2
--Parent:RTC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:RTC_Internal
-RTC_INTR_TIME_IN_MS
--Description:RTC计时中断时间/ms

--Platform:MSP430G2
--Parent:RTC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1000
-RTC_INTERNAL_TIMER
--Description:基本定时器接口（弃用）

--Platform:MSP430G2
--Parent:RTC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:RTC_1S
-ADC_EN
--Description:

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-ADC_REF_SEL
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:VREF_GND
-ADC_SAMP_TIME
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:ADCCLK64
-ADC_SAMP_RATE
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:ADC50KSPS
-ADC_REF_GEN_VOL
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:ADC1500MV
-ADC_CLK_SOURCE
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:ADC_SMCLK
-ADC_DATA_LEFT_ALIGN
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CLK_DIV
--Description:1~8

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-ADC_CH_A0_EN
--Description:0

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A1_EN
--Description:1

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A2_EN
--Description:2

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A3_EN
--Description:3

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A4_EN
--Description:4

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A5_EN
--Description:5

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A6_EN
--Description:6

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A7_EN
--Description:7

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_VEREF_P_EN
--Description:8

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-ADC_CH_VREF_N_EN
--Description:9

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_TEMP_EN
--Description:10

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-ADC_CH_VCC_VSS_EN
--Description:11

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A12_EN
--Description:12

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A13_EN
--Description:13

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A14_EN
--Description:14

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_A15_EN
--Description:15

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-ADC_CH_HIGNEST
--Description:

--Platform:MSP430G2
--Parent:ADC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:10
-DMA_EN
--Description:DMA is supported only in MSP430x2xx device family

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-DMA_DYNAMIC_POLICY
--Description:DMA_DIRECT/DMA_LIST

--Platform:MSP430G2
--Parent:DMA_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:DMA_DIRECT
-DMA_LIST_SIZE
--Description:

--Platform:MSP430G2
--Parent:DMA_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:5
-DMA0_STATIC
--Description:DMA功能固定，不能被动态调度

--Platform:MSP430G2
--Parent:DMA_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-DMA0_REQUEST
--Description:

--Platform:MSP430G2
--Parent:DMA0_STATIC
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:{SoftwareTrigger,BlockMode,RisingEdge,0,WordData,Increase,0,WordData,Increase,0}
-DMA1_STATIC
--Description:DMA功能固定，不能被动态调度

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-DMA1_REQUEST
--Description:

--Platform:MSP430G2
--Parent:DMA1_STATIC
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:{SoftwareTrigger,BlockMode,RisingEdge,0,WordData,Increase,0,WordData,Increase,0}
-DMA2_STATIC
--Description:DMA功能固定，不能被动态调度

--Platform:MSP430G2
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-DMA2_REQUEST
--Description:

--Platform:MSP430G2
--Parent:DMA2_STATIC
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:{SoftwareTrigger,BlockMode,RisingEdge,0,WordData,Increase,0,WordData,Increase,0}
-LFXT1_HIGHSPEED
--Description:高速外部振荡器

--Platform:MSP430G2
--Parent:LFXT1_FREQ
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-LFXT1_HIGHSPEED
--Description:低速外部振荡器

--Platform:MSP430G2
--Parent:LFXT1_FREQ
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-BTIMER_COUNT
--Description:基本计时器数量
0为禁用
--Platform:STM32
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:8
+conf_driver.h
-SSPI_EN
--Description:软件SPI
SSPI固定为SPI模式3，MSB First
CPOL=1
CPHA=1
--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-LCD_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:1
--SetValue:FONT_EN
--Value:1
-LCD_DRIVER
--Description:LCD接口驱动，取值有HSPI和SSPI

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:HSPI
-LCD_INTR_EN
--Description:LCD数据传输由中断控制

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-LCD_BUF_SIZE
--Description:LCD缓冲区大小，仅在中断模式时有效

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:40
-LCD_RST_PIN
--Description:RST引脚号，为GPIOx,PINx的二元组

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:GPIOB,PIN0
-LCD_CS_PIN
--Description:CS引脚号，为GPIOx,PINx的二元组

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:GPIOB,PIN1
-LCD_A0_PIN
--Description:A0引脚号，为GPIOx,PINx的二元组

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:GPIOA,PIN4
-LCD_INIT_FILL_DATA
--Description:

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0x55
-LCD_BUFFER_EN
--Description:启用LCD全屏刷新模式；缓冲区1KB由用户定义

--Platform:
--Parent:LCD_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TCA6416A_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-HT1621_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-DAC8411_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-G2PLATFORM
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-TFT_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TFT_INIT_COLOR
--Description:

--Platform:
--Parent:TFT_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:LIGHTBLUE
-LTDC_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-LTDC_TYPE
--Description:

--Platform:
--Parent:LTDC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0x4342
-LCD_PIXFORMAT
--Description:

--Platform:
--Parent:LTDC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:LCD_PIXEL_FORMAT_RGB565
-LCD_FRAME_BUF_ADDR
--Description:LCD帧缓冲区首地址,这里定义在SDRAM里面.

--Platform:
--Parent:LTDC_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0XC0000000
-FONT_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-SDRAM_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-GT9147_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TFT_ILI9341_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
+conf_Math.h
-BASE64_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-TIME_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
+conf_middleware.h
-ABUTTON_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-ABUTTON_COUNT
--Description:

--Platform:
--Parent:ABUTTON_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:4
-ABUTTON_GET_FUNC_BUFFER_LEN
--Description:

--Platform:
--Parent:ABUTTON_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:10
-ABUFFON_REFRESH_HOOK_EN
--Description:

--Platform:
--Parent:ABUTTON_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-ABUTTON_RAWINPUT_WORDLENGTH
--Description:

--Platform:
--Parent:ABUTTON_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:8
-GUI_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-GUI_WIDTH
--Description:<256

--Platform:
--Parent:GUI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:128
-GUI_HEIGHT
--Description:<256

--Platform:
--Parent:GUI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:64
-GUI_BUF_TYPE
--Description:

--Platform:
--Parent:GUI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:GUI_BLACK_V
-GUI_REFRESH_HOOK
--Description:

--Platform:
--Parent:GUI_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-APPE_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-BT_EXT_CALLBACK
--Description:

--Platform:
--Parent:APPE_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-APPE_PEND_BUF_MAX
--Description:

--Platform:
--Parent:APPE_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:8
-SCR_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-AINPUT2D_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-AINPUT2D_POINT_COUNT
--Description:

--Platform:
--Parent:AINPUT2D_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:10
-AINPUT2D_DPI_X
--Description:

--Platform:
--Parent:AINPUT2D_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:10
-AINPUT2D_BUFFER_LEN
--Description:

--Platform:
--Parent:AINPUT2D_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:25
-AVARIABLE_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-AVARIABLE_INT8U_NUM
--Description:

--Platform:
--Parent:AVARIABLE_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-AVARIABLE_INT16U_NUM
--Description:

--Platform:
--Parent:AVARIABLE_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-AVARIABLE_FLOAT_NUM
--Description:

--Platform:
--Parent:AVARIABLE_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:4
+conf_app.h
-APP_MENU_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-APP_LAUNCHER_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-APP_COUNT
--Description:

--Platform:
--Parent:APP_LAUNCHER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:2
-APP_MENU
--Description:

--Platform:
--Parent:APP_LAUNCHER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:"Time
-APP_STRUCT
--Description:muse be address

--Platform:
--Parent:APP_LAUNCHER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:&AETimeSync,&AESetTime
-TIMESET_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TIMESET_FINISH_OP
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:TimeSyncProcess();
-APPENDLAYER_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-APPENDLAYER_BUFFERSIZE
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:40
-APPENDLAYER_FORMAT
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:"Temp:%.2f"
-APPENDLAYER_VARIABLES
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:AVariableFloat[0]
-APPENDLAYER_X
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:ScrWidth-APPENDLAYER_W
-APPENDLAYER_Y
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:0
-APPENDLAYER_W
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:8*10
-APPENDLAYER_H
--Description:

--Platform:
--Parent:APPENDLAYER_EN
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:40
-CANVASBASIC_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
+conf_UI.h
-UI_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-TESTBROWSER_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-UIBUTTON_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-UICANVAS_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
-UILABEL_EN
--Description:

--Platform:
--Parent:
--Disabled:
--Enable:
--Set:
--SetValue:
--Value:1
