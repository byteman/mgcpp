//////////////////////////////////////////////////////////////////////
// SkinForm.cpp: implementation of the CSkinForm class.
//
//////////////////////////////////////////////////////////////////////

#include "SkinForm.h"


#include "dt_core.h"
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <cstdio>
#include <cctype>
#include <pthread.h>
using namespace std;

static vector <CSkinForm *> m_Forms;
#define MAX_INVALID_ID -1
#define MIN_INVALID_ID 0xffff
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSkinForm *CSkinForm::p_PreForm = NULL;

static HotkeySet g_HotkeySet;

static bool HotKeyInit = false;
/*
static bool mutex_init_flag = false;
static pthread_mutex_t __msg_cb_mutex;
static pthread_mutex_t __event_cb_mutex;
static pthread_mutex_t __forms_mutex;

#define     MSG_CB_LOCK     pthread_mutex_lock(&__msg_cb_mutex)
#define     MSG_CB_UNLOCK   pthread_mutex_unlock(&__msg_cb_mutex)

#define     EVENT_CB_LOCK   //pthread_mutex_lock(&__event_cb_mutex)
#define     EVENT_CB_UNLOCK //pthread_mutex_unlock(&__event_cb_mutex)

#define     FORMS_LOCK      pthread_mutex_lock(&__forms_mutex)
#define     FORMS_UNLOCK    pthread_mutex_unlock(&__forms_mutex)
*/
CSkinForm::CSkinForm()
{
    /*
    if (!mutex_init_flag)
    {
        //pthread_mutex_init(&__msg_cb_mutex, NULL);
        //pthread_mutex_init(&__event_cb_mutex, NULL);
        //pthread_mutex_init(&__forms_mutex, NULL);
        mutex_init_flag = true;
    }
    */
    

	m_items_cnt = 0;
	m_hWnd = HWND_INVALID;
	m_Alloc_PicRes = false;
	m_Load_Res = false;
        //m_res = new BMP_RES();
        _iconGrp = new CIconGroup();
        _intenalIcons   = new CIconGroup();

        //assert(m_res != NULL);
        assert(_iconGrp != NULL);
        assert(_intenalIcons != NULL);
	p_skin_items = NULL;
	memset((void *) &m_skin_head, 0, sizeof(skin_head_t));
	memset(m_title, 0, 32);

	if (!HotKeyInit)
	{
		g_HotkeySet.clear();
	}
	m_Showflag = false;
        m_bColse = false;
        _Ctrlist.clear();
        _focusList.clear();
        _maxFocusId = MAX_INVALID_ID;
        _minFocusId = MIN_INVALID_ID;
        _curFocusId = -1;
        _prevFocusId= -1;

	AchillesDBG("-=-=SkinForm.cpp=-=-CSkinForm::CSkinForm\r\n");
}

