#include "includes.h"
//---------------------------math-------------------------------
#if BASE64_EN>0
#include "Math/base64.c"
#endif
#if SHA3_EN>0
#include "Math/sha3.c"
#endif
#if TIME_EN>0
#include "Math/time.c"
#endif
#include "Math/Distance.c"
//---------------------------middleware-------------------------
#include "Middleware/Middleware.c"
#if ABUTTON_EN>0
#include "Middleware/AbstractButton.c"
#endif
#if GUI_EN>0
#include "Middleware/GUI.c"
#endif
//#if >0
//#include "Middleware/.c"
//#endif
#if 0
#include "Middleware/Stream.c"
#endif
#if APPE_EN>0
#include "Middleware/AppE.c"
#endif
#if SCR_EN>0
#include "Middleware/ScreanAbstract.c"
#endif
#if AINPUT2D_EN>0
#include "Middleware/Abstract2DInput.c"
#endif
#if AVARIABLE_EN>0
#include "Middleware/AbstractVariable.c"
#endif
//--------------------------diver------------------------------
#include "Driver/Driver.c"
#if DAC8411_EN>0
#include "Driver/DAC8411.c"
#endif
#if FONT_EN>0
#include "Driver/font0816.c"
#endif
#if G2PLATFORM>0
#include "Driver/G2Platform.c"
#endif
#if HT1621_EN>0
#include "Driver/HT1621.c"
#endif
#if LCD_EN>0
#include "Driver/LX_12864.c"
#endif
#if SegLCD_G2_EN>0
#include "Driver/SegLCD_G2.c"
#endif
#if SSPI_EN>0
#include "Driver/SSPI.c"
#endif
#if TCA6416A_EN>0
#include "Driver/TCA6416A.c"
#endif
#if TFT_EN>0
#include "Driver/TFT.c"
#endif
#if LTDC_EN>0
#include "Driver/TFT_LTDC.c"
#endif
#if SDRAM_EN>0
#include "Driver/SDRAM.c"
#endif
#if GT9147_EN>0
#include "Driver/GT9147.c"
#endif
//--------------------------SOCDriver-------------------------
#include "MDDS_STM32/Adapter.c"
//--------------------------Application-----------------------
#if APP_MENU_EN>0
#include "Application/menu.c"
#endif
#if APP_LAUNCHER_EN>0
#include "Application/Launcher.c"
#endif
#if TIMESET_EN>0
#include "Application/TimeSet.c"
#endif
#if CANVASBASIC_EN>0
#include "Application/CanvasBasic.c"
#endif
#if APPENDLAYER_EN>0
#include "Application/AppendLayer.c"
#endif
//--------------------------UI--------------------------------
#if UI_EN>0
#include "UI/UI.c"
#if TESTBROWSER_EN>0
#include "UI/TextBrowser.c"
#endif
#if UIBUTTON_EN>0
#include "UI/UIButton.c"
#endif
#if UICANVAS_EN>0
#include "UI/UICanvas.c"

#endif
#if UILABEL_EN>0
#include "UI/UILabel.c"

#endif
#endif
