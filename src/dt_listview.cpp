#include "dt_listview.h"
#include <assert.h>
static CListView* pMe;
CListView::CListView(CTRLDATA* data,CSkinForm* parent,string typeName)
    :CCommCtrl(data,parent,typeName)
{
    _colFlags = DEF_COLFLAG;
    _colNum = 0;
}
CListView::CListView(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName)
{

    _colFlags = DEF_COLFLAG;
    _colNum = 0;

    CTRLDATA *data = new CTRLDATA;

    char* tmp = new char[strlen(desc->caption) + 1];
    memset(tmp,0,strlen(desc->caption) + 1);

    strcpy(tmp,desc->caption);
    data->caption = tmp;

    tmp = new char[typeName.size() + 1];
    memset(tmp,0,strlen(desc->caption) + 1);
    strcpy(tmp,typeName.c_str());

    data->class_name=tmp;
    data->dwAddData = 0;
    data->dwExStyle = DEF_LISTVIEW_EXSTYLE;
    data->dwStyle   = DEF_LISTVIEW_STYLE;
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
CListView::~CListView()
{
    pMe = NULL;
}
int CListView::AddColumn(int index,std::string itemText,int width)
{
    LVCOLUMN lvcol;

    lvcol.nCols = index;
    lvcol.pszHeadText = (char*)itemText.c_str();
    lvcol.width = width;
    lvcol.pfnCompare = NULL;
    lvcol.colFlags = _colFlags;

    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        SendDlgItemMessage (_parent->m_hWnd, _id, LVM_ADDCOLUMN, 0, (LPARAM)&lvcol);
        _colNum++;
        _headerStr.push_back(itemText);
    }
    
}

void CListView::Show()
{
    ShowWindow(_parent->GetItemHwnd(_id), SW_SHOW);
}

void CListView::Hide()
{
    ShowWindow(_parent->GetItemHwnd(_id), SW_HIDE);
}

void CListView::SetColWidth(int index,int width)
{
    if(index <= _colNum)
    {
        if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
        {
            LVCOLUMN lvcol;
            //std::cout <<"id = " <<_id <<std::endl;
            SendDlgItemMessage (_parent->m_hWnd, _id, LVM_GETCOLUMN, index, (LPARAM)&lvcol);
            lvcol.width = width;
            SendDlgItemMessage (_parent->m_hWnd, _id, LVM_SETCOLUMN, index, (LPARAM)&lvcol);
        }


    }
}
void CListView::SetColHeight(int height)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        //std::cout <<"id = " <<_id <<std::endl;
        SendDlgItemMessage (_parent->m_hWnd, _id, LVM_SETHEADHEIGHT, (WPARAM)0, (LPARAM)0);

    }
}
void CListView::SetColHeadText(int index, std::string itemText)
{
    if(index <= _colNum)
    {
        if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
        {
            LVCOLUMN lvcol;
            //std::cout <<"id = " <<_id <<std::endl;
            SendDlgItemMessage (_parent->m_hWnd, _id, LVM_GETCOLUMN, index, (LPARAM)&lvcol);
            lvcol.pszHeadText = (char*)itemText.c_str();
            SendDlgItemMessage (_parent->m_hWnd, _id, LVM_SETCOLUMN, index, (LPARAM)&lvcol);
        }


    }
}
static char* _getColHeaderText(HWND hwnd,int idx)
{
    LVCOLUMN lvcol;
    if(hwnd == HWND_INVALID)
        return "hello";
    SendMessage (hwnd, LVM_GETCOLUMN, idx, (LPARAM)&lvcol);
    printf("%d,%s\n",idx,lvcol.pszHeadText);
    return lvcol.pszHeadText;
}
std::string  CListView::GetColHeaderText(int idx)
{
    /*
    if(idx <= _colNum)
    {
        if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
        {
            HWND h = GetDlgItem(_parent->m_hWnd,_id);
            return _getColHeaderText(h,idx);
        }


    }*/
    if(idx <= _colNum)
    {
        return _headerStr.at(idx);
    }
    return "";
}
int  CListView::GetColWidth(int index)
{
    int ret = 0;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        //std::cout <<"id = " <<_id <<std::endl;
        ret =  SendDlgItemMessage (_parent->m_hWnd, _id, LVM_GETCOLUMNWIDTH, (WPARAM)0, (LPARAM)0);
        assert(ret != -1);
    }
    return ret;
}