CSkinForm::~CSkinForm()
{
    skin_deinit(&m_skin_head);
    m_hWnd = HWND_INVALID;
    UnloadRes();
    FreeItems();

    //if (m_res)
    //{
    //    delete m_res;
    //    m_res = NULL;
    //}

    for(size_t i = 0; i < _Ctrlist.size(); i++)
    {
        if(_Ctrlist.at(i))
        {
            delete _Ctrlist.at(i);
        }
    }
    _Ctrlist.clear();
    _focusList.clear();
    JDEBUG(JERRO, "CSkinForm Destory\r\n");

    AchillesDBG("-=-=SkinForm.cpp=-=-CSkinForm::~CSkinForm\r\n");
}
static HWND curHwnd = HWND_INVALID;
void
CSkinForm::FreePicRes(int nres)
{
    if (m_Alloc_PicRes)
    {

        //for (int j = 0; j < nres; j++)
        //{
            //UnloadBitmap((PBITMAP) & (m_skin_head.bmps[j]));
       // }
        if(_iconGrp)
        {
            delete _iconGrp;
            _iconGrp = NULL;
        }

        if(_intenalIcons)
        {
            delete _intenalIcons;
            _intenalIcons = NULL;
        }

        if (m_skin_head.bmps)
        {
            delete[]m_skin_head.bmps;
            //m_res->num = 0;
            m_skin_head.bmps = NULL;
        }
    }
    m_Alloc_PicRes = false;
}
void CopyBitmap(PBITMAP srcBmp, PBITMAP dstBmp)
{
    memcpy(dstBmp,srcBmp,sizeof(BITMAP));
}
/*
bool GetLanguagePicPath(StringList& picList,const char **path, int pic_num)
{
    printf("come here1\n");
    string curLang;
    char* p= getenv("dt1000-lang");
    if(p == NULL){
        curLang = "chinese";
    }else
        curLang = p;
    printf("lang = %s\n",curLang.c_str());
    if( (curLang != "english") && (curLang != "chinese")){
        return false;
    }
    for(int i = 0; i < pic_num; i++){      
        string str = "../resource/"+curLang+"/"+ string(path[i]);
        std::cout << str << std::endl;
        picList.push_back(str);
    }
    return true;
}*/
bool CSkinForm::AllocPicRes(const char **path, int pic_num)
{

    if (m_Alloc_PicRes)
    {
            JDEBUG(JERRO, "Has alloc picres\n");
            return true;
    }
    //m_res->file_array = path;
    //m_res->num = pic_num;


    m_skin_head.bmps = (BITMAP *) new
            BITMAP[pic_num];
//==================assert======================
    assert(m_skin_head.bmps != NULL);
    if (m_skin_head.bmps == NULL)
    {
        JDEBUG(JERRO, "Can't alloc BITMAP\n");
        return false;
    }
/*
    StringList tmpPics;
    assert(GetLanguagePicPath(tmpPics,path,pic_num));
    for(size_t i = 0; i < tmpPics.size(); i++)
    {
        std::cout << tmpPics.at(i) << std::endl;
        _iconGrp->AddIcons(tmpPics.at(i));
    }*/
    _iconGrp->AddIcons(path,pic_num);
//==================assert======================
    assert(pic_num == _iconGrp->GetCount());

    IconList list = _iconGrp->GetIconList();
//==================assert======================
    assert(pic_num ==  list.size());

    for (int i = 0; i < pic_num; i++)
    {
        //==================assert======================
        assert(list.at(i) != NULL);
        PBITMAP tmpDst = (PBITMAP)(&m_skin_head.bmps[i]);
        PBITMAP tmpSrc = (list.at(i)->GetBitmap());
        assert(tmpDst && tmpSrc);
        CopyBitmap(tmpSrc,tmpDst);
        //==================assert======================
    }

    m_Alloc_PicRes = true;

    return true;
}

bool CSkinForm::HasLoadRes()
{
	//fprintf(stderr,"%s HasLoadRes\n",m_title);
	return m_Load_Res;
}

bool CSkinForm::LoadRes(const char **path, int pic_num)
{
	if (!AllocPicRes(path, pic_num))
	{
		JDEBUG(JERRO, "Can't alloc Pic res\n");
		return false;
	}

	m_Load_Res = true;

	return true;
}

bool CSkinForm::UnloadRes()
{
	if (!HasLoadRes())
	{
		JDEBUG(JERRO, "Has not load res\n");
		return false;
	}

        //FreePicRes(m_res->num);
        FreePicRes(0);

	m_Load_Res = false;
	JDEBUG(JINFO, "SkinForm UnLoadResource\n");

}

void
CSkinForm::InitSkinHeader(const char *p_name, int bk_bmp_index,
						  skin_item_t * p_item, int nr_items)
{

	strncpy(m_title, p_name, 32);
	m_skin_head.name = m_title;
	m_skin_head.style = SKIN_STYLE_TOOLTIP;
	m_skin_head.bk_bmp_index = bk_bmp_index;
	if (p_item == NULL)
	{
		m_skin_head.items = p_skin_items;
	}
	else
		m_skin_head.items = p_item;
	if (nr_items == 0)
	{
		m_skin_head.nr_items = m_items_cnt;
	}
	else
		m_skin_head.nr_items = nr_items;
	m_skin_head.attached = 0;
//	JDEBUG(JINFO,"%s InitSkinHeader\n", m_title);

}

