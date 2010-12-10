#ifndef DT_SKINLABLE_H
#define DT_SKINLABLE_H
#include "dt_skinctrl.h"

class CSkinLable : public CSkinCtrl
{
public:   
    //CSkinLable(skin_item_t* data, CSkinForm* parent,string typeName=SKIN_BUTTON);
    //CSkinLable(SKIN_CTRL_DESC* desc, CSkinForm* parent,string typeName=SKIN_BUTTON);
    CSkinLable(int bmpindex,SKIN_CTRL_DESC* desc, CSkinForm* parent,string typeName="skin_lable");
    virtual ~CSkinLable();
    void Display(std::string strText);
};

#endif // DT_SKINLABLE_H