int  CListView::GetColNum()
{
    int ret = 0;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        //std::cout <<"id = " <<_id <<std::endl;
        ret =  SendDlgItemMessage (_parent->m_hWnd, _id, LVM_GETCOLUMNCOUNT, (WPARAM)0, (LPARAM)0);
        assert(ret != -1);
    }
    return ret;
}
//itemHwnd == root item hwnd
GHANDLE  CListView::_AddItem(LVITEM& item,GHANDLE itemHwnd,int height)
{

    item.nItemHeight = height;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        return SendDlgItemMessage (_parent->m_hWnd, _id, LVM_ADDITEM, (WPARAM)itemHwnd, (LPARAM)&item);

    }
    return HWND_INVALID;
}
GHANDLE CListView::AddRootItem(std::string root)
{
    StringList temp;
    temp.push_back(root);
    return AddSubItems(temp,25,0);
}
GHANDLE CListView::AddSubItems(StringList subitems,int itemHeight,GHANDLE hRootItem)
{
    LVITEM    item;
    LVSUBITEM subdata;
    Lock();

    GHANDLE hItem = _AddItem(item,hRootItem,itemHeight);

    assert(hItem != HWND_INVALID);
    static int index = 0;
    subdata.flags = 0;
    subdata.image = 0;
    subdata.nTextColor = RGB2Pixel(HDC_SCREEN,255,0,0);
    subdata.nItem   =  0;


    //printf("nItem = %d\n",subdata.nItem);
    subdata.nTextColor = 0;
    int num = (_colNum>subitems.size())?subitems.size():_colNum;
    for(int  i = 0 ; i < num; i++)
    {
        //subdata.nItem   =  i;
        subdata.subItem = i;
        //subdata.subItem = 0;
        subdata.pszText = (char*)subitems.at(i).c_str();
        SendDlgItemMessage (_parent->m_hWnd, _id, LVM_SETSUBITEM, (WPARAM)hItem, (LPARAM)&subdata);
    }

    Unlock();
    return hItem;
}
/*
GHANDLE CListView::AddItems(StringList items,int itemHeight)
{
    LVITEM    item;
    LVSUBITEM subdata;
    Lock();

    GHANDLE hItem = _AddItem(item,0,itemHeight);

    assert(hItem != HWND_INVALID);
    static int index = 0;
    subdata.flags = 0;
    subdata.image = 0;
    subdata.nTextColor = RGB2Pixel(HDC_SCREEN,0,0,0);
    subdata.nItem   =  0;


    //printf("nItem = %d\n",subdata.nItem);
    subdata.nTextColor = 0;
    int num = (_colNum>items.size())?items.size():_colNum;
    for(int  i = 0 ; i < num; i++)
    {
        //subdata.nItem   =  i;
        subdata.subItem = i;
        //subdata.subItem = 0;
        subdata.pszText = (char*)items.at(i).c_str();
        SendDlgItemMessage (_parent->m_hWnd, _id, LVM_SETSUBITEM, (WPARAM)hItem, (LPARAM)&subdata);
    }

    Unlock();
    return hItem;
}*/
void CListView::Lock()
{
    SendDlgItemMessage (_parent->m_hWnd, _id, MSG_FREEZECTRL, true,(LPARAM)0);
}	
void CListView::Unlock()
{
    SendDlgItemMessage (_parent->m_hWnd, _id, MSG_FREEZECTRL, FALSE,(LPARAM)0);
				
}	
void CListView::DelColumn(int index)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _id, LVM_DELCOLUMN, (WPARAM)index,0);
    }
}
 /*LVM_DELITEM
 * int nRow;
 * HLVITEM pi;
 *
 * wParam = (WPARAM)nRow;
 * lParam = (LPARAM)pi;
 * \endcode
 *
 * \param nRow If pi is zero, nRow specified the row index of the target item to delete.
 * \param pi Handle of the target item.
 */
void CListView::DelItem(int index)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _id, LVM_DELCOLUMN,index,0 );
    }
}
void CListView::Clear()
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LVM_DELALLITEM, 0, 0);
    }
}

int  CListView::GetItemNum()
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        return SendDlgItemMessage (_parent->m_hWnd, _data->id, LVM_GETITEMCOUNT, 0, 0);
    }
    return 0;
}
void CListView::SelectRow(int row)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LVM_CHOOSEITEM , row, 0);
    }
}
void CListView::SetSubItemText(int index, std::string text)
{
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
        SendDlgItemMessage (_parent->m_hWnd, _data->id, LB_SETTEXT, index, (LPARAM)text.c_str());
    }
}

