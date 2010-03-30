#ifndef _CCONSILE_IO_H_
#define _CCONSILE_IO_H_

#include <iostream>
#include <windows.h>
//#include <tchar.h>



// Text Color
#define LIGHTBLUE				9
#define LIGHTGREEN				10
#define LIGHTRED				12
#define YELLOW					14
#define WHITE					15

// console callback type
typedef BOOL ( *PHANDLER )( DWORD );


//===========================================================
//	MODULE ID	:	CConsole_IO
//	DIRECTOR	:	황태윤
//	VERSION 	:	1.0.0	    ( 1.0.0 : 2007/08/12  )
//	DESCRIPTION :   Console의 IO를 처리하는 객체.
//
//	UPDATE      :
//===========================================================

class CConsole_IO
{
public:
	CConsole_IO();
	~CConsole_IO();

	void SetConsoleDefaultColor( WORD wTextColor = 0 );
	void OutputConsoleStringA( LPCSTR szString, WORD wTextColor = 0 );
	void OutputConsoleStringW( LPCWSTR szString, WORD wTextColor = 0 );
	BOOL SetConsoleWindowTextA( LPCSTR szTitle );
	BOOL SetConsoleWindowTextW( LPCWSTR szTitle );
	DWORD GetConsoleInputStringA( LPSTR szString, DWORD dwSize, WORD wInputColor = 0 );
	DWORD GetConsoleInputStringW( LPWSTR szString, DWORD dwSize, WORD wInputColor = 0 );

	BOOL SetConsoleCtrlCallback( PHANDLER pHandler, BOOL fAdd );

private:
	HANDLE	m_hIn;				// 표준입력 핸들
	HANDLE	m_hOut;				// 표준출력 핸들
	WORD	m_DefaultColor;		// 디폴트 칼라

};

#ifndef _UNICODE
#define OutputConsoleString OutputConsoleStringA
#else
#define OutputConsoleString OutputConsoleStringW
#endif

#ifndef _UNICODE
#define SetConsoleWindowText SetConsoleWindowTextA
#else
#define SetConsoleWindowText SetConsoleWindowTextW
#endif

#ifndef _UNICODE
#define GetConsoleInputString GetConsoleInputStringA
#else
#define GetConsoleInputString GetConsoleInputStringW
#endif

#endif //_CCONSILE_IO_H_
