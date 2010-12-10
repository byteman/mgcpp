#ifndef DT_SKINCHKBUTTON_H
#define DT_SKINCHKBUTTON_H
#include "dt_skinctrl.h"


typedef  SKIN_CTRL_DESC SKIN_CHECK_DESC;

#define SKIN_CHK_BUTTON "SKIN_CHK_BUTTON"
class CSkinChkButton:public CSkinCtrl
{
public:
    CSkinChkButton(skin_item_t* data, CSkinForm* parent,string typeName=SKIN_CHK_BUTTON);
    CSkinChkButton(SKIN_CHECK_DESC* desc, CSkinForm* parent,string typeName=SKIN_CHK_BUTTON);
    CSkinChkButton(int bmpindex,SKIN_CHECK_DESC* desc, CSkinForm* parent,string typeName=SKIN_CHK_BUTTON);
    virtual ~CSkinChkButton();
    bool GetCheckStatus();
    void SetCheckStatus(bool check);

};

#endif // DT_SKINBUTTON_H
