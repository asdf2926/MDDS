#ifndef UICANVAS_H
#define UICANVAS_H
#if UICANVAS_EN>0
typedef struct{
    INT8U PenSize;
    Color BackColor;
    Color PenColor;
    INT16U lx;
    INT16U ly;
} UICanvasData;
void UICanvasEventHandler(UIData* ui,const Event *e);
#endif
#endif
