#include "dt_commctrl.h"
#include <assert.h>
CCommCtrl::CCommCtrl()
{
    _alloc_desc = false;
    _data = NULL;
}
CCommCtrl::CCommCtrl(CTRLDATA* data,CSkinForm* parent,string typeName)
    :CCtrl(parent,typeName),
    _alloc_desc(false)
{
    SetParam(data,parent,typeName);

}
void CCommCtrl::SetParam(CTRLDATA* data,CSkinForm* parent,string typeName)
{
    _data   = data;


    SetCtrlParentAndName(parent,typeName);

    assert((_data != NULL) && (_parent != NULL));
    //fprintf(stderr,"class name = %s\n",_data->class_name);
    //std::cout << "classname=" <<_data->class_name <<std::endl;
    if(std::string(_data->class_name) != std::string(typeName))
    {
        std::cerr << "typeName Mismatch" << _data->class_name << " " << typeName << std::endl;
        assert(1 == 0);
    }
    //std::cout << "CCommCtrl parent = " << &_parent << std::endl;
    if(_parent) {
        _parent->AddCommItem(COMMON_CTRL_STYLE, data);
        _id = data->id;
        //std::cout << "commctl id =" << _id << std::endl;
    }

    //该函数必须在_id已经分配，SetCtrlParentAndName已经调用才能调用
    RegisterCtrl(this);


    //std::cout << "parent = " << &_parent << std::endl;

}
CCommCtrl::~CCommCtrl()
{
    if(_data && (_alloc_desc))
    {
        delete []_data->caption;
        delete []_data->class_name;
        delete _data;
    }
    _data = NULL;
}
