#include "includes.h"

BL UIEventHandler(UIData d[],const Event *e)
{
	BL Flag=0;
    while(d->EventHandler)
    {
        if(e->Type==EVENT_CREATE)d->TrackId=-1;
        if(d->TrackId!=-1)
        {
            //if(AInput2DAvailable[d->TrackId]==0)
            //else 
            if(e->Type==EVENT_INPUT_2D)
            {
				((AInput2D *)e->ExternData)->x-=d->x;
				((AInput2D *)e->ExternData)->y-=d->y;
                (*(d->EventHandler))(d,e);
                return 1;
            }
        }
		if(e->Type==EVENT_INPUT_2D)
        {
            if( (d->x<=     ((AInput2D *)e->ExternData)->x)&&
                (d->y<=     ((AInput2D *)e->ExternData)->y)&&
                (d->x+d->w> ((AInput2D *)e->ExternData)->x)&&
                (d->y+d->h> ((AInput2D *)e->ExternData)->y))
            {
                d->TrackId=((AInput2D *)e->ExternData)->index;
				((AInput2D *)e->ExternData)->x-=d->x;
				((AInput2D *)e->ExternData)->y-=d->y;
                (*(d->EventHandler))(d,e);
                return 1;
            }
        }else{
            (*(d->EventHandler))(d,e);
            Flag=1;
        }
        
         d+=1;
    }
	return Flag;
}
