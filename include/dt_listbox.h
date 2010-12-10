#ifndef CLISTBOX_H
#define CLISTBOX_H

#include "dt_commctrl.h"


#define DEF_LBX_STYLE  WS_VISIBLE|WS_VSCROLL|WS_BORDER|LBS_SORT|LBS_AUTOCHECKBOX|LBS_USEICON|LBS_NOTIFY
#define DEF_LBX_EXSTYLE WS_EX_TRANSPARENT
typedef vector<int> ItemsList;
class CListBox:public CCommCtrl
{
public:
    CListBox(CTRLDATA* data,CSkinForm* parent,string typeName = CTRL_LISTBOX);
    CListBox(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName=CTRL_LISTBOX);
    virtual ~CListBox();
    void AddItem(std::string itemText,std::string icon="");
    void InsertItem(int index,std::string itemText,std::string icon="");
    void DelItem(int index);
    void Clear();
    int  TotalCounts();
    int  GetSelCounts();
    std::string GetItemText(int index);
    std::string GetText();
    void SetItemText(int index, std::string text);
    void SetCurSel(int index);
    int  GetCurSel();
    void SetSel(int index, bool selected);
    bool GetSel(int index);
    int  GetSelItems(ItemsList& items);
    int  FindItemByText(std::string text,bool exact);
    void SetItemWidth(int val);
    void SetItemHeight(int val);
    void MoveUp(bool up);
    bool GetItemSize(int &width,int &height);
private:   
    void _AddItem(int index,std::string itemText,std::string icon="");
    std::string _strText;

    //ItemsList selItemList;
};

#endif // CLISTBOX_H
