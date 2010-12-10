#ifndef DT_IPADDR_H
#define DT_IPADDR_H
#include "dt_commctrl.h"
#define MAX_TEXT_LENGTH 256
//#define CTRL_IP_ADDRESS "ipaddr"
#define DEF_IPADDR_EXSTYLE WS_EX_TRANSPARENT
#define DEF_IPADDR_STYLE   WS_TABSTOP|WS_VISIBLE|IPS_CENTER|IPS_VCENTER|IPS_NOTIFY
class CIpAddr:public CCommCtrl
{
public:
    //CIpAddr();
    CIpAddr(COMM_CTRL_DESC* desc,CSkinForm* parent,string typeName=CTRL_IP_ADDRESS);
    virtual ~CIpAddr();
    bool setAddress(std::string strIp);
    std::string getAddress();
};

#endif // DT_IPADDR_H
