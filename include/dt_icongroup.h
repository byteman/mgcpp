#ifndef DT_ICONGROUP_H
#define DT_ICONGROUP_H

#include "dt_core.h"
typedef vector<CIcon*> IconList;
/*
一组图片文件,每个文件代表一个不同的状态
*/
class CIconGroup
{
public:
    CIconGroup(bool cache=false);
    CIconGroup(const char** icon_array,int file_num,bool cache=false);
    ~CIconGroup();

    bool AddIcons(const char** icon_array,int file_num,bool cache=false);
    bool AddIcons(std::string iconfile,bool cache=false);
    bool AddIcons(CIcon* icon);
    //bool LoadIcons(const char* icon_array,int icon_num,HWND hwnd);
    void Show(int left, int top,HWND hwnd,int index=1,int iconIdx = 1);
    void Show(int left, int top, int index=1,int iconIdx=1);
    void Show(HDC hdc,int left, int top, int index=1,int iconIdx=1);
    void ShowAll(HDC hdc);
    void Hide();
    int  GetCount();
    IconList& GetIconList();
private:
    int _file_num;
    IconList _iconlist;
    HWND _hwnd;
    bool _bCache;
    int GetIconNum(std::string path);
    int _left,_top;
};

#endif // DT_ICONGROUP_H
