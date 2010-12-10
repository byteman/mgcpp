#ifndef DTEDIT_H
#define DTEDIT_H
#include "dt_commctrl.h"
#define MAX_TEXT_LENGTH 256

#define DEF_EDIT_EXSTYLE WS_EX_TRANSPARENT
#define DEF_EDIT_STYLE   WS_VISIBLE| WS_GROUP
class CEdit:public CCommCtrl
{
public:
    CEdit(CTRLDATA* data,CSkinForm* parent,string typeName=CTRL_EDIT);
    CEdit(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName=CTRL_EDIT);
    virtual ~CEdit();
    void SetTextAligned(int aligned);
    void EnablePassword(bool yes);
    void EnableUpperCase(bool yes);
    void EnableLowerCase(bool yes);
    void EnableReadOnly(bool yes);
    std::string  GetSelText();
    void SelectAllText();
    void CopySelectText();
    void CutSelectText();
    void SetFontSize(int size);
    void SetLineHeight(int val);
    int  GetLineHeight();
    void SetText(std::string strText);
    std::string GetText();
    void SetLimitLength(int length);
    int  GetLimitLength();
    void EnableDecimal(bool yes);
    void EnableDigtal(bool yes);
    void Redo();
    void SetPasswordChar(char ch);
private:
    char _buf[MAX_TEXT_LENGTH];

		
};

#endif // DTEDIT_H
