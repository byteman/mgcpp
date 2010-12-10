#include "dt_cachebmp.h"
#include <iostream>
#include <unistd.h>
CacheBitmap::CacheBitmap(std::string fileName):
			_refCnt(1)
{
                //std::cout << "CacheBitmap" <<std::endl;
		LoadFile(fileName);
}

bool CacheBitmap::LoadFile(std::string fileName)
{
    //std::cout << "load file" << fileName << std::endl;
    //sleep(1);
    if( LoadBitmapFromFile(HDC_SCREEN,&_hBmp,fileName.c_str()) < 0)
    {
        std::cout << "can't load file" << fileName << std::endl;
        _bLoad = false;
        return false;
    }
    _name  = fileName;
    _bLoad = true;
   

    return _bLoad;
}

CacheBitmap::~CacheBitmap()
{
                //std::cout << "~CacheBitmap" <<std::endl;
    UnloadBitmap(&_hBmp);
    _name = "";
    _refCnt = 0;
    _bLoad = false;
		
}
bool CacheBitmap::isLoad()
{
		return _bLoad;
}
BITMAP* CacheBitmap::GetData()
{	
		return &_hBmp;
}
void CacheBitmap::AddRef()
{
		_refCnt++;
                //std::cout << "ref="<<_refCnt <<std::endl;
}
void CacheBitmap::Free()
{
		if (--_refCnt <= 0)
		{
			delete this;
		}
}
void CacheBitmap::Unload()
{
		delete this;
}
std::string& CacheBitmap::GetName()
{
		return _name;
}



CacheBitmapPool::CacheBitmapPool()
{
        //std::cout << "CacheBitmapPool" <<std::endl;
	CacheList.clear();
}
CacheBitmapPool::~CacheBitmapPool()
{
	for (int i = 0; i < CacheList.size(); i++)
	{
		if (CacheList.at(i))
		{
			CacheList.at(i)->Unload();				
		}
	}
	CacheList.clear();
        //std::cout << "~CacheBitmapPool" <<std::endl;
}
void CacheBitmapPool::FreeBitmap(CacheBitmap* bmp)
{
	  //can,t find bmp in CacheList
	 
	  //if find bmp in in CacheList
	  //then erase it from CacheList and bmp->Free();
	  
	   bmp->Free();
}
CacheBitmap* CacheBitmapPool::getBitmap(std::string name,bool cache)
{
	CacheBitmap* tmp = NULL;
        cache = true;
	for (int i = 0; i < CacheList.size(); i++)
	{
		if(CacheList.at(i))
		if (CacheList.at(i)->GetName() == name)
		{
			CacheList.at(i)->AddRef();
                        //std::cout << "find cache file" << name << std::endl;
			return CacheList.at(i);				
		}
	}
	
	tmp = new CacheBitmap(name);
	if (cache)
	{
		tmp->AddRef();
		CacheList.push_back(tmp);
	}
	return tmp;
}