void
CSkinForm::Close()
{
    if(m_hWnd != curHwnd)
    {
        fprintf(stderr,"====================CSkinForm::Close() mismatch m_hWnd=%x curHwnd=%x\n",m_hWnd,curHwnd);
        return;
    }
    m_bColse = true;
    m_Showflag = false;

    if(m_hWnd)
    {
        // 1.sync call ,when this function return,in this function the on_close will be called.

        //SendMessage(m_hWnd,MSG_CLOSE,0,0);
        OnClose ();
        destroy_skin_window(m_hWnd);
        UnRegisterForm(m_hWnd);
        m_hWnd = HWND_INVALID;
    }
}

void
CSkinForm::OnButtonClick(skin_item_t * p_item)
{

}


void
CSkinForm::OnGetFocus(skin_item_t * p_item)
{

}

void
CSkinForm::OnKillFocus(skin_item_t * p_item)
{

}
void CSkinForm::ProcessTabKey()
{
    if((_curFocusId == -1) && (_prevFocusId == -1))
    {
        _curFocusId  = 0;
        _prevFocusId = 0;
    }else
       _curFocusId = (_prevFocusId+1)%m_items_cnt;

    int x =  (p_skin_items+_curFocusId)->x;
    int y =  (p_skin_items+_curFocusId)->y;
    HWND newHwnd = GetDlgItem(m_hWnd,_curFocusId);
   //printf("curID = %d, prevID=%d,total = %d\n",_curFocusId,_prevFocusId,m_items_cnt);
   //printf("id = 0x%x 0x%x\n",p_skin_items[_curFocusId].id,p_skin_items[_prevFocusId].id);
   if(p_skin_items[_curFocusId].id == 0xaa55) 
   {
        if(p_skin_items[_prevFocusId].id == 0xaa55)
        {
           SetNullFocus(m_hWnd);
           SetFocusChild(newHwnd);
        }else{
           SetNullFocus(m_hWnd);
           SetFocusChild(newHwnd);
           PostMessage(m_hWnd,MSG_MOUSEMOVE,0,(y<<16)+x);
        }
   }else{
        if(p_skin_items[_prevFocusId].id == 0xaa55)
        {
            PostMessage(m_hWnd,MSG_MOUSEMOVE,0,(y<<16)+x);
            SendDlgItemMessage(m_hWnd,_prevFocusId,MSG_KILLFOCUS,0,0);
            SetNullFocus(m_hWnd);
        }else{
            PostMessage(m_hWnd,MSG_MOUSEMOVE,0,(y<<16)+x);
        }
   }
   _prevFocusId = _curFocusId;
}
void CSkinForm::ProcessEnterKey()
{
    //fprintf(stderr,"ProcessEnterKey\n");
    skin_item_t* p =   skin_get_hilited_item(&m_skin_head);
    if(p != NULL){
        event_cb_func(m_hWnd,p,SIE_BUTTON_CLICKED,0);
    }
}

