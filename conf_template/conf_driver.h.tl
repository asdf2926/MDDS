+conf_driver.h
-CONF_EXT_H_
--Description:
--Parent:ndef
--Value:
-SSPI_EN
--Description:
--Parent:ndef
--Value:0
-SSPI_CK
--Description:SCK引脚，为GPIOx,PINx的二元组
--Parent:SSPI_EN
--Value:GPIOA,PIN4
-SSPI_MOSI
--Description:MOSI引脚，为GPIOx,PINx的二元组
--Parent:SSPI_EN
--Value:GPIOA,PIN2
-LCD_EN
--Description:
--Value:1
-LCD_DRIVER
--Description:LCD接口驱动，取值有HSPI和SSPI
--Parent:LCD_EN
--Value:HSPI
-LCD_INTR_EN
--Description:LCD数据传输由中断控制
--Parent:LCD_EN
--Value:0
-LCD_DMA_EN
--Description:
--Parent:LCD_EN
--Value:0
-LCD_BUF_SIZE
--Description:LCD缓冲区大小，仅在中断模式时有效
--Parent:LCD_EN
--Value:40
-LCD_RST_PIN
--Description:RST引脚号，为GPIOx,PINx的二元组
--Parent:LCD_EN
--Value:GPIOB,PIN0
-LCD_CS_PIN
--Description:CS引脚号，为GPIOx,PINx的二元组
--Parent:LCD_EN
--Value:GPIOB,PIN1
-LCD_A0_PIN
--Description:A0引脚号，为GPIOx,PINx的二元组
--Parent:LCD_EN
--Value:GPIOA,PIN4
-LCD_INIT_FILL_DATA
--Description:
--Parent:LCD_EN
--Value:0x55
-LCD_BUFFER_EN
--Description:启用LCD全屏刷新模式；缓冲区1KB由用户定义
--Parent:LCD_EN
--Value:1
-TCA6416A_EN
--Description:
--Value:0
-TCA6416A_INTERFACE
--Description:IIC only
--Parent:TCA6416A_EN
--Value:IIC
-TCA6416A_PORT_0_DIR
--Description:
--Parent:TCA6416A_EN
--Value:0
-TCA6416A_PORT_1_DIR
--Description:
--Parent:TCA6416A_EN
--Value:0x0f
-TCA6416A_PORT_0_OUT
--Description:
--Parent:TCA6416A_EN
--Value:0xaa
-TCA6416A_PORT_1_OUT
--Description:
--Parent:TCA6416A_EN
--Value:0xff
-HT1621_EN
--Description:
--Value:0
-HT1621_INTERFACE
--Description:
--Parent:HT1621_EN
--Value:GPIO
-HT1621_CS_PIN
--Description:
--Parent:HT1621_EN
--Value:GPIOB,PIN0
-HT1621_RD_PIN
--Description:not necessary,always 1
--Parent:HT1621_EN
--Value:GPIOB,PIN5
-HT1621_WR_PIN
--Description:
--Parent:HT1621_EN
--Value:GPIOB,PIN1
-HT1621_DATA_PIN
--Description:
--Parent:HT1621_EN
--Value:GPIOA,PIN4
-SegLCD_G2_EN
--Description:
--Parent:HT1621_EN
--Value:0
-DAC8411_EN
--Description:
--Value:0
-SYNC_HIGH
--Description:
--Parent:DAC8411_EN
--Value:P1OUT
-SYNC_LOW
--Description:
--Parent:DAC8411_EN
--Value:P1OUT
-SCLK_HIGH
--Description:
--Parent:DAC8411_EN
--Value:P2OUT
-SCLK_LOW
--Description:
--Parent:DAC8411_EN
--Value:P2OUT
-DIN_HIGH
--Description:
--Parent:DAC8411_EN
--Value:P1OUT
-DIN_LOW
--Description:
--Parent:DAC8411_EN
--Value:P1OUT
-G2PLATFORM
--Description:
--Value:0
-TFT_EN
--Description:
--Value:1
-TFT_INIT_COLOR
--Description:
--Parent:TFT_EN
--Value:LIGHTBLUE
-LTDC_EN
--Description:
--Value:1
-LTDC_TYPE
--Description:
--Parent:LTDC_EN
--Value:0x4342
-LCD_PIXFORMAT
--Description:
--Parent:LTDC_EN
--Value:LCD_PIXEL_FORMAT_RGB565
-LCD_FRAME_BUF_ADDR
--Description:
--Parent:LTDC_EN
--Value:0XC0000000
-FONT_EN
--Description:
--Value:0
-SDRAM_EN
--Description:
--Value:1
-GT9147_EN
--Description:
--Value:1
-TFT_ILI9341_EN
--Description:
--Value:1
