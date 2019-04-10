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
//--------------------------diver------------------------------
#include "Driver/Driver.c"
#if DAC8411_EN>0
#include "Driver/DAC8411.c"
#endif
#if TFT_EN+LCD_EN>0
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

