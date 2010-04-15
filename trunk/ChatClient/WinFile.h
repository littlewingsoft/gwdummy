/*
	The author		: jazonsim
	Create Date		: 1998/10/09

	Modify Date		: 2001/07/10
*/
#ifndef __WINFILE_H
#define __WINFILE_H


#include <windows.h>


class  CWinFile 
{
protected:
	int m_hFile;
public:
	enum OpenFlags {
		modeRead =          0x0000,
		modeWrite =         0x0001,
		modeReadWrite =     0x0002,
		shareCompat =       0x0000,
		shareExclusive =    0x0010,
		shareDenyWrite =    0x0020,
		shareDenyRead =     0x0030,
		shareDenyNone =     0x0040,
		modeNoInherit =     0x0080,
		modeCreate =        0x1000,
		modeNoTruncate =    0x2000,
		typeText =          0x4000,
		typeBinary =   (int)0x8000
		};
/*
	enum Attribute {
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20
		};
*/
	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

	CWinFile() : m_hFile(-1) {}
	virtual ~CWinFile() {
		Close();
	}

	int GetHandle() {
		return m_hFile;
	}
	void SetHandle(int hHandle) {
		m_hFile = hHandle;
	}
	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	virtual BOOL OpenRead(LPCTSTR lpszFileName);
	virtual BOOL OpenWrite(LPCTSTR lpszFileName);
	virtual BOOL OpenReadWrite(LPCTSTR lpszFileName);
	virtual void Close();
	virtual BOOL Read(void* lpBuf, UINT nCount);
	virtual BOOL Write(const void* lpBuf, UINT nCount);
	virtual LONG Seek(LONG lOff, UINT nFrom = 0x1);
	virtual void SeekToBegin(LONG lOff = 0L) {
		Seek(lOff, begin);
	}
	virtual DWORD SeekToCurrent(LONG lOff) {
		return Seek(lOff, current);
	}
	virtual DWORD SeekToEnd(LONG lOff = 0L) {
		return Seek(lOff, end);
	}
	virtual DWORD GetLength();
};

inline BOOL CWinFile::Read(void* lpBuf, UINT nCount) {
#ifdef _DEBUG
	if(nCount == 0) return FALSE;
	if(lpBuf == NULL) return FALSE;
#endif
	DWORD dwRead;
#ifdef _DEBUG
	BOOL b = ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL);
	if(dwRead != nCount) ::MessageBox(NULL, "Read Size Different", "Error", MB_OK | MB_ICONERROR);
	return b;
#else
	return ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL);
#endif
}

#endif
