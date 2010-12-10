#ifndef GUIENG_H
#define GUIENG_H
#include "dt_core.h"

#define TITLE_FONT  0
#define TEXT_FONT   1
#define INFO_FONT   2
typedef vector<string> StringList;
class GuiEng
{
public:
    GuiEng();
    static GuiEng& Get();
    CEdit*          CreateEditCtrl(CSkinForm* parent,std::string formName,std::string ctrlName);
    CStatic*        CreateStaticCtrl(CSkinForm* parent,std::string formName,std::string ctrlName);
    CSkinButton*    CreateSkinButton(CSkinForm* parent,std::string formName,std::string ctrlName);
    CListView*      CreateListViewCtrl(CSkinForm* parent,std::string formName,std::string ctrlName);
    CIpAddr*        CreateIpCtrl(CSkinForm* parent,std::string formName,std::string ctrlName);
    bool            loadRes(CSkinForm* parent,std::string formName);
    int             loadTipInfo(std::string formName,std::string tipName,StringList& tips);
    void            getCenterRect(RECT *rect);
    PLOGFONT        GetLogFont(int size);
    bool            InitCommGui();
    CCtrl*          GetCtrl(std::string ctrlName);
    //void            DestroyLogFont(PLOGFONT);
    int baseWidth;
    int baseHeight;
    int curWidth;
    int curHeight;
private:
    PLOGFONT  _logFonts[4];
    CIconGroup icons;
};

#endif // GUIENG_H
