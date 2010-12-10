#include "dt_ctrl.h"
#include "common.h"
#include <assert.h>
CCtrl::CCtrl():
        _id(-1),
        _parent(NULL),
        _typeName("CCtrl")
{
    //std::cout << "parent = " << &_parent << std::endl;
}
CCtrl::CCtrl(CSkinForm* parent,std::string typeName):
        _id(-1)
{ 
    SetCtrlParentAndName(parent,typeName);
}
void CCtrl::SetCtrlParentAndName(CSkinForm* parent,std::string typeName)
{
    _parent   = parent;
    _typeName = typeName;
    //std::cout << "parent = " << &_parent << std::endl;

}
bool CCtrl::EnableOwnStyle(bool yes)
{

}
void CCtrl::RegisterCtrl(CCtrl* ctrl)
{
    assert(_parent != NULL);
    _parent->AddCtrl(this);
}
CCtrl::~CCtrl()
{
    _parent->DelCtrl(this);
    _parent = NULL;
    _typeName = "";
}
int CCtrl::GetId()
{
    return _id;
}
std::string& CCtrl::GetTypeName()
{
    return _typeName;
}
bool    CCtrl::CanFocus()
{
    return false;
}
void    CCtrl::SetFocus()
{
    HWND h = GetDlgItem(_parent->m_hWnd,_id);
    if(h != HWND_INVALID)
    {
       //SetFocusChild(h);
    }
}
