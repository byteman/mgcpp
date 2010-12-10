#ifndef	__CLASS_H__
#define	__CLASS_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include <minigui/mgext.h>
#include <minigui/skin.h>
#include <assert.h>

#include "AchillesDBG.h"
#define IME_X        495
#define IME_Y        438
#define IME_W        300
#define IME_H        40

#define JINFO	1
#define JWARN	2
#define JERRO	3

#ifdef JDEBUG_ENABLED

#define JDEBUG(t, args...) 																																				\
	if (t == JINFO) {																																								\
		printf ("\033[36;40mINFO:: %s:%d [%s] \033[37;40m", __FILE__, __LINE__, __PRETTY_FUNCTION__);	\
	} else if (t == JWARN) {																																				\
		printf ("\033[33;40mWARN:: %s:%d [%s] \033[37;40m", __FILE__, __LINE__, __PRETTY_FUNCTION__);	\
	} else if (t == JERRO) {																																				\
		printf ("\033[31;40mERRO:: %s:%d [%s] \033[37;40m", __FILE__, __LINE__, __PRETTY_FUNCTION__);	\
	}																																																\
	printf(args);																																										\
	fflush(stdin);																																									\

#else

#define JDEBUG(t, args...) 

#endif

#ifdef DEBUG
#define dbg(fmt...) fprintf(stderr,fmt);
#else
#define dbg(fmt...) do { } while (0)
#endif

#define dbg_trace dbg("%s %d\n",__FILE__,__LINE__)

//IC卡消息
#define MSG_USER_IC_INFO        (MSG_USER + 100)
//称重消息
#define MSG_USER_WETTING_NOTIFY (MSG_USER+101)
        //
#define MSG_USER_IME_STATUS     (MSG_USER+102)
#define MSG_USER_INPUT          (MSG_USER+103)
#define MSG_USER_DIG_AD         (MSG_USER+104)

#endif

