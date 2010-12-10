#include "dt_font.h"
#include <Poco/SingletonHolder.h>
#include <stdlib.h>

CFont::CFont()
{
    font_color=RGB2Pixel(HDC_SCREEN,255,0,0);
    name="";
    pfont=NULL;
    size=0;
}
int CFont::setFontColor(gal_pixel color)
{
    font_color = color;
}
CFontMgr::CFontMgr()
{

    std::vector<CFont*> fonts;
    for(int i = 0; i < 4; i++)
    {
        CFont *f = new CFont;
        f->name="stxinwei";
        int size=16 + i*8;
        f->pfont= CreateLogFont("ttf","stxinwei","GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN,
                                FONT_SETWIDTH_NORMAL,
                                FONT_SPACING_CHARCELL,
                                FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
                                size, 0);

        f->size=size;

        fprintf(stderr,"create font %s size=%d handle = %x\n",f->name.c_str(),size,f->pfont);

        fonts.push_back(f);
    }
    fontmaps["stxinwei"] = fonts;

    fonts.clear();
    for(int j=0; j <4;j++){
        CFont *f = new CFont;
        f->name="song";
        int size=16+j*8;
        f->pfont = CreateLogFont("rbf","song","GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN,
                                FONT_SETWIDTH_NORMAL,
                                FONT_SPACING_CHARCELL,
                                FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
                                size, 0);
        f->size=size;

        fprintf(stderr,"create font %s size=%d handle = %x\n",f->name.c_str(),size,f->pfont);

        fonts.push_back(f);
    }
    fontmaps["song"] = fonts;
}
CFontMgr& CFontMgr::Get()
{
    static Poco::SingletonHolder<CFontMgr> sh;
    return *sh.get();
}
CFont* CFontMgr::GetFont(std::string fontname,int size)
{
    for(size_t i = 0 ; i < fontmaps[fontname].size(); i++)
    {
        if (size == fontmaps[fontname].at(i)->size)
        {
            fprintf(stderr,"find font  %s size=%d\n",fontname.c_str(),size);
            return fontmaps[fontname].at(i);
        }
    }
    fprintf(stderr,"can not find font  %s size=%d\n",fontname.c_str(),size);
    return fontmaps[fontname].at(0);
}
