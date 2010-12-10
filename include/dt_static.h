#ifndef DTSTATIC_H
#define DTSTATIC_H

#include "dt_commctrl.h"
#define DEF_STATIC_STYLE    SS_CENTER | SS_NOTIFY | WS_VISIBLE
#define DEF_STATIC_EXSTYLE  WS_EX_TRANSPARENT
class CStatic:public CCommCtrl
{
public:
    CStatic(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName=CTRL_STATIC);
    CStatic(CTRLDATA* data,CSkinForm* parent,string typeName=CTRL_STATIC);
    virtual ~CStatic();
    void SetText(string strText);
    string& GetText();
    bool  SetFontSize(int size);
private:
    string _strText;
    PLOGFONT _font;
};

#endif // DTSTATIC_H
