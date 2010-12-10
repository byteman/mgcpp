#ifndef DT_BUTTON_H
#define DT_BUTTON_H
#include "dt_commctrl.h"
class CButton : public CCommCtrl
{
public:
    CButton(CTRLDATA* data,CSkinForm* parent,string typeName=CTRL_BUTTON);
    virtual ~CButton();

};

#endif // DT_BUTTON_H
