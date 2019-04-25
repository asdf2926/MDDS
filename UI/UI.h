#ifndef _UI_H
#define _UI_H
#if UI_EN>0
typedef struct s_UIData{
    void (*EventHandler)(struct s_UIData*,const Event*);
    INT16U x;INT16U y;
    INT16U w;INT16U h;
    void *ExtData;
    INT8S TrackId;
} UIData;




BL UIEventHandler(UIData d[],const Event *e);
#endif
#endif
