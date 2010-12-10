#ifndef DT_SKINCTRL_H
#define DT_SKINCTRL_H
#include "dt_ctrl.h"

typedef struct tag_SKINCTRL_DESC{
    int bmpindex;
    int left;
    int top;
    char* caption;
}SKIN_CTRL_DESC;

class CSkinCtrl : public CCtrl
{
public:
    CSkinCtrl(CSkinForm* parent,string typeName="SkinCtrl");
    CSkinCtrl(skin_item_t* data, CSkinForm* parent,string typeName);
    virtual void    Show();
    virtual void    Hide();
    virtual ~CSkinCtrl();

protected:
    skin_item_t*  _data;
};

#endif // DT_SKINCTRL_H
