#include "dt_static.h"

CStatic::CStatic(CTRLDATA* data,CSkinForm* parent,string typeName):
        CCommCtrl(data,parent,typeName)
{

}
CStatic::CStatic(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName)
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
    data->dwExStyle = DEF_STATIC_EXSTYLE;
    data->dwStyle   = DEF_STATIC_STYLE;
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
    _font = CreateLogFont("ttf","stxinwei","GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN,
                         FONT_SETWIDTH_NORMAL,
                         FONT_SPACING_CHARCELL,
                         FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
                         36, 0);
}
CStatic::~CStatic()
{

}
void CStatic::SetText(string strText)
{
    if(_parent) {
        _parent->SetItemText(_data->id,strText);
    }
}
string& CStatic::GetText()
{
    _strText = "";
    if(_parent && _data->id)
        _strText = _parent->GetItemText(_data->id);
    return _strText;
}
 bool  CStatic::SetFontSize(int size)
 {
     if(_font->size != size){
        DestroyLogFont(_font);
        _font = CreateLogFont("ttf","stxinwei","GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN,
                                FONT_SETWIDTH_NORMAL,
                                FONT_SPACING_CHARCELL,
                                FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
                                size, 0);
        if(_font == NULL)
            return false;
     }
     if( (_parent) && (_parent->m_hWnd != HWND_INVALID))
     {
        fprintf(stderr,"fontxx = %s\n",_font->family);

        return (SetWindowFont(GetDlgItem(_parent->m_hWnd,_id),_font)!=NULL);
     }
     return false;
 }
