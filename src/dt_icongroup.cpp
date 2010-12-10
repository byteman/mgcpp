#include "dt_icongroup.h"

/*
CIconGroup icoPreLoader;
icoPreLoader.AddIcons(preLoad_icon_array,xxx,true);
只要加载一次，以后所有的这些文件都可以cache存取
*/

CIconGroup::CIconGroup(bool cache):
        _file_num(0),
        _hwnd(HWND_INVALID),
        _bCache(cache)
{
    _iconlist.clear();
}

CIconGroup::CIconGroup(const char** icon_array,int file_num,bool cache):
         _hwnd(HWND_INVALID),
        _file_num(file_num),
        _bCache(cache)
{
    _iconlist.clear();
    _file_num = file_num;
    for(int i = 0; i < _file_num; i++)
    {
        CIcon* tmp = new CIcon(icon_array[i],1,_bCache);
        _iconlist.push_back(tmp);
    }
    
}
CIconGroup::~CIconGroup()
{
    //fprintf(stderr,"cnt = %d\n",_iconlist.size());
    for(size_t i = 0; i < _iconlist.size(); i++)
    {
        if(_iconlist.at(i))
        {
            delete _iconlist.at(i);
        }
    }
    _iconlist.clear();
    _file_num =  0;
}
int CIconGroup::GetIconNum(std::string path)
{
	int start = path.rfind("_");
	
	int stop  = path.rfind(".");

	if(( stop == std::string::npos) || (start == std::string::npos))
	{
		return 1;
	}
	if (stop <= (start+1))
	{
		return 1;
	}
	std::string numStr = path.substr(start+1,(stop - start -1));
        //std::cout << "numStr = " << numStr << std::endl;

	int ret = atoi(numStr.c_str());
        /*
        if(numStr == "btn")
        {
            std::cout << "ret = " << ret << std::endl;
        }*/
	if (ret == 0)
	{
		ret = 1;
	}
	return ret;
}

bool CIconGroup::AddIcons(const char** icon_array,int file_num,bool cache)
{
    for(int i = 0; i < file_num; i++)
        if(!AddIcons(string(icon_array[i]),cache))
            return false;
    return true;
}
bool CIconGroup::AddIcons(CIcon* icon)
{
    if(icon->IsLoad())
    {
        _iconlist.push_back(icon);
        _file_num++;
        return true;
    }
    return false;
}
bool CIconGroup::AddIcons(std::string iconfile,bool cache)
{

    //printf("realPath = %s\n",realPath.c_str());
    CIcon* tmp = new CIcon(iconfile,GetIconNum(iconfile),cache);
    if(tmp->IsLoad())
    {
        _iconlist.push_back(tmp);
        _file_num++;
        return true;
    }
    std::cerr << "CIconGroup::AddIcons Can't load icon " << iconfile << std::endl;
    return false;
}

void CIconGroup::Show(int left, int top, int index,int iconIdx)
{
    if((index > 0) && (index <= _file_num) )
    {
        if(_iconlist.at(index-1))
        {
           _iconlist.at(index-1)->Show(left,top,iconIdx);
        }
    }
}
void CIconGroup::Show(HDC hdc,int left, int top, int index,int iconIdx)
{
    if((index > 0) && (index <= _file_num))
    {
        if(_iconlist.at(index-1))
        {
           _iconlist.at(index-1)->Show(hdc,left,top,iconIdx);
        }
    }
}
void CIconGroup::Show(int left, int top,HWND hwnd,int index,int iconIdx)
{
    if((index > 0) && (index <= _file_num))
    {
        if(_iconlist.at(index-1))
        {
           _iconlist.at(index-1)->Show(left,top,hwnd,iconIdx);
        }
    }
}
void CIconGroup::ShowAll(HDC hdc)
{
    for(int i = 0; i < _file_num; i++){
        _iconlist.at(i)->Show(hdc);
    }
}
void CIconGroup::Hide()
{

}
int  CIconGroup::GetCount()
{
    return _file_num;
}
IconList& CIconGroup::GetIconList()
{
    return _iconlist;
}
