// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef _WIN32_SOCK_DLL_STDAFX_H
#define _WIN32_SOCK_DLL_STDAFX_H
#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifndef WINVER
#define WINVER 0x0500
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0500
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0500
#endif
// Unicode lib
#include <tchar.h>
// C lib
#include <conio.h>
#include <stdio.h>
#include <string.h>
// Socket2 lib
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
// Microsoft Socket lib
#include <mswsock.h>
#pragma comment(lib, "mswsock.lib")

#endif // _WIN32_SOCK_DLL_STDAFX_H