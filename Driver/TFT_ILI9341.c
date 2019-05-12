#include "includes.h"
#if TFT_ILI9341_EN>0
//========================================================
void LCD_WriteCommand(INT8U c) {
	int i;
	D_C_L;
	CS_L;
	for (i = 0; i < 8; i++) {
		if (c & 0x80) {
			SDA_H;
		} else
			SDA_L;
		SCL_L;
		SCL_H;
		c <<= 1;
	}

	CS_H;
}

//========================================================

void LCD_WriteData(INT8U dat) {
	int i;
	D_C_H;
	CS_L;
	for (i = 0; i < 8; i++) {
		if (dat & 0x80) {
			SDA_H;
		} else
			SDA_L;
		SCL_L;
		SCL_H;
		dat <<= 1;
	}

	CS_H;
}
//========================================================
void LCD_Write_Data(INT16U dat16) {
	LCD_WriteData(dat16 >> 8);
	LCD_WriteData(dat16);
}

void LCD_Write_Data1(INT8U dat1, INT8U dat2) {
	int i, j;
	D_C_H;
	CS_L;
	for (i = 0; i < 8; i++) {
		if (dat1 & 0x80) {
			SDA_H;
		} else
			SDA_L;
		SCL_L;
		SCL_H;
		dat1 <<= 1;
	}
	CS_H;

	CS_L;
	for (j = 0; j < 8; j++) {
		if (dat2 & 0x80) {
			SDA_H;
		} else
			SDA_L;
		SCL_L;
		SCL_H;
		dat2 <<= 1;
	}
	CS_H;

}
void Draw_Pos_Size(int x, int y, int width, int height)
{

	LCD_WriteCommand(0x2A);
	LCD_WriteData(x >>8);		//X 起点位置
	LCD_WriteData(x &0xff);
	LCD_WriteData((x +  width) >>8);		//X 终点位置
	LCD_WriteData((x +  width) &0xff);

	LCD_WriteCommand(0x2B);
	LCD_WriteData(y >>8);
	LCD_WriteData(y &0xff);
	LCD_WriteData((y + height) >>8);
	LCD_WriteData((y + height) &0xff);

}
void TFT_DrawPoint(INT16U x,INT16U y,Color c)
{
    Draw_Pos_Size(x,y,1,1);
	LCD_WriteCommand(0x2C);
    LCD_Write_Data(c);
}
void ILI9341_INITIAL() {

	RES_H;
	delay_10us(20);
	RES_L;
	delay_10us(100);
	RES_H;
	delay_10us(10);
	//SDA=0;
	//  SCL=0;
	delay_10us(40);

	// 初始化输出
	//P1DIR |= PIN3 + PIN2;
	P4DIR |= PIN3 + PIN0;
	P3DIR |= PIN7;
	P8DIR &= ~PIN2;
	P2DIR |= PIN3;
	P8DIR |= PIN1;

//------------------------------------ST7735R Reset Sequence-----------------------------------------//
	RES_H;
	delay_10us(100);                                                     //Delay 1ms
	RES_L;
	delay_10us(200);                                                     //Delay 1ms
	RES_H;
	delay_10us(200);                                                   //Delay 120ms

//************* Start Initial Sequence **********//
	LCD_WriteCommand(0xCF);
	LCD_WriteData(0x00);
	LCD_WriteData(0xC1);
	LCD_WriteData(0X30);

	LCD_WriteCommand(0xED);
	LCD_WriteData(0x64);
	LCD_WriteData(0x03);
	LCD_WriteData(0X12);
	LCD_WriteData(0X81);

	LCD_WriteCommand(0xE8);
	LCD_WriteData(0x85);
	LCD_WriteData(0x10);
	LCD_WriteData(0x7A);

	LCD_WriteCommand(0xCB);
	LCD_WriteData(0x39);
	LCD_WriteData(0x2C);
	LCD_WriteData(0x00);
	LCD_WriteData(0x34);
	LCD_WriteData(0x02);

	LCD_WriteCommand(0xF7);
	LCD_WriteData(0x20);

	LCD_WriteCommand(0xEA);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);

	LCD_WriteCommand(0xC0);    //Power control
	LCD_WriteData(0x21);   //VRH[5:0]

	LCD_WriteCommand(0xC1);    //Power control
	LCD_WriteData(0x13);   //SAP[2:0];BT[3:0]

	LCD_WriteCommand(0xC5);    //VCM control
	LCD_WriteData(0x3F);
	LCD_WriteData(0x3C);

	LCD_WriteCommand(0xC7);    //VCM control2
	LCD_WriteData(0XB3); //Лђеп B1h

	LCD_WriteCommand(0x36);    // Memory Access Control
	LCD_WriteData(0x08);

	LCD_WriteCommand(0x3A);
	LCD_WriteData(0x55);

	LCD_WriteCommand(0xB1);
	LCD_WriteData(0x00);
	LCD_WriteData(0x1B);

	LCD_WriteCommand(0xB6);    // Display Function Control
	LCD_WriteData(0x0A);
	LCD_WriteData(0xA2);

	LCD_WriteCommand(0xF6);
	LCD_WriteData(0x01);
	LCD_WriteData(0x30);

	LCD_WriteCommand(0xF2);    // 3Gamma Function Disable
	LCD_WriteData(0x00);

	LCD_WriteCommand(0x26);    //Gamma curve selected
	LCD_WriteData(0x01);

	LCD_WriteCommand(0xE0);    //Set Gamma
	LCD_WriteData(0x0F);
	LCD_WriteData(0x24);
	LCD_WriteData(0x21);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x09);
	LCD_WriteData(0x4D);
	LCD_WriteData(0XB8);
	LCD_WriteData(0x3C);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x13);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x05);
	LCD_WriteData(0x00);

	LCD_WriteCommand(0XE1);    //Set Gamma
	LCD_WriteData(0x00);
	LCD_WriteData(0x1B);
	LCD_WriteData(0x1E);
	LCD_WriteData(0x03);
	LCD_WriteData(0x10);
	LCD_WriteData(0x06);
	LCD_WriteData(0x32);
	LCD_WriteData(0x47);
	LCD_WriteData(0x43);
	LCD_WriteData(0x05);
	LCD_WriteData(0x0C);
	LCD_WriteData(0x0B);
	LCD_WriteData(0x35);
	LCD_WriteData(0x3A);
	LCD_WriteData(0x0F);

	LCD_WriteCommand(0x11);    //Exit Sleep
	delay_10us(120);
	LCD_WriteCommand(0x29);    //Display on
}

#endif
