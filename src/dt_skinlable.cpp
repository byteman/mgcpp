#include "dt_skinlable.h"
static si_bmplabel_t num_bmp_desc = { "1258.00", "0123456789 -." };
CSkinLable::CSkinLable(int bmpindex,SKIN_CTRL_DESC* desc, CSkinForm* parent,string typeName):
        CSkinCtrl(parent,typeName)
{
    if(_parent) {
         _id =_parent->AddSkinItem(SKIN_BMPLBL_STYLE,bmpindex, desc->left,desc->top,(void*)&num_bmp_desc);
    }
}
CSkinLable::~CSkinLable()
{

}
void CSkinLable::Display(std::string strText)
{
    if(_parent) {
        _parent->SetSkinlableText(_id,strText.c_str());
    }
}
