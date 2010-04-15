/*
	The author		: jazonsim
	Create Date		: 1998/10/09

	Modify Date		: 2004/06/08 - FILE_SHARE_READ ¼öÁ¤
*/
#include "WinFile.h"


BOOL CWinFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags) 
{
	DWORD dwAccess = 0;
	switch(nOpenFlags & 3) {
	case modeRead:
		dwAccess = GENERIC_READ;
		break;
	case modeWrite:
		dwAccess = GENERIC_WRITE;
		break;
	case modeReadWrite:
		dwAccess = GENERIC_READ | GENERIC_WRITE;
		break;
	default :
		return FALSE;
	}
	DWORD dwShareMode = 0;
	switch (nOpenFlags & 0x70)
	{
		/*
	case shareCompat:
	case shareExclusive:
		dwShareMode = 0;
		break;
		*/
	case shareDenyWrite:
		dwShareMode = FILE_SHARE_READ;
		break;
	case shareDenyRead:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case shareDenyNone:
		dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
		break;
	default:
		return FALSE;
	}
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;
	DWORD dwCreateFlag;
	if(nOpenFlags & modeCreate) {
		if(nOpenFlags & modeNoTruncate) dwCreateFlag = OPEN_ALWAYS;
		else dwCreateFlag = CREATE_ALWAYS;
	} else dwCreateFlag = OPEN_EXISTING;

	HANDLE hFile = ::CreateFile(lpszFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;
	m_hFile = (int)hFile;

	return TRUE;
}

BOOL CWinFile::OpenRead(LPCTSTR lpszFileName) 
{
	//DWORD dwShareMode = 0;				// for Win95/98
	DWORD dwShareMode = FILE_SHARE_READ;	// for WinME/XP/2000/2003

	HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_READ, 
		dwShareMode,			
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE) return FALSE;
	m_hFile = (int)hFile;

	return TRUE;
}

BOOL CWinFile::OpenWrite(LPCTSTR lpszFileName) 
{
	HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_WRITE, 0, 
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;
	m_hFile = (int)hFile;

	return TRUE;
}

BOOL CWinFile::OpenReadWrite(LPCTSTR lpszFileName) 
{
	HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_READ | GENERIC_WRITE, 0, 
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE) return FALSE;
	m_hFile = (int)hFile;

	return TRUE;
}

void CWinFile::Close() 
{
	if(m_hFile == -1) return;
	::CloseHandle((HANDLE)m_hFile);
	m_hFile = -1;
}

BOOL CWinFile::Write(const void* lpBuf, UINT nCount) 
{
#ifdef _DEBUG
	if(nCount == 0) return FALSE;
	if(lpBuf == 0) return FALSE;
#endif
	DWORD nWritten;
	return WriteFile((HANDLE)m_hFile, lpBuf, nCount, &nWritten, NULL);
}

LONG CWinFile::Seek(LONG lOff, UINT nFrom) 
{
	return SetFilePointer((HANDLE)m_hFile, lOff, NULL, (DWORD)nFrom);
}

DWORD CWinFile::GetLength() 
{
	DWORD dwCur = Seek(0L, current);
	DWORD dwLen = SeekToEnd();
	Seek(dwCur, begin);
	return dwLen;
}