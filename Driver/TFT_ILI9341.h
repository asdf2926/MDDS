#if TFT_ILI9341_EN>0
//#define		RES = P3^5;
#define		RES_H 	P2OUT |= BIT3
#define 	RES_L	P2OUT &= ~BIT3

//#define		SCL = P3^7;
#define		SCL_H 	P8OUT |= BIT1
#define 	SCL_L	P8OUT &= ~BIT1

//A0
#define		D_C_H 	P4OUT |= BIT3
#define 	D_C_L	P4OUT &= ~BIT3

//#define		CSB = P3^4;
#define		CS_H 	P4OUT |= BIT0
#define 	CS_L	P4OUT &= ~BIT0

//#define		SDA = P3^6;
#define		SDA_H 	P3OUT |= BIT7
#define 	SDA_L	P3OUT &= ~BIT7

#define LCD_MAX_HEIGHT 320
#define LCD_MAX_WIDTH  240

void ILI9341_INITIAL();
void Draw_Pos_Size(int x, int y, int width, int height);

#endif
