#ifndef CLISTVIEW_H
#define CLISTVIEW_H
/*
 目前一个界面只能支持一个ListView控件
*/
#include "dt_commctrl.h"
#include "dt_icon.h"

#define DEF_LISTVIEW_STYLE 	  WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_BORDER
#define DEF_COLFLAG               LVCF_LEFTALIGN
#define DEF_LISTVIEW_EXSTYLE      WS_EX_TRANSPARENT
typedef vector<std::string>  StringList;
enum SORT_TYPE{
    SORT_ALPHA,
    SORT_NUM
};

class CListView:public CCommCtrl
{
public:
    CListView(CTRLDATA* data,CSkinForm* parent,string typeName = CTRL_LISTVIEW);
    CListView(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName=CTRL_LISTVIEW);
    virtual ~CListView();
    int AddColumn(int index=0,std::string itemText="null",int width=50);
    void DelColumn(int index);
    void SetColWidth(int index, int width);
    void SetColHeight(int height);
    void SetColHeadText(int index, std::string itemText);
    std::string  GetColHeaderText(int idx);
    int  GetColWidth(int index);
    int  GetColNum();
    void ex_listview_draw_item(HWND hwnd, int idx, HDC hdc , RECT *rcDraw);
    void ex_listview_draw_bk(HWND hwnd, HLVHDR hlvhdr, HDC hdc , RECT *rcDraw);

    //GHANDLE AddItems(StringList items,int itemHeight=25);
    GHANDLE AddRootItem(std::string root);
    GHANDLE AddSubItems(StringList subitems,int itemHeight=25,GHANDLE hRootItem=0);
    void Lock();
    void Unlock();
    void DelItem(int index);
    void Clear();
    void SelectRow(int row);
    int  GetItemNum();
    std::string GetSelSubItemText(int index);
    void SetSubItemText(int index, std::string text);  
    int  GetCurSelItem();
    void SetCustomDrawFunc(LVCUSTOMDRAWFUNCS* drawFuncs);
    bool EnableSkinStyle(bool yes);
    bool EnableTreeViewStyle(bool yes);
    int  GetSelCount();
    bool isSelected();
    void Show();
    void Hide();
    //bool SetSortType(SORT_TYPE type=SORT_NUM);
private:   
    GHANDLE  _AddItem(LVITEM& item,GHANDLE itemHwnd,int height);

    std::string _strText;
    StringList _headerStr;
    DWORD _colFlags;
    int		_colNum;
    CIcon bmpBk,bmpSplit;
    //ItemsList selItemList;
};

#endif // CLISTVIEW_H
