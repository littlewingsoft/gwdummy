#include "stdafx.h"
#include "CConsole.h"


//=============================================================================
//	Name: ������, �Ҹ���
//	Desc:  
//	Call: 
//=============================================================================
CConsole_IO::CConsole_IO()
{
	m_hIn = GetStdHandle(STD_INPUT_HANDLE);
	m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if( INVALID_HANDLE_VALUE == m_hIn 
		|| INVALID_HANDLE_VALUE == m_hOut )
	{
		std::cout << "Fatal error : hConsole is INVALID_HANDLE_VALUE" << std::endl;
		std::cout << "Program aborted." << std::endl;
		exit(1);
	}

	m_DefaultColor = WHITE;
}

CConsole_IO::~CConsole_IO()
{

}


//=============================================================================
//	Name: SetConsoleDefaultColor
//	Desc: Console���� ����� ����Ʈ ���� �����Ѵ�.
//	Call: 
//=============================================================================
void CConsole_IO::SetConsoleDefaultColor( WORD wTextColor )
{
	SetConsoleTextAttribute( m_hIn, wTextColor );
	SetConsoleTextAttribute( m_hOut, wTextColor );

	m_DefaultColor = wTextColor;
}


//=============================================================================
//	Name: OutputConsoleString
//	Desc: Console�� ������ ������ �ؽ�Ʈ�� ǥ��
//	Call: 
//=============================================================================
void CConsole_IO::OutputConsoleStringA( LPCSTR szString, WORD wTextColor )
{
	if( 0 == wTextColor )
		SetConsoleTextAttribute( m_hOut, m_DefaultColor );
	else
		SetConsoleTextAttribute( m_hOut, wTextColor );

	DWORD dw = 0;
	WriteConsole( m_hOut, szString, (DWORD)strlen(szString), &dw, NULL );
}

void CConsole_IO::OutputConsoleStringW( LPCWSTR szString, WORD wTextColor )
{
	if( 0 == wTextColor )
		SetConsoleTextAttribute( m_hOut, m_DefaultColor );
	else
		SetConsoleTextAttribute( m_hOut, wTextColor );

	DWORD dw = 0;
	WriteConsole( m_hOut, szString, (DWORD)wcslen(szString), &dw, NULL );
}


//=============================================================================
//	Name: SetConsoleWindowText
//	Desc: Console�� title �ؽ�Ʈ ����
//	Call: 
//=============================================================================
BOOL CConsole_IO::SetConsoleWindowTextA( LPCSTR szTitle )
{
	return SetConsoleTitleA( szTitle );
}

BOOL CConsole_IO::SetConsoleWindowTextW( LPCWSTR szTitle )
{
	return SetConsoleTitleW( szTitle );
}


//=============================================================================
//	Name: GetConsoleInputString
//	Desc: Console���� ���ڿ��� �Է¹޴´�
//	Call: 
//=============================================================================
DWORD CConsole_IO::GetConsoleInputStringA( LPSTR szString, DWORD dwSize, WORD wInputColor )
{
	if( 0 == wInputColor )
		SetConsoleTextAttribute( m_hOut, m_DefaultColor );
	else
		SetConsoleTextAttribute( m_hOut, wInputColor );

	DWORD dw = 0;
	ReadConsole( m_hIn, szString, dwSize, &dw, NULL);
	// Enter �Է½� 0����
	if( 0 == stricmp(szString, "\r\n") || 0 == dw )
		return 0;
	return dw-2;
}

DWORD CConsole_IO::GetConsoleInputStringW( LPWSTR szString, DWORD dwSize, WORD wInputColor )
{
	if( 0 == wInputColor )
		SetConsoleTextAttribute( m_hOut, m_DefaultColor );
	else
		SetConsoleTextAttribute( m_hOut, wInputColor );

	DWORD dw = 0;
	ReadConsole( m_hIn, szString, dwSize, &dw, NULL);
	// Enter �Է½� 0����
	if( 0 == wcsicmp(szString, L"\r\n") || 0 == dw )
		return 0;
	return dw-2;
}


//=============================================================================
//	Name: SetConsoleCtrlCallback
//	Desc: ����� ��Ʈ�� �ڵ鷯�� ����Ʈ�� �߰�.. Ư�� �̺�Ʈ�� ó���� �Ѵ�
//	Call: 
//=============================================================================
BOOL CConsole_IO::SetConsoleCtrlCallback( PHANDLER  pHandler, BOOL fAdd )
{
	return SetConsoleCtrlHandler( (PHANDLER_ROUTINE)pHandler, fAdd );
}
