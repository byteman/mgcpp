#ifndef DT_CACHEBMP_H
#define DT_CACHEBMP_H
#include "common.h"
#include "dt_icon.h"
#include <vector>

class CacheBitmap{
public:
    bool LoadFile(std::string fileName);
    CacheBitmap(std::string fileName);
    bool isLoad();
    void AddRef();
    BITMAP* GetData();
    void Free();
    void Unload();
    std::string& GetName();
private:
    ~CacheBitmap();
    BITMAP _hBmp;
    int _refCnt;
    bool _bLoad;
    std::string _name;

};

class CacheBitmapPool{
public:
    CacheBitmapPool();
    ~CacheBitmapPool();

    CacheBitmap* getBitmap(std::string name,bool cache);
private:
    void FreeBitmap(CacheBitmap* bmp);
    std::vector<CacheBitmap*> CacheList;
    friend class CIcon;
};
#endif