int
CSkinForm::WinProc(HWND hWnd, int message, WPARAM wParam, LPARAM lParam,
				   int *p_result)
{
	//Add by Achilles end 2010-4-16
        //if( (hWnd != curHwnd) && (message != MSG_CREATE))
        //    return 0;
	if (message > MSG_USER)
	{
		OnUserMsg(hWnd, message, wParam, lParam);
		return 0;
	}
	switch (message)
	{
	case MSG_PAINT:
		OnPaint(hWnd);
		break;
	case MSG_TIMER:
		OnTimer(wParam);
		break;

	case MSG_CREATE:
		OnCreate();
		break;
	case MSG_SHOWWINDOW:
		{
			if (m_Showflag)
				break;
                        InstallCommCtrlHook(hWnd);
                        _EditHook();

			OnShow();
			m_Showflag = true;
			break;
		}
	case MSG_INITDIALOG:
		break;
	case MSG_KEYUP:
                //fprintf(stderr,"MSG_KEYUP code=0x%x\n",wParam);
                if(wParam == SCANCODE_F12)
                {
                    //exit(0);
                }else if(wParam == SCANCODE_ESCAPE)
                {

                    std::string titleStr = this->m_title;
                    //fprintf(stderr,"Close %s\n",titleStr.c_str ());
                    if(titleStr != "CLoginForm") {
                        if(curHwnd == hWnd)
                            Close();
                    }


                }else if(wParam == SCANCODE_TAB)
                {
                    //fprintf(stderr,"recv tab\n");
                    ProcessTabKey();
                }else if(wParam == SCANCODE_LEFTALT)
                {
                    //SendAsyncMessage(_mg_ime_wnd,MSG_IME_CLOSE,0,0);

                }else if(wParam == SCANCODE_ENTER){
                    ProcessEnterKey();
                }else if(wParam == SCANCODE_F8){
                    //ShowWindow(hWnd,SW_SHOWNORMAL);
                    //fprintf(stderr,"recv SCANCODE_F8\n");
                }else{}
		OnKeyUp(wParam, lParam);
		break;
	case MSG_LBUTTONDOWN:
        {
            int x_pos = LOSWORD (lParam);
            int y_pos = HISWORD (lParam);

            OnLButtonDown(x_pos, y_pos);
		break;
         }
        case MSG_LBUTTONDBLCLK:
        {

                int x_pos = LOSWORD (lParam);
                int y_pos = HISWORD (lParam);

                OnLButtonDbClick(x_pos, y_pos);

                break;
         }
	case MSG_COMMAND:
		OnCommand(hWnd, message, (int) wParam, (int) lParam);
		break;
	case MSG_CLOSE:
                OnClose();
		break;
	default:
		break;
	}
	return 0;
}

int
CSkinForm::msg_cb_func(HWND hWnd, int message, WPARAM wParam,
                       LPARAM lParam, int *p_result)
{
    if (hWnd == HWND_INVALID)
    {
        return 0;
    }
#if 1
    if(message == MSG_SHOWWINDOW)
    {
        //fprintf(stderr,"hWnd=0x%x recv showmsg\n",hWnd);
        curHwnd = hWnd;

    }



       if(hWnd != curHwnd)
        {

            if( (message == MSG_KEYUP) && (wParam==SCANCODE_ENTER)&&(wParam == SCANCODE_ESCAPE))
            {
                fprintf(stderr,"***********curHwnd=0x%x  hWnd=0x%x recv SCANCODE_ESCAPE&&SCANCODE_ENTER  msg %d\n",curHwnd,hWnd,message);
                return 0;
            }
            else if(message==MSG_CLOSE)
            {
                fprintf(stderr,"mismatch user msg=0x%x\n",message);
                fprintf(stderr,"***********curHwnd=0x%x  hWnd=0x%x recv MSG_CLOSE msg %d\n",curHwnd,hWnd,message);
                return 0;
            }

            else if(message==MSG_TIMER)
            {
                //fprintf(stderr,"***********curHwnd=0x%x  hWnd=0x%x recv msg %d\n",curHwnd,hWnd,message);
                return 0;
            }
 /*
            else if( (message >= MSG_LBUTTONDOWN)  && (message <= MSG_LBUTTONDBLCLK))
            {
                //fprintf(stderr,"button msg\n");
                return 0;
            }
            else if( (message >= MSG_DT_LBUTTONDOWN)  && (message <= MSG_DT_LBUTTONDBLCLK))
            {
                //fprintf(stderr,"button msg\n");
                return 0;
            }
            else if( (message == MSG_ERASEBKGND) || (message == MSG_PAINT))
            {
                return 0;
            }
        */
            else if(message > MSG_USER)
            {
                fprintf(stderr,"mismatch user msg=0x%x\n",message);
                return 0;
            }

            //fprintf(stderr,"***********curHwnd=0x%x  hWnd=0x%x recv msg %d\n",curHwnd,hWnd,message);


        }

#endif
    CSkinForm *p_form = LookForByHwnd(hWnd);

    int n;
    if (p_form)
    {
        n = p_form->WinProc(hWnd, message, wParam, lParam, p_result);
        return n;
    }

    //MSG_CB_LOCK;
    if ((p_form = p_PreForm) != NULL)
    {
        p_PreForm = NULL;
        //MSG_CB_UNLOCK;

        p_form->RegisterForm(hWnd, p_form);


        n = p_form->WinProc(hWnd, message, wParam, lParam, p_result);
        return  n;
    }

    //MSG_CB_UNLOCK;

    return 0;
}

