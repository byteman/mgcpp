#ifndef DT_FONT_H
#define DT_FONT_H
#include "common.h"
#include <string>
#include <map>
#include <vector>

class CFont{
public:
    CFont();
    int setFontColor(gal_pixel color);
    std::string name;
    PLOGFONT  pfont;
    gal_pixel font_color;
    int       size;
};

typedef std::map< std::string,std::vector<CFont*> > TFontMap;
class CFontMgr
{
public:
    CFontMgr();
    static CFontMgr& Get();
    //PLOGFONT GetFont(std::string fontname,int size);
    CFont*   GetFont(std::string fontname,int size);
private:
    TFontMap fontmaps;
    //PLOGFONT _logFonts[8];
};

#endif // DT_FONT_H
