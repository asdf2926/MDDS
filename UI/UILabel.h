#ifndef UILABEL_H
#define UILABEL_H
#if UILABEL_EN>0
typedef struct{
    const char *Label;
    Color FontColor;
    BL AppendMode;
    Color BackColor;
} UILabelData;
void UILabelEventHandler(UIData* ui,const Event *e);
#endif
#endif