int
CSkinForm::event_cb_func(HWND hWnd, skin_item_t * p_item, int event,
						 void *p_data)
{
    //EVENT_CB_LOCK;
    if ( (hWnd == HWND_INVALID) || (hWnd != curHwnd))
    {
        //EVENT_CB_UNLOCK;

        return 0;
    }

    CSkinForm *p_form = LookForByHwnd(hWnd);
    if (p_form == NULL)
    {
        if (hWnd != HWND_INVALID)
        {

            destroy_skin_window(hWnd);
            //EVENT_CB_UNLOCK;
            return 0;
        }
    }

	switch (event)
	{
	case SIE_BUTTON_CLICKED:
		if (p_form && !p_form->m_bColse) p_form->OnButtonClick(p_item);
		break;
	case SIE_SLIDER_CHANGED:
		if (p_form && !p_form->m_bColse) p_form->OnSliderChange(p_item);
		break;
	case SIE_GAIN_FOCUS:
		if (p_form && !p_form->m_bColse) p_form->OnGetFocus(p_item);
		break;
	case SIE_LOST_FOCUS:
		if (p_form && !p_form->m_bColse) p_form->OnKillFocus(p_item);
		break;
	default:
		break;
	}

    //EVENT_CB_UNLOCK;

	return 0;
}

void
CSkinForm::RegisterForm(HWND hWnd, CSkinForm * p_form)
{
    JDEBUG(JINFO,"RegisterForm hwnd = 0x%lx, form = %x%lx\n",hWnd,p_form);

    //FORMS_LOCK;

    if (hWnd == HWND_INVALID)
    {
        //FORMS_UNLOCK;
        return;
    }

	p_form->m_hWnd = hWnd;

    vector < CSkinForm * >::iterator iter;
    for (iter = m_Forms.begin(); iter != m_Forms.end(); iter++)
    {
        if (hWnd == (*iter)->m_hWnd)
        {
            break;
        }
    }

    if (iter == m_Forms.end())
    {
        m_Forms.push_back(p_form);
    }

    //FORMS_UNLOCK;

    //fprintf(stderr,"Add--- Forms's cnt = %d\n",m_Forms.size());
}

void
CSkinForm::UnRegisterForm(HWND hWnd)
{
    //FORMS_LOCK;

	vector < CSkinForm * >::iterator iter = m_Forms.begin();
	for (; iter != m_Forms.end();)
	{
		if (hWnd == (*iter)->m_hWnd)
			iter = m_Forms.erase(iter);
		else
			iter++;
	}

    //FORMS_UNLOCK;

    JDEBUG(JINFO,"UnRegisterForm hwnd = 0x%lx\n",hWnd);
    //printf("UnRegisterForm hwnd = 0x%lx\n",hWnd);
    JDEBUG(JINFO,"Del -- Forms's cnt = %d\n",m_Forms.size());
}

CSkinForm *
CSkinForm::LookForByHwnd(HWND hWnd)
{
    //FORMS_LOCK;
    if (hWnd == HWND_INVALID)
    {
        //FORMS_UNLOCK;
        return  NULL;
    }
    
	int cnt = m_Forms.size();

	for (int i = 0; i < cnt; i++)
	{
		if (m_Forms.at(i)->m_hWnd == hWnd)
		{
                    CSkinForm * form;
                    form = m_Forms.at(i);
            //FORMS_UNLOCK;
                    return form;
		}
	}

    //FORMS_UNLOCK;

	return NULL;
}


bool CSkinForm::_CommCtrlNotify(HWND hwnd, int id, int nc)
{
	this->OnCommCtrlNotify(hwnd, id, nc);

	return true;
}

