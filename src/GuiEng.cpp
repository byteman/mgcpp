#include "GuiEng.h"
#include "iniFile.h"
#include <Poco/StringTokenizer.h>
#include <Poco/NumberParser.h>
#include <Poco/Format.h>


GuiEng::GuiEng()
{
    TIniFile cfg("dvr.conf");
    fprintf(stderr,"width=%d h = %d\n",RECTW(g_rcDesktop),RECTH(g_rcDesktop));
    baseWidth = cfg.ReadInteger("common","basewidth", 360);
    baseHeight= cfg.ReadInteger("common","baseheight",240);
    curWidth = RECTW(g_rcDesktop);
    curHeight=RECTH(g_rcDesktop);

    for(int i = 0; i < 4; i++)
        _logFonts[i] = CreateLogFont("ttf","stxinwei","GB2312-0", FONT_WEIGHT_SUBPIXEL, FONT_SLANT_ROMAN,
                         FONT_SETWIDTH_NORMAL,
                         FONT_SPACING_CHARCELL,
                         FONT_UNDERLINE_NONE, FONT_STRUCKOUT_NONE,
                         16+i*8, 0);

}
GuiEng& GuiEng::Get()
{
    static GuiEng eng;
    return eng;
}
CIpAddr*  GuiEng::CreateIpCtrl(CSkinForm* parent,std::string formName,std::string ctrlName)
{
    TIniFile cfg("dvr.conf");
    std::string itemInfo;
    itemInfo = cfg.ReadString(formName,ctrlName,"");
    if(itemInfo != ""){
        Poco::StringTokenizer itemSet(itemInfo,",");
        if(itemSet.count() >= 4){
            COMM_CTRL_DESC desc;
            desc.x = Poco::NumberParser::parse(itemSet[0])*curWidth/baseWidth;
            desc.y = Poco::NumberParser::parse(itemSet[1])*curHeight/baseHeight;
            desc.h = Poco::NumberParser::parse(itemSet[2])*curHeight/baseHeight;
            desc.w = Poco::NumberParser::parse(itemSet[3])*curWidth/baseWidth;
            fprintf(stderr,"edit ctrl x=%d,y=%d,w=%d,h=%d\n",desc.x,desc.y,desc.w,desc.h);
            desc.caption = (itemSet.count() == 4)?(char*)"ipaddr":(char*)itemSet[4].c_str();

            return new CIpAddr(&desc,parent);
        }
    }
    return NULL;
}
CEdit*  GuiEng::CreateEditCtrl(CSkinForm* parent,std::string formName,std::string ctrlName)
{
    TIniFile cfg("dvr.conf");
    std::string itemInfo;
    itemInfo = cfg.ReadString(formName,ctrlName,"");
    if(itemInfo != ""){
        Poco::StringTokenizer itemSet(itemInfo,",");
        if(itemSet.count() >= 4){
            COMM_CTRL_DESC desc;
            desc.x = Poco::NumberParser::parse(itemSet[0])*curWidth/baseWidth;
            desc.y = Poco::NumberParser::parse(itemSet[1])*curHeight/baseHeight;
            desc.h = Poco::NumberParser::parse(itemSet[2])*curHeight/baseHeight;
            desc.w = Poco::NumberParser::parse(itemSet[3])*curWidth/baseWidth;
            fprintf(stderr,"edit ctrl x=%d,y=%d,w=%d,h=%d\n",desc.x,desc.y,desc.w,desc.h);
            desc.caption = (itemSet.count() == 4)?(char*)"edit":(char*)itemSet[4].c_str();

            return new CEdit(&desc,parent);
        }
    }
    return NULL;
}
CListView* GuiEng::CreateListViewCtrl(CSkinForm* parent,std::string formName,std::string ctrlName)
{
    TIniFile cfg("dvr.conf");
    std::string itemInfo;
    itemInfo = cfg.ReadString(formName,ctrlName,"");
    if(itemInfo != ""){
        Poco::StringTokenizer itemSet(itemInfo,",");
        if(itemSet.count() >= 4){
            COMM_CTRL_DESC desc;
            desc.x = Poco::NumberParser::parse(itemSet[0])*curWidth/baseWidth;
            desc.y = Poco::NumberParser::parse(itemSet[1])*curHeight/baseHeight;
            desc.h = Poco::NumberParser::parse(itemSet[2])*curHeight/baseHeight;
            desc.w = Poco::NumberParser::parse(itemSet[3])*curWidth/baseWidth;

            fprintf(stderr,"listview ctrl x=%d,y=%d,w=%d,h=%d\n",desc.x,desc.y,desc.w,desc.h);
            desc.caption = (itemSet.count() == 4)?(char*)"listview":(char*)itemSet[4].c_str();

            return new CListView(&desc,parent);
        }
    }
    return NULL;
}
CStatic*  GuiEng::CreateStaticCtrl(CSkinForm* parent,std::string formName,std::string ctrlName)
{
    TIniFile cfg("dvr.conf");
    std::string itemInfo;
    itemInfo = cfg.ReadString(formName,ctrlName,"");
    if(itemInfo != ""){
        Poco::StringTokenizer itemSet(itemInfo,",");
        if(itemSet.count() >= 4){
            COMM_CTRL_DESC desc;
            desc.x = Poco::NumberParser::parse(itemSet[0])*curWidth/baseWidth;
            desc.y = Poco::NumberParser::parse(itemSet[1])*curHeight/baseHeight;
            desc.h = Poco::NumberParser::parse(itemSet[2])*curHeight/baseHeight;
            desc.w = Poco::NumberParser::parse(itemSet[3])*curWidth/baseWidth;

            fprintf(stderr,"static ctrl x=%d,y=%d,w=%d,h=%d\n",desc.x,desc.y,desc.w,desc.h);
            desc.caption = (itemSet.count() == 4)?(char*)"edit":(char*)itemSet[4].c_str();

            return new CStatic(&desc,parent);
        }
    }
    return NULL;
}
CSkinButton* GuiEng::CreateSkinButton(CSkinForm* parent,std::string formName,std::string ctrlName)
{
    TIniFile cfg("dvr.conf");
    std::string itemInfo;
    itemInfo = cfg.ReadString(formName,ctrlName,"");
    if(itemInfo != ""){
        Poco::StringTokenizer itemSet(itemInfo,",");
        if(itemSet.count() >= 6){
            SKIN_BUTTON_DESC desc;
            desc.left = Poco::NumberParser::parse(itemSet[0])*curWidth/baseWidth;
            desc.top  = Poco::NumberParser::parse(itemSet[1])*curHeight/baseHeight;
            desc.bmpindex = Poco::NumberParser::parse(itemSet[5]);
            desc.caption = (char*)itemSet[4].c_str();

            fprintf(stderr,"skinbtn ctrl x=%d,y=%d,w=%d,h=%d\n",desc.left,desc.top);
            return new CSkinButton(&desc,parent);
        }
    }
    return NULL;
}
bool    GuiEng::loadRes(CSkinForm* parent,std::string formName)
{
    TIniFile cfg("dvr.conf");
    int num = cfg.ReadInteger(formName,"picnum",0);
    if(num > 0)
    {
        std::vector<std::string> picVect;
        const char** ptrRes = new const char*[num];
        for(int i =0 ; i < num ; i++)
        {
            picVect.push_back(cfg.ReadString(formName,Poco::format("pic%d",i),""));
            ptrRes[i] = (char*)picVect.at(i).c_str();
        }
        if (!parent->LoadRes(ptrRes, num))
        {
                printf("Can't loadres\n");
                return false;
        }
        //return true;
    }

    num = cfg.ReadInteger(formName,"iconum",0);
    if(num > 0){
        for(int i = 0; i < num; i++)
        {
            std::string iconInfo = cfg.ReadString(formName,Poco::format("icon%d",i),"");
            if(iconInfo != "")
            {
                Poco::StringTokenizer iconSet(iconInfo,",");
                if(iconSet.count() >= 5){
                    CIcon* tmp = new CIcon(iconSet[4]);
                    int x = Poco::NumberParser::parse(iconSet[0])*curWidth/baseWidth;
                    int y = Poco::NumberParser::parse(iconSet[1])*curHeight/baseHeight;
                    tmp->SetPos(x,y);
                    parent->_intenalIcons->AddIcons(tmp);

                }
            }
        }
    }
    return true;

}
void            GuiEng::getCenterRect(RECT *rect)
{

}
PLOGFONT        GuiEng::GetLogFont(int size)
{
    if(size <= 60 )
        return _logFonts[(size-16)/8];
    else
        return _logFonts[0];
}
bool            GuiEng::InitCommGui()
{

}
CCtrl*          GuiEng::GetCtrl(std::string ctrlName)
{

}
int             GuiEng::loadTipInfo(std::string formName,std::string tipName,StringList& tips)
{
    TIniFile cfg("dvr.conf");
    int num = cfg.ReadInteger(formName,tipName,0);
    tips.clear();
    for(int i = 0; i < num; i++){
        std::string tip = cfg.ReadString(formName,Poco::format("tip%d",i),"no tip");
        tips.push_back(tip);
    }
    return num;
}
