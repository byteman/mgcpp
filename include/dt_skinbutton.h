#ifndef DT_SKINBUTTON_H
#define DT_SKINBUTTON_H
#include "dt_skinctrl.h"


typedef  SKIN_CTRL_DESC SKIN_BUTTON_DESC;

#define SKIN_BUTTON "SKIN_BUTTON"
class CSkinButton:public CSkinCtrl
{
public:
    CSkinButton(skin_item_t* data, CSkinForm* parent,string typeName=SKIN_BUTTON);
    CSkinButton(SKIN_BUTTON_DESC* desc, CSkinForm* parent,string typeName=SKIN_BUTTON);
    CSkinButton(int bmpindex,SKIN_BUTTON_DESC* desc, CSkinForm* parent,string typeName=SKIN_BUTTON);
    bool GetCheckStatus();
    virtual ~CSkinButton();


};

#endif // DT_SKINBUTTON_H
