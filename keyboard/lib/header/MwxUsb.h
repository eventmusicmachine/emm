#ifndef MWXUSB_H
#define MWXUSB_H

#include "windows.h"

typedef unsigned char (OPEN_USB)(void);
typedef unsigned char (CLOSE_USB)(void);
typedef unsigned char (ACCEPT_LED)(int value);
typedef void (SET_CALLBACK)(void (__stdcall *lpfn)(int));
typedef unsigned char (READ_POS_KEY_USB)(int *cpData1,DWORD dwTime);


#endif // MWXUSB_H