int  CListView::GetCurSelItem()
{
    int ret = 0;
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {
    	
        int index = SendDlgItemMessage (_parent->m_hWnd, _data->id, LVM_GETSELECTEDCOLUMN , 0, 0);
       
        ret = index;
    }
    return ret;
}
int  CListView::GetSelCount()
{
    //fprintf(stderr,"_parent=%x,hwnd=%x\n",_parent,_parent->m_hWnd);
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        return SendDlgItemMessage (_parent->m_hWnd, _data->id, LVM_GETSELECTEDITEM  , 0, 0);
    }
    return 0;
}
bool  CListView::isSelected()
{
    //fprintf(stderr,"_parent=%x,hwnd=%x\n",_parent,_parent->m_hWnd);
    if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
    {

        return (SendDlgItemMessage (_parent->m_hWnd, _data->id, LVM_GETSELECTEDITEM  , 0, 0) != HWND_NULL);
    }
    return false;

}
std::string CListView::GetSelSubItemText(int index)
{
    if(_parent->m_hWnd)
    {
        HLVITEM hSelItem = SendDlgItemMessage(_parent->m_hWnd, _data->id, LVM_GETSELECTEDITEM, 0, 0);
        if (hSelItem != HWND_INVALID){
            LVSUBITEM subitem;
            char strBuf[256] = {0,};

            subitem.subItem = index;
            subitem.pszText = strBuf;
            if( -1 == SendDlgItemMessage(_parent->m_hWnd, _data->id,LVM_GETSUBITEMTEXT, hSelItem , (LPARAM)&subitem))
                return "";
            return strBuf;

        }
    }

    return "";
}
void CListView::SetCustomDrawFunc(LVCUSTOMDRAWFUNCS* drawFuncs)
{
    if(_parent->m_hWnd)
    {
        SendDlgItemMessage(_parent->m_hWnd, _data->id, LVM_SETCUSTOMDRAW, 0, (LPARAM)drawFuncs);
    }
}


void CListView::ex_listview_draw_bk(HWND hwnd, HLVHDR hlvhdr, HDC hdc , RECT *rcDraw)
{
    bmpBk.Show(hdc,rcDraw->left,rcDraw->top);
}
void listview_draw_bk(HWND hwnd, HLVHDR hlvhdr, HDC hdc , RECT *rcDraw)
{
    if(pMe)
        pMe->ex_listview_draw_bk(hwnd,hlvhdr,hdc,rcDraw);
}
void sDrawText(HDC hdc,int x,int y,int width,int height,const char* str,UINT format)
{
    RECT rect;
    if(str != NULL){
        SetRect(&rect,x+2,y+2,x+width,y+height);
        DrawText(hdc,str,-1,&rect,format);
    }
}
void CListView::ex_listview_draw_item(HWND hwnd, int idx, HDC hdc , RECT *rcDraw)
{
    bmpBk.Show(hdc,rcDraw->left,rcDraw->top);
    bmpSplit.Show(hdc,rcDraw->right-3,rcDraw->top);
    SetBkMode(hdc,BM_TRANSPARENT);

    const char* strTitle = GetColHeaderText(idx).c_str();
    assert(strTitle != NULL);
    sDrawText(hdc,rcDraw->left+3,0,rcDraw->right-rcDraw->left-4,rcDraw->bottom-rcDraw->top,strTitle,DT_SINGLELINE|DT_LEFT);

}
void listview_draw_item(HWND hwnd, int idx, HDC hdc , RECT *rcDraw)
{

    if(pMe)
        pMe->ex_listview_draw_item(hwnd,idx,hdc,rcDraw);
    //SetBkColor(hdc,GetWindowBkColor(hwnd));
    //SetTextColor(hdc,RGBA2Pixel(hdc,16,92,173,255));



}
bool CListView::EnableSkinStyle(bool yes)
{
    LVCUSTOMDRAWFUNCS drawFuncs;
    if(yes)
    {
        HWND lvHwnd = GetDlgItem(_parent->m_hWnd,_id);
        if(lvHwnd == HWND_INVALID)
            return false;
        drawFuncs.pfnDrawHdrBk   = listview_draw_bk;
        drawFuncs.pfnDrawHdrItem = listview_draw_item;
        bmpBk.LoadFile("comm/lvbk.png");
        bmpSplit.LoadFile("comm/lvcol.png");
        pMe = this;

        //SetWindowAdditionalData(lvHwnd,(DWORD)this);
    }else{
        drawFuncs.pfnDrawHdrBk   = NULL;
        drawFuncs.pfnDrawHdrItem = NULL;
        pMe = NULL;
    }

    this->SetCustomDrawFunc(&drawFuncs);
}
bool CListView::EnableTreeViewStyle(bool yes)
{
    if( (!_parent) || (_parent->m_hWnd == HWND_INVALID))
        return false;
    HWND lvHwnd = GetDlgItem(_parent->m_hWnd,_id);
    if(lvHwnd == HWND_INVALID)
        return false;
    DWORD style = GetWindowStyle(lvHwnd);
    if(yes){
        style |= LVS_TREEVIEW;
    }else{
        style &= ~LVS_TREEVIEW;
    }
    IncludeWindowStyle(lvHwnd,style);
    InvalidateRect(lvHwnd,NULL,true);
    return true;
}
