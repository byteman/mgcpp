#ifndef DT_COMBOX_H
#define DT_COMBOX_H
#include "dt_commctrl.h"
#define DEF_COMBOX_EXSTYLE  WS_EX_TRANSPARENT
#define DEF_COMBOX_STYLE    WS_TABSTOP|WS_VISIBLE|CBS_DROPDOWNLIST|CBS_NOTIFY|CBS_UPPERCASE
class CComBox : public CCommCtrl
{
public:
    CComBox(CTRLDATA* data,CSkinForm* parent,string typeName=CTRL_COMBOBOX);
    CComBox(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName=CTRL_COMBOBOX);
    virtual ~CComBox();
    void AddItem(std::string itemText,std::string icon="");
    void InsertItem(int index,std::string itemText,std::string icon="");
    void DelItem(int index);
    void DelItem(std::string text);
    void Clear();
    int  TotalCounts();
    int  GetSelCounts();
    void EnableTransparent();
    std::string GetItemText(int index);
    std::string GetSelItemText();
    void SetItemText(int index, std::string text);
    void SetText(std::string text);
    void SetCurSel(int index);
    int  GetCurSel();
    void SetSel(int index, bool selected);
    bool GetSel(int index);
    int  FindItemByText(std::string text,int start,bool exact=false);
    bool IsDrapDown();
    void ReadOnly(bool yes);
    void EditorReadOnly(bool yes);
    void Enable(bool yes);
private:
    std::string _strText;
};

#endif // DT_COMBOX_H
