#include "includes.h"



void MiddlewareInit()

{

	#if GUI_EN>0

	GUIInit();

	#endif
	#if BTIMER_COUNT>0
	BasicTimerInit();
	#endif
	#if ABUTTON_EN>0
	AButtonInit();
	
	#endif
	
	#if AINPUT2D_EN>0
	AInput2DInit();
	#endif
    #if APPE_EN>0
    AppEInit();
    AButtonCallBackSet(AppEAButtonCallBack);
    #endif
}



