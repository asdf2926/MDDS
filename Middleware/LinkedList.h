#ifndef _LINKEDLIST_H

#define _LINKEDLIST_H

#define LINKLIST_MAKE(STRUCT_NAME) struct STRUCT_NAME *p##STRUCT_NAME##First,*p##STRUCT_NAME##Last;

#define LINKLIST_STRUCT(STRUCT_NAME) struct STRUCT_NAME *Prev;\
    struct STRUCT_NAME *Next;

#define LINKLIST_ADD_FIRST(STRUCT_NAME,DATA) \
    if(p##STRUCT_NAME##First)   \
    {                       \
        p##STRUCT_NAME##First->Prev=DATA;   \
        DATA->Next=p##STRUCT_NAME##First;         \
    }else{                  \
        DATA->Next=NULL;          \
    }                       \
    DATA->Prev=NULL;              \
    p##STRUCT_NAME##First=DATA;             \
    if(p##STRUCT_NAME##Last==NULL)p##STRUCT_NAME##Last=DATA;

#define LINKLIST_INSERT_FRONT(STRUCT_NAME,DATA,POS) \
    if(p##STRUCT_NAME##First==POS)   \
    {                       \
        LINKLIST_ADD_FIRST(STRUCT_NAME,DATA)\
    }else{                  \
        DATA->Next=POS;          \
        DATA->Prev=POS->Prev;\
        POS->Prev->Next=DATA;\
        POS->Prev=DATA;\
    }                       



#define LINKLIST_REMOVE(STRUCT_NAME,DATA) \
    if(DATA->Prev)                      \
    {\
        if(DATA->Next)\
        {\
            DATA->Prev->Next=DATA->Next;\
            DATA->Next->Prev=DATA->Prev;\
        }else\
        {\
            DATA->Prev->Next=NULL;\
            p##STRUCT_NAME##Last=DATA->Prev;\
        }\
    }else{\
        if(DATA->Next)\
        {\
            p##STRUCT_NAME##First=DATA->Next;\
            DATA->Next->Prev=NULL;\
        }else\
            p##STRUCT_NAME##First=NULL;\
    }

#define LINKLIST_INIT(STRUCT_NAME) p##STRUCT_NAME##First=p##STRUCT_NAME##Last=NULL;

#define LINKLIST_FOREACH(VAL,STRUCT_NAME) for(VAL=p##STRUCT_NAME##First;VAL!=NULL;VAL=VAL->Next)

#define LINKLIST_FOREACH_BACK(VAL,STRUCT_NAME) for(VAL=p##STRUCT_NAME##Last;VAL!=NULL;VAL=VAL->Prev)

#define LINKLINTLOOP_INSERT_BACK(STRUCT_NAME,DATA,POS) \
    DATA->Next=POS->Next;\
    DATA->Prev=POS;\
    POS->Next->Prev=DATA;\
    POS->Next=DATA;

#define LINKLINTLOOP_INSERT_FRONT(STRUCT_NAME,DATA,POS) \
    DATA->Next=POS;\
    DATA->Prev=POS->Prev;\
    POS->Prev->Next=DATA;\
    POS->Prev=DATA;

#endif

		

