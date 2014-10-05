//////////////////////////////////////////////////////////////////////////
//
// tags.h - TAGS: Yet Another Tag Reading Library for BASS 2.3+
//
// Author: Wraith, 2k5-2k6
// Public domain. No warranty.
//
// (public)
// 
// Abstract:    reads tags from given BASS handle, formats them according
//              to given format string and returns the resulting string.
//           
// read tags-readme.txt for details
//

#ifndef _YATRL_H_W2348_H4232
#define _YATRL_H_W2348_H4232

#include "bass.h"

#ifdef __cplusplus
extern "C" {
#endif

// Current version. Just increments each release.
#define TAGS_VERSION 17

// returns description of the last error.
const char* WINAPI TAGS_GetLastErrorDesc();

// main purpose of this library
const char* WINAPI TAGS_Read( DWORD dwHandle, const char* fmt );
const char* WINAPI TAGS_ReadEx( DWORD dwHandle, const char* fmt, DWORD tagtype );

// retrieves the current version
DWORD WINAPI TAGS_GetVersion();

#ifdef __cplusplus
}
#endif


#endif
