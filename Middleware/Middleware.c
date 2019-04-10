#include "includes.h"



void MiddlewareInit()

{

	#if GUI_EN>0

	GUIInit();

	#endif

	#if ABUTTON_EN>0
	AButtonInit();
	
	#endif
    #if APPE_EN>0
    AppEInit();
    AButtonCallBackSet(AppEAButtonCallBack);
    #endif
}



