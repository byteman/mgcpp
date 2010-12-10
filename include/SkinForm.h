//////////////////////////////////////////////////////////////////////
// SkinForm.h: interface for the CSkinForm class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __SKINFORM_H__
#define __SKINFORM_H__
#include "common.h"
#include <vector>
#include <string>
#include <iostream>
#include <minigui/skin.h>

using namespace std;

#define MSG_HOTKEY MSG_USER+2
#define MSG_WET_WT MSG_USER+3
#define ARRAY_SIZE(array,type) ((sizeof(array))/(sizeof(type)))

#define COMMON_CTRL_STYLE   (SI_TYPE_CONTROL|SI_TEST_SHAPE_RECT|SI_STATUS_VISIBLE)
#define SKIN_BUTTON_STYLE   (SI_TYPE_CMDBUTTON|SI_TEST_SHAPE_RECT|SI_STATUS_VISIBLE)
#define SKIN_BMPLBL_STYLE   (SI_TYPE_BMPLABEL|SI_TEST_SHAPE_RECT|SI_STATUS_VISIBLE)
#define SKIN_CHKBTN_STYLE   (SI_TYPE_CHKBUTTON|SI_TEST_SHAPE_RECT|SI_STATUS_VISIBLE)
#define	ES_DIGIT_ONLY       0x40L		/*  */
#define ES_DECIMAL          0x80L
class CCtrl;
typedef vector<CCtrl*> CTRLIST;
typedef vector<int> TABFOCUSLIST;

#define MSG_PHONE_METHOD_SWITCH MSG_USER+13
#define MSG_PHONE_METHOD_STATUS MSG_USER+14
#define MSG_PHONE_IME_OPEN MSG_USER+15
#define MSG_PHONE_IME_CLOSE MSG_USER+16
class RES
{
  public:
	int type;
	int num;
	//char* path[32];
};
typedef struct tag_Pos{
    int x;
    int y;
}POS;
class HOTKEY
{
  public:
	HOTKEY();
	HOTKEY(HWND hwnd, int id, int fsModifiers, int vk)
	{
		m_hwnd = hwnd;
		m_id = id;
		m_fsModifiers = fsModifiers;
		m_vk = vk;
	}
	HWND m_hwnd;

	int m_id;

	int m_fsModifiers;

	int m_vk;
};

typedef struct skin_bmp_s		//Add by Achille 2009/11/27 11:15:55
{
	int x;
	int y;
	int w;
	int h;
    const char* path;
	BITMAP m_bmp;
} skin_bmp_t;
typedef struct ctrldata{
   char* class_name;
   DWORD style;
   int   x,y,h,w;
   const char* caption;
   DWORD dwAddData;
   DWORD dwExStyle;
}ctrldata_t;
typedef vector < HOTKEY > HotkeySet;

typedef vector < skin_item_t > TItemSet;

class BMP_RES:public RES
{
  public:
	const char **file_array;
};
class CCtrl;
class CIconGroup;
class CFont;
class CSkinForm
{
  public:
	CSkinForm();
	virtual ~CSkinForm();
	virtual bool LoadRes(const char **path, int pic_num);
	virtual bool UnloadRes();
	virtual HWND CreateForm(HWND hWnd, int lx = 0, int ly = 0, int rx =
							800, int by = 480, BOOL bModal = TRUE);
	void Close();

	virtual void OnButtonClick(skin_item_t * p_item);
	virtual void OnSliderChange(skin_item_t * p_item);
	virtual void OnGetFocus(skin_item_t * p_item);
	virtual void OnKillFocus(skin_item_t * p_item);
	virtual void OnPaint(HWND hWnd);
	virtual void OnCreate();
	virtual void OnShow();
	virtual void OnClose();
	virtual void OnTimer(int ID);
	virtual void OnLButtonDown(int x, int y);
        virtual void OnLButtonDbClick(int x, int y);
	virtual void OnKeyUp(int scancode, DWORD shiftstate);
	virtual int  AddSkinItem(DWORD style = SKIN_BUTTON_STYLE, int bmpidx =
							0, int left = 0, int top = 0, void *type_data =
							NULL);
	virtual int AddSkinItem(DWORD style = SKIN_BUTTON_STYLE, skin_item_t * p_skin = NULL);	//Add by Achilles 2009-11-26
	virtual int AddCommItem(DWORD style =
							COMMON_CTRL_STYLE, CTRLDATA * p_item = NULL);
	virtual void OnCommand(HWND hWnd, int message, WPARAM wParam,
						   LPARAM lParam);
	bool _CommCtrlNotify(HWND hwnd, int id, int nc);
	bool RegisterHotKey(HWND hWnd, int id, int fsModifiers, int vk);
	void SetItemStatus(int id, DWORD status);
	DWORD GetItemStatus(int id);
	virtual void OnUserMsg(HWND hWnd, int message, WPARAM wParam,
						   LPARAM lParam);
	virtual void OnEditChange(HWND hEdit, char key);
	virtual void OnCommCtrlNotify(HWND hwnd, int id, int nc);
	int WinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam,
				int *p_result);
        void DrawMyText(HDC hdc,CFont* font, RECT *rect, std::string text, int opt=(DT_CENTER|DT_VCENTER|DT_SINGLELINE));
        string GetItemText(int id);
        bool   SetItemText(int id,string strText);
        bool   SetItemText(int id,char*  szText);
        bool   SetSkinlableText(int id, char* strText);
        bool   SetSkinlableText(int id, string strText);
        void   AddCtrl(CCtrl* ctrl);
        void   DelCtrl(CCtrl* ctrl);
	bool InstallCommCtrlHook(HWND handle);
        bool GetCheckStatus(int id);
        void SetCheckStatus(int id,bool check);
        HWND GetItemHwnd(int id);
	HWND m_hWnd;
        CIconGroup* _intenalIcons;
  protected:
	static int msg_cb_func(HWND hWnd, int message, WPARAM wParam, LPARAM lParam, int *p_result);
	static int event_cb_func(HWND hWnd, skin_item_t * p_item, int event, void *p_data);

	void InitSkinHeader(const char *p_name = "unknown", int bk_bmp_index =
						0, skin_item_t * p_items = NULL, int nr_items = 0);

	bool FillBoxWithBitmapEx(HDC hdc, skin_bmp_t * p_bmp_t = NULL);	//Add by Achilles 2009/11/27 11:34:27

public:
    skin_item_t *p_skin_items;
    skin_head_t m_skin_head;

protected:
    bool m_bColse;
    bool m_Showflag;

  private:
    bool HasLoadRes();
	bool AllocPicRes(const char **path, int pic_num);
	void FreePicRes(int nres);
	void FreeItems();
	static CSkinForm *LookForByHwnd(HWND hWnd);

    void ProcessEnterKey();
	void SerachHotKey(int scancode, DWORD shiftstate);
	void RegisterForm(HWND hWnd, CSkinForm * p_form);
	void UnRegisterForm(HWND hWnd);
    int  _EditHook();
    void ProcessTabKey();
	static CSkinForm *p_PreForm;
	int m_items_cnt;
	BMP_RES *m_res;
    CIconGroup* _iconGrp;
	bool m_Alloc_PicRes;
	bool m_Load_Res;
	TItemSet m_ChildArrays;
	char m_title[32];			//skin form's title;
    CTRLIST  _Ctrlist;
    int _maxFocusId,_minFocusId;
    int _curFocusId,_prevFocusId;
    TABFOCUSLIST _focusList;
};

#endif							// !defined __SKINFORM_H__
