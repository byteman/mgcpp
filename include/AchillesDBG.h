#ifndef _ACHILLES_DBG_H
#define _ACHILLES_DBG_H
#undef Achilles_DEBUG
#ifdef Achilles_DEBUG
#define AchillesDBG printf
#else
inline void Achillesdebug(const char *format, ...){}
#define AchillesDBG 1?((void)0):Achillesdebug
#endif

#endif //_ACHILLES_DBG_H

