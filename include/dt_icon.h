#ifndef DT_ICON_H
#define DT_ICON_H
#include "common.h"
#include <string>
class CacheBitmap;
class CIcon
{
public:
    CIcon(bool cache=false);

    CIcon(std::string filename,int count=1,bool cache=false);
    ~CIcon();
    /*
    返回的BITMAP千万不能delete
    */
    BITMAP* GetBitmap();
    bool IsLoad();
    bool LoadFile(std::string filename,int count=1,bool cache=false);
    //void Show(HWND parent,int left,int top,int index = 0);
    //void Show(HWND parent,RECT &rect,int index = 0);
    void Show(HDC hdc,int left,int top,int index = 1);
    void Show(RECT &rect,int index = 1);
    void Show(int left,int top,int index = 1);
    void Show(HDC hdc);
    void SetPos(int x, int y);
    void Hide();
private:
    BITMAP *_hIcon;
    CacheBitmap* _cacheBmp;
    int _w,_h;
    int _num;
    int _curShow;
    bool _bLoad;
    bool _bCache;
    RECT _rect;
    void Reset();
    HDC  _hdc;
    int _left,_top;
};

#endif // DT_ICON_H
