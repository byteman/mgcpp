#ifndef DTCOMMCTRL_H
#define DTCOMMCTRL_H
#include "dt_ctrl.h"

typedef struct tag_COMMCTRL_DESC{
    int x,y,w,h;
    char* caption;
}COMM_CTRL_DESC;

class CCommCtrl:public CCtrl
{
public:
    CCommCtrl();
    CCommCtrl(CTRLDATA* data,CSkinForm* parent,string typeName="CommCtrl");
    virtual ~CCommCtrl();
    void SetParam(CTRLDATA* data,CSkinForm* parent,string typeName);
protected:
    //CSkinForm* _parent;
    CTRLDATA*  _data;
    COMM_CTRL_DESC* _desc;
    bool        _alloc_desc;
};

#endif // DTCOMMCTRL_H
