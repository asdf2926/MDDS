#ifndef _ABSTRACT2DINPUT_H
#define _ABSTRACT2DINPUT_H
#if AINPUT2D_EN>0
enum e_Input2DType{
    Input2DNone=0,
    Input2DDown,
    Input2DUp,
    Input2DMoveStart,
    Input2DMove,
    Input2DHold,
    Input2DZoom,
    Input2DMulti
};

typedef struct{
    INT16S x;
    INT16S y;
    INT16S vx;//poi/s
    INT16S vy;//poi/s
    float zoom;
    INT16U TimeMs;
    INT8U index;
    enum e_Input2DType Status;
} AInput2D;

extern INT16U AInput2DInput[AINPUT2D_POINT_COUNT][2];
extern INT8U AInput2DAvailable[AINPUT2D_POINT_COUNT];

void AInput2DInit(void);
//AInput2D AInput2DGet(void );
//void AInput2DCallBackSet(void (*pCallBack)(AInput2D));
void AInput2DCallBack(AInput2D d);
void AInput2DProcess_10ms(INT8U);
void AInput2DRefreshHook(void);
#endif
#endif
