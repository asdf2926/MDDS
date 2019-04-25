#ifndef UIBUTTON_H
#define UIBUTTON_H
#if UIBUTTON_EN>0
typedef struct{
    const char *Label;
    Color FontColor;
    Color BackColor;
    Color PressColor;
    void (*CallBack)(UIData*);
} UIButtonData;
void UIButtonEventHandler(UIData* ui,const Event *e);
#endif
#endif
