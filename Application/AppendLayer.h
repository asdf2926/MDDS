#ifndef _APPENDLAYER_H
#define _APPENDLAYER_H
#if APPENDLAYER_EN>0
typedef struct{
    const char*StringBuffer;

}AppendLayerData;
extern AppE AppAppendLayer;
BL AEAppendLayerEventHandler(struct s_AppE *app,const Event * e);

#endif
#endif
