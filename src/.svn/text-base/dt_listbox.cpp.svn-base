#include "dt_listbox.h"
#include <assert.h>
CListBox::CListBox(CTRLDATA* data,CSkinForm* parent,string typeName)
    :CCommCtrl(data,parent,typeName)
{

}
CListBox::CListBox(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName)
{
    CTRLDATA *data = new CTRLDATA();
    char* tmp = new char[strlen(desc->caption) + 1];
    memset(tmp,0,strlen(desc->caption) + 1);

    strcpy(tmp,desc->caption);
    data->caption = tmp;

    tmp = new char[typeName.size() + 1];
    memset(tmp,0,strlen(desc->caption) + 1);
    strcpy(tmp,typeName.c_str());

    data->class_name=tmp;
    data->dwAddData = 0;
    data->dwExStyle = DEF_LBX_EXSTYLE;
    data->dwStyle   = DEF_LBX_STYLE;
    data->id        = -1; //auto alloc id
    data->w         = desc->w;
    data->h         = desc->h;
    data->x         = desc->x;
    data->y         = desc->y;

    //std::cout << "b parent = " <<_parent << std::endl;
    SetParam(data,parent,typeName);
    //std::cout << "a parent = " <<_parent << std::endl;
    //std::cout << "CListView parent = " << &_parent << std::endl;
    _alloc_desc = true;
}
CListBox::~CListBox()
{

}
void CListBox::AddItem(std::string itemText,std::string icon)
{
    _AddItem(0,itemText,icon);
}
void CListBox::InsertItem(int index,std::string itemText,std::string icon)
{
    _AddItem(index,itemText,icon);
}
void CListBox::_AddItem(int index,std::string itemText,std::string icon)
{
    HICON hIcon  = 0;           /* 声明图标句柄 */
    LISTBOXITEMINFO lbii;   /* 声明列表框条目结构体变量 */
    if(icon != "")
    {
        hIcon = LoadIconFromFile (HDC_SCREEN, icon.c_str(), 1);  /* 加载图标 */
        fprintf(stderr,"hIcon = %x\n",hIcon);
    }

    /* 设定结构信息，并添加条目 */
    lbii.hIcon  = hIcon?hIcon:0;
    /*
        CMFLAG_PARTCHECKED      部分选中
        CMFLAG_CHECKED;         选中
        CMFLAG_BLANK            不选择
        IMGFLAG_BITMAP          可以选择位图,不用icon
    */
    lbii.cmFlag = CMFLAG_BLANK;
    lbii.string = (char*)itemText.c_str();
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        //std::cout <<"id = " <<_id <<std::endl;
        SendDlgItemMessage (_parent->m_hWnd, _id, LB_ADDSTRING, index, (LPARAM)&lbii);
    }
}
void CListBox::DelItem(int index)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_DELETESTRING, index, 0);
    }
}
void CListBox::Clear()
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_RESETCONTENT, 0, 0);
    }
}

int  CListBox::TotalCounts()
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        return SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETCOUNT, 0, 0);
    }
    return -1;

}
int  CListBox::GetSelCounts()
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        return SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETSELCOUNT, 0, 0);
    }
    return -1;
}
std::string CListBox::GetItemText(int index)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        _strText = "";
        int textLen = SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETTEXTLEN, index, 0);
        // cout<<"textLen"<<textLen<<endl;
        if(textLen > 0)
        {
            cout<<"textLen"<<textLen<<endl;
            char* textPtr = new char[textLen + 1];
            memset(textPtr, 0, textLen + 1);
            if(textPtr)
            {
                SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETTEXT, index, (LPARAM)textPtr);
                _strText = textPtr;
                delete []textPtr;
            }
            //_strText.reserve(textLen+2);

            //cout<<"txt"<<_strText<<endl;
        }

    }
    return _strText;
}
std::string CListBox::GetText()
{
    int idx = GetCurSel();
    return GetItemText(idx);

}
void CListBox::SetItemText(int index, std::string text)
{

    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_SETTEXT, index, (LPARAM)text.c_str());
    }
}
void CListBox::SetCurSel(int index)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_SETCURSEL, index, 0);
    }
}
int  CListBox::GetCurSel()
{
    int ret = 0;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        int index = SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETCURSEL, 0, 0);
        if(LB_ERR == index)
            ret = -1;
        else
            ret = index;
    }
    return ret;
}
void CListBox::SetSel(int index, bool selected)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_SETSEL, (WPARAM)selected, (LPARAM)index);
    }

}
bool CListBox::GetSel(int index)
{
    int ret = 0;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        ret = SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETSEL, (WPARAM)index, (LPARAM)0);
    }
    return (ret != 0);
}
int  CListBox::GetSelItems(ItemsList& items)
{
    int sel_count = 0;
    items.clear();
    if(( sel_count = GetSelCounts()) > 0)
    {
        int *sel_items = (int*)alloca (sizeof(int)*sel_count);
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETSELITEMS, (WPARAM)sel_count, (LPARAM)sel_items);
        for(int i = 0; i < sel_count; i++)
        {
            items.push_back(sel_items[i]);
        }
    }
    return sel_count;
}
int  CListBox::FindItemByText(std::string text,bool exact)
{
    int msg = exact?LB_FINDSTRINGEXACT:LB_FINDSTRING;
    int ret = 0;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        ret = SendDlgItemMessage (_parent->m_hWnd, _data->id, msg, 0, (LPARAM)text.c_str());
        if(ret == LB_ERR)
        {
            ret = -1;
        }
    }
    return ret;
}

void CListBox::SetItemWidth(int val)
{

}
void CListBox::SetItemHeight(int val)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
         SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_SETITEMHEIGHT, 0, val);
    }
}
bool CListBox::GetItemSize(int &width,int &height)
{

            ;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        height = SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_GETITEMHEIGHT, 0, height);
        width  = 0;
        return true;
    }

    return false;
}
void CListBox::MoveUp(bool up)
{
    if(_parent)
    {
        if(up){
            SendDlgItemMessage(_parent->m_hWnd,_data->id,MSG_KEYDOWN,MAKELONG(SCANCODE_CURSORBLOCKUP,0),0);
        }else
            SendDlgItemMessage(_parent->m_hWnd,_data->id,MSG_KEYDOWN,MAKELONG(SCANCODE_CURSORBLOCKDOWN,0),0);
    }
}
