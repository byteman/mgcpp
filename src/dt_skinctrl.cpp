#include "dt_skinctrl.h"
CSkinCtrl::CSkinCtrl(skin_item_t* data, CSkinForm* parent,string typeName)
                :CCtrl(parent,typeName)

{
    _data   = data;

}
CSkinCtrl::CSkinCtrl(CSkinForm* parent,string typeName):
        CCtrl(parent,typeName)
{

}
CSkinCtrl::~CSkinCtrl()
{

}

void    CSkinCtrl::Show()
{
    skin_show_item(&(_parent->m_skin_head), _id, TRUE);
}

void    CSkinCtrl::Hide()
{
    skin_show_item(&(_parent->m_skin_head), _id, FALSE);
}
