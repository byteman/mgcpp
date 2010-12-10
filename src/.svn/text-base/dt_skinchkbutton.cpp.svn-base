#include "dt_skinchkbutton.h"

CSkinChkButton::CSkinChkButton(skin_item_t* data, CSkinForm* parent,string typeName):
            CSkinCtrl(data,parent,typeName)

{
    if(_parent) {
         _parent->AddSkinItem(SKIN_CHKBTN_STYLE, data);
         _id = data->id;
    }
}
CSkinChkButton::CSkinChkButton(SKIN_CHECK_DESC* desc, CSkinForm* parent,string typeName):
            CSkinCtrl(parent,typeName)
{
    if(_parent) {
         _id =_parent->AddSkinItem(SKIN_CHKBTN_STYLE,desc->bmpindex, desc->left,desc->top);
    }
}
CSkinChkButton::CSkinChkButton(int bmpindex,SKIN_CHECK_DESC* desc, CSkinForm* parent,string typeName):
        CSkinCtrl(parent,typeName)
{
    if(_parent) {
         _id =_parent->AddSkinItem(SKIN_CHKBTN_STYLE,bmpindex, desc->left,desc->top);
    }
}
CSkinChkButton::~CSkinChkButton()
{

}
bool CSkinChkButton::GetCheckStatus()
{
    if(_parent) {
        return _parent->GetCheckStatus(_id);
    }
    return false;
}
void CSkinChkButton::SetCheckStatus(bool check)
{
    if(_parent) {
        _parent->SetCheckStatus(_id,check);
    }
}
