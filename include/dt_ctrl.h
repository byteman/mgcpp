#ifndef DT_CTRL_H
#define DT_CTRL_H
#include "SkinForm.h"
class CCtrl
{
public:
    CCtrl();
    CCtrl(CSkinForm* parent,std::string typeName="Ctrl");
    void SetCtrlParentAndName(CSkinForm* parent,std::string typeName);
    void RegisterCtrl(CCtrl* ctrl);
    bool EnableOwnStyle(bool yes);
    virtual ~CCtrl();
    virtual int GetId();
    virtual void  Show(){};
    virtual void  Hide(){};
    std::string& GetTypeName();
    virtual bool    CanFocus();
    void    SetFocus();
    CSkinForm* _parent;
protected:

    int _id;
    std::string _typeName;
};

#define SEND_CMD0(cmd) \
		do \
		{	 \
				if( (_parent) && (_parent->m_hWnd != HWND_INVALID)) \
		    { \
		         SendDlgItemMessage (_parent->m_hWnd, _data->id, cmd, 0,0); \
		    }	\
		}while(0)
	
    
#define SEND_CMD1(cmd,wParam) \
                    do \
                    {	 \
                        if( (_parent) && (_parent->m_hWnd != HWND_INVALID)) \
                        { \
                             SendDlgItemMessage (_parent->m_hWnd, _data->id, cmd, wParam,0); \
                        }	\
                    }while(0)
    
#define SEND_CMD2(cmd,wParam,lParam) \
                        do \
                        {	 \
                            if( (_parent) && (_parent->m_hWnd != HWND_INVALID)) \
                            { \
                                 SendDlgItemMessage (_parent->m_hWnd, _data->id, cmd, (WPARAM)wParam,(LPARAM)lParam); \
                            }	\
                        }while(0)
#endif // DT_CTRL_H