//add_data is set by ctrl.not user
static void
_comm_ctrl_notify_proc(HWND hwnd, int id, int nc, DWORD add_data)
{
	
	//CSkinForm* frm = (CSkinForm * )add_data;
	CSkinForm *
		frm = (CSkinForm *) GetWindowAdditionalData(hwnd);

	if (frm)
		frm->_CommCtrlNotify(hwnd, id, nc);
	else
    {
		JDEBUG(JWARN,"NULL FROM\n");
    }
}
static WNDPROC old_edit_proc;
static int new_edit_proc(HWND hwnd, int message, WPARAM wParam, LPARAM lParam)
{

    if (message == MSG_CHAR) {
        DWORD my_style = GetWindowStyle(hwnd);
        //printf("mystyle = 0x%x char = %c\n",my_style,wParam);
        if ((my_style & ES_DIGIT_ONLY) && (wParam < '0' || wParam > '9'))
        {        
                return 0;
        }
        else if((my_style & ES_DECIMAL) && ( (wParam != '.') && (wParam < '0' || wParam > '9')))
        {
                return 0;
        }
#if 0
        else if((wParam == '\'')|| (wParam == '\"') || (wParam == ' ')||(wParam == ':'))
        {
                wParam=' ';
                return (*old_edit_proc) (hwnd, message, wParam, lParam);
        }
#endif
        else if(wParam == ':')
        {
               return 0;
        }
    }
    return (*old_edit_proc) (hwnd, message, wParam, lParam);
}
int
CSkinForm::_EditHook()
{
    for(int i = 0; i < m_items_cnt; i++)
    {
        if (p_skin_items[i].id == 0xaa55)
        {
            CTRLDATA *data = (CTRLDATA*)p_skin_items[i].type_data;
            string ctrlStr = data->class_name;
            if((ctrlStr == CTRL_EDIT) || (ctrlStr == CTRL_SLEDIT))
            {
                    HWND hCtrl = (HWND)p_skin_items[i].bmp_index;
                    if(hCtrl == HWND_INVALID)
                    {
                        JDEBUG(JERRO,"_Can't Get Edit's HWND\n");
                        return -1;
                    }
                    old_edit_proc = SetWindowCallbackProc(hCtrl, new_edit_proc);
                     
            }        
        }

    }
}
bool CSkinForm::InstallCommCtrlHook(HWND handle)
{
	//JDEBUG(JINFO,"install hook\n");
	for (int i = 0; i < m_items_cnt; i++)
	{
		//belong common ctrls
		if (p_skin_items[i].id == 0xaa55)
		{
			//p_skin_items[i].attached  = (DWORD)this;
			SetWindowAdditionalData(GetDlgItem
									(handle,
									 ((CTRLDATA *) p_skin_items[i].
									  type_data)->id), (DWORD) this);
			SetNotificationCallback(GetDlgItem
									(handle,
									 ((CTRLDATA *) p_skin_items[i].
									  type_data)->id),
									_comm_ctrl_notify_proc);

			JDEBUG(JINFO,"id = %d\n", \
				   ((CTRLDATA *) p_skin_items[i].type_data)->id);
		}
	}

	return true;

}

HWND CSkinForm::CreateForm(HWND hWnd, int lx, int ly, int rx, int by,
						   BOOL bModal)
{
	//m_skin_head.items[0].style &= ~SI_STATUS_HILIGHTED;
	if (!skin_init(&m_skin_head, event_cb_func, msg_cb_func))
	{
            JDEBUG(JERRO, "%s skin_init failed\n", m_title);
	}
	else
	{
            //MSG_CB_LOCK;
            p_PreForm = this;
            //MSG_CB_UNLOCK;
            ThrowAwayMessages(hWnd);
            m_hWnd =   create_skin_main_window_ex(&m_skin_head,hWnd,lx,ly,rx, by, WS_EX_NONE, bModal);
            CSkinForm * look = LookForByHwnd(m_hWnd);

            return m_hWnd;
	}
	return HWND_INVALID;
}

void
CSkinForm::OnPaint(HWND hWnd)
{
    HDC hdc = BeginPaint(hWnd);
    _intenalIcons->ShowAll(hdc);
    EndPaint(hWnd,hdc);
}

void
CSkinForm::OnCreate()
{

}

void
CSkinForm::OnTimer(int ID)
{

}

void
CSkinForm::OnUserMsg(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{

}

void
CSkinForm::OnClose()
{

}

void
CSkinForm::OnShow()
{

}

void
CSkinForm::OnEditChange(HWND hEdit, char key)
{

}

void
CSkinForm::OnCommCtrlNotify(HWND hwnd, int id, int nc)
{

}

bool CSkinForm::RegisterHotKey(HWND hWnd, int id, int fsModifiers, int vk)
{

	g_HotkeySet.push_back(HOTKEY(hWnd, id, fsModifiers, vk));

	return true;
}

void
CSkinForm::SerachHotKey(int scancode, DWORD shiftstate)
{
	int i = 0;
        fprintf(stderr,"serach hotkey\n");
	for (i = 0; i < g_HotkeySet.size(); i++)
	{
		if (g_HotkeySet.at(i).m_vk == scancode)
		{
                    PostMessage(g_HotkeySet.at(i).m_hwnd,0x890,0,scancode);
		}
	}
}

void
CSkinForm::OnKeyUp(int scancode, DWORD shiftstate)
{

}

void
CSkinForm::OnLButtonDown(int x, int y)
{

}
void
CSkinForm::OnLButtonDbClick(int x, int y)
{

}

void
CSkinForm::OnSliderChange(skin_item_t * p_item)
{

}

void
CSkinForm::OnCommand(HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
{

}

int
CSkinForm::AddSkinItem(DWORD style, int bmpidx, int left, int top,
					   void *type_data)
{

	//printf("skin_items=%x,cnt=%d\n",p_skin_items,m_items_cnt);
	p_skin_items =
		(skin_item_t *) realloc(p_skin_items,
								(m_items_cnt + 1) * sizeof(skin_item_t));
	memset((void *) &p_skin_items[m_items_cnt], 0, sizeof(skin_item_t));

	p_skin_items[m_items_cnt].id = m_items_cnt;
	p_skin_items[m_items_cnt].style = style;
	p_skin_items[m_items_cnt].bmp_index = bmpidx;
	p_skin_items[m_items_cnt].x = left;
	p_skin_items[m_items_cnt].y = top;
        if((style&SKIN_BMPLBL_STYLE) || (style&SI_TYPE_NRMSLIDER)/*Add by Achilles 2010-9-2*/)
            p_skin_items[m_items_cnt].type_data = type_data;
        //p_skin_items[m_items_cnt].type_data = new char[128];
        //bzero(p_skin_items[m_items_cnt].type_data,128);
        //if(type_data)
        //strncpy((char*)p_skin_items[m_items_cnt].type_data,(const char*)type_data,128);

	return m_items_cnt++;
}

int
CSkinForm::AddSkinItem(DWORD style, skin_item_t * p_skin)	//Add by Achilles 2009-11-26
{
	p_skin_items =
		(skin_item_t *) realloc(p_skin_items,
								(m_items_cnt + 1) * sizeof(skin_item_t));
	//memset((void*)&p_skin_items[m_items_cnt], 0, sizeof(skin_item_t));
	memcpy((void *) &p_skin_items[m_items_cnt], (void *) p_skin,
		   sizeof(skin_item_t));
	return m_items_cnt++;
}
int
CSkinForm::AddCommItem(DWORD style, CTRLDATA * p_item)
{

	if (p_item == NULL)
		return -1;
    if(p_item->id < 100)
    {
        JDEBUG(JWARN,"CommItem id must >= 100\n");
    //    exit(-1);
    }
	//printf("skin_items=%x,cnt=%d\n",p_skin_items,m_items_cnt);
	p_skin_items =
		(skin_item_t *) realloc(p_skin_items,
								(m_items_cnt + 1) * sizeof(skin_item_t));
	memset((void *) &p_skin_items[m_items_cnt], 0, sizeof(skin_item_t));
	p_skin_items[m_items_cnt].id = 0xaa55;
	p_skin_items[m_items_cnt].style = style;
	p_skin_items[m_items_cnt].type_data = p_item;
        if(p_item->id == -1)
            p_item->id = m_items_cnt++;
	return p_item->id;
}
void
CSkinForm::FreeItems()
{
	if (p_skin_items)
	{
		free((void *) p_skin_items);
		//p_skin_items = NULL;
	}
	p_skin_items = NULL;
}

void
CSkinForm::SetItemStatus(int id, DWORD status)
{
	if (id < m_items_cnt)
	{
		p_skin_items[id].style = status;
	}
}

DWORD CSkinForm::GetItemStatus(int id)
{
	if (id < m_items_cnt)
	{
		return p_skin_items[id].style;
	}
	return 0;
}
bool CSkinForm::GetCheckStatus(int id)
{
    return (GetItemStatus(id) & SI_BTNSTATUS_CHECKED);

}
void CSkinForm::SetCheckStatus(int id,bool check)
{
    if(check)
        p_skin_items[id].style |= SI_BTNSTATUS_CHECKED;
    else
        p_skin_items[id].style &= (~SI_BTNSTATUS_CHECKED);
}

bool CSkinForm::FillBoxWithBitmapEx(HDC hdc, skin_bmp_t * p_bmp_t)	//Add by Achilles 2009/11/27 11:31:07
{
	if (p_bmp_t)
		return FillBoxWithBitmap(hdc, p_bmp_t->x, p_bmp_t->y, p_bmp_t->w,
								 p_bmp_t->h, &(p_bmp_t->m_bmp));
	else
		return false;
}
HWND CSkinForm::GetItemHwnd(int id)
{
    if(m_hWnd)
        return GetDlgItem(m_hWnd,id);
    return HWND_INVALID; 
}
string CSkinForm::GetItemText(int id)
{
    char buf[256] = {0,};
    string strText = "";
    HWND h = GetItemHwnd(id);
    if(h != HWND_INVALID)
    {
        GetWindowText(h,buf,256);
        strText = string(buf);
    }
    return strText;

}
bool   CSkinForm::SetItemText(int id,string strText)
{
    HWND h = GetItemHwnd(id);
    if(h != HWND_INVALID)
    {
        SetWindowText(h,strText.c_str());
        return true;
    }
    return false;
    
}
bool   CSkinForm::SetItemText(int id,char*  szText)
{
    if((szText == NULL) || (szText[0] == '\0'))
    {
        return false;
    }
    return SetItemText(id,string(szText));
}
bool  CSkinForm::SetSkinlableText(int id, char* strText)
{
   return skin_set_item_label(&m_skin_head,id,strText);
}
bool  CSkinForm::SetSkinlableText(int id, string strText)
{
   return skin_set_item_label(&m_skin_head,id,strText.c_str());
}
void   CSkinForm::AddCtrl(CCtrl* ctrl)
{
    assert(ctrl);

    int index = ctrl->GetId();
    std::string typeName = ctrl->GetTypeName();
    if( (typeName == CTRL_EDIT) || (typeName == CTRL_COMBOBOX))
    {
         _focusList.push_back(index);
    }

    _Ctrlist.push_back(ctrl);
}
void   CSkinForm::DelCtrl(CCtrl* ctrl)
{
    vector < CCtrl * >::iterator iter = _Ctrlist.begin();
    for (; iter != _Ctrlist.end();)
    {
            if (ctrl == (*iter))
            {
                iter = _Ctrlist.erase(iter);
            }
            else
                    iter++;
    }
}
#define VERSION 1380
extern "C"
{
    int          getVersionCode()
    {
        return VERSION;
    }
    std::string  getVersionString()
    {
        return __DATE__;
    }
}
void CSkinForm::DrawMyText(HDC hdc,CFont* font, RECT *rect, std::string text, int opt)
{
    if( (rect == NULL) || (font == NULL))
        return;
    if(opt == 0)
    {
        //opt = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
    }
    SelectFont (hdc,font->pfont);
    SetBkMode (hdc,BM_TRANSPARENT);
    SetTextColor (hdc,font->font_color);
    DrawText(hdc,text.c_str(),text.length (),rect,opt);
}
