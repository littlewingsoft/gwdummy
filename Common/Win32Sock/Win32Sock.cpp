// Win32Sock.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "IOCPManager.h"
#include "Win32Sock.h"
#include "lzf.h"
#include <time.h>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

LONG ExceptionFilter(LPEXCEPTION_POINTERS pExceptionInfo, LPCSTR szPosition)
{
	PEXCEPTION_RECORD	lpExceptionRecord		= pExceptionInfo->ExceptionRecord;
	DWORD				dwExceptionCode			= lpExceptionRecord->ExceptionCode;
	LPVOID				lpExceptionAddress		= lpExceptionRecord->ExceptionAddress;
	TCHAR				szExceptionInfo[256]	= { _T( "" ) };
	wsprintf( szExceptionInfo, _T( "Code:0x%08X  Address:0x%p at %s" ), \
              dwExceptionCode, lpExceptionAddress, szPosition );
	LPTSTR lpExceptionInfo = szExceptionInfo + _tcslen( szExceptionInfo );
	if ( dwExceptionCode == EXCEPTION_ACCESS_VIOLATION )
	{
		LPSTR lp = lpExceptionRecord->ExceptionInformation[0] ? "write":"read";
		wsprintf( lpExceptionInfo, TEXT("Attempt to %s data at 0x%p.\r\n"), lp, 
                  lpExceptionRecord->ExceptionInformation[1] );
	}
#ifdef _DEBUG
//    MessageBox( NULL, szExceptionInfo, szPosition, MB_OK | MB_ICONWARNING );
#endif
	char szLogFileName[256];	memset( szLogFileName, 0, 256);
	FILE* pFile = NULL;
	struct tm when;
	__time64_t now;

	_time64( &now );
	when = *_localtime64( &now );
	char szFinalLog[512];
	memset(szFinalLog, 0, 512);
	sprintf(szFinalLog, "%d-%d-%d %d:%d:%d %s\r\n", \
		when.tm_year+1900, when.tm_mon+1, when.tm_mday, when.tm_hour, when.tm_min, when.tm_sec, szExceptionInfo);
	strcpy(szLogFileName, "win32sock.log");
	pFile = fopen(szLogFileName, "a");
	if( !pFile )
		return EXCEPTION_EXECUTE_HANDLER;
	fseek(pFile, 0L, SEEK_END);
	fwrite(szFinalLog, strlen(szFinalLog), 1, pFile);
	fclose(pFile);
/*  TCHAR szSysTime[32];
    SYSTEMTIME SystemTime; GetLocalTime( &SystemTime );
    wsprintf( szSysTime, _T( "%d-%02d-%02d %02d:%02d:%02d: " ), SystemTime.wYear, \
              SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, \
              SystemTime.wSecond );
    TCHAR szLogFile[MAX_PATH];
    GetModuleFileName( NULL, szLogFile, sizeof( szLogFile ) / sizeof( TCHAR ) );
    if ( _tcslen( szLogFile ) > 0 ) _tcscat( szLogFile, _T( ".Exception.Log" ) );
    HANDLE hLogFile = CreateFile( szLogFile, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, \
                                  OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    if ( hLogFile != NULL )
    {
        DWORD dwBytes = 0, dwWriteBytes = ( DWORD )_tcslen( szSysTime ) * sizeof( TCHAR );
        WriteFile( hLogFile, szSysTime, dwWriteBytes, &dwBytes, NULL );
        dwWriteBytes = ( DWORD )_tcslen( szExceptionInfo ) * sizeof( TCHAR );
        WriteFile( hLogFile, szExceptionInfo, dwWriteBytes, &dwBytes, NULL );
        CloseHandle( hLogFile );
    }
*/
//#endif
	return ( EXCEPTION_EXECUTE_HANDLER );
}

CIOCPManager	g_Iocp;
CMemoryCatch	g_MemoryPool;

bool IOCPStartup(CSockManager* pSockManager, DWORD dwThreadsCount, bool display)
{
    return ( g_Iocp.StartUp(pSockManager, dwThreadsCount, display) );
}

void IOCPCleanup()
{
    g_Iocp.CleanUp();
}

CWin32Sock::CWin32Sock() 
{ 
	m_hSocket = INVALID_SOCKET;
	m_dwReadSize = 8192;
	m_byStatus = STATUS_DISCONNECTED;
}

CWin32Sock::~CWin32Sock() 
{ 
	Close();
}

void* CWin32Sock::operator new( size_t dwBytes )
{
    return (g_MemoryPool.NewHeapMemory(dwBytes));
}
void* CWin32Sock::operator new[]( size_t dwBytes )
{
    return (g_MemoryPool.NewHeapMemory(dwBytes));
}

void CWin32Sock::operator delete( void* lpData )
{
    g_MemoryPool.DelHeapMemory(lpData);
}

void CWin32Sock::operator delete[]( void* lpData )
{
    g_MemoryPool.DelHeapMemory(lpData);
}

bool CWin32Sock::Create()
{
    __try
    {
        if(m_hSocket != INVALID_SOCKET) return true;
        m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
        return (m_hSocket != INVALID_SOCKET);
    }
	__except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Create") ) {return false;}
    return true;
}

void CWin32Sock::Close()
{
    LPVOID lpDataBuff = NULL;
    __try
    {
		if(m_byStatus == STATUS_DISCONNECTED)
			return;
        DWORD dwBuffSize = (DWORD)sizeof(IOCP_BUFFER);
		lpDataBuff = g_Iocp.m_MemoryPool.NewHeapMemory(dwBuffSize);
        LPIOCP_BUFFER lpOvlHead = (LPIOCP_BUFFER)lpDataBuff;
        memset(lpOvlHead, 0, dwBuffSize);
        LPWSAOVERLAPPED lpOvl = &(lpOvlHead->Overlapped);
		lpOvlHead->dwOperation = OVL_CLOSE;
		BOOL fResult = PostQueuedCompletionStatus( g_Iocp.m_hIOCPort, 0, (ULONG_PTR)this, lpOvl );
		if(fResult==FALSE) {
			DWORD dwError = GetLastError();
			printf("Close Post Error[%d]...\r\n", dwError);
			g_Iocp.m_MemoryPool.DelHeapMemory(lpDataBuff);
		}
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Close") )
    {
        g_Iocp.m_MemoryPool.DelHeapMemory(lpDataBuff);
    }
}

bool CWin32Sock::Listen(LPCSTR szHost, unsigned short usPort)
{
    __try
    {
		struct linger lingerOpt;
		lingerOpt.l_onoff = 1;
		lingerOpt.l_linger = 0;

		setsockopt(m_hSocket, SOL_SOCKET, SO_LINGER, (char *)&lingerOpt, sizeof(lingerOpt));

		int opt=1;
//		if(setsockopt(m_hSocket, SOL_SOCKET, SO_DONTLINGER, (const char*)&opt, sizeof(opt))==SOCKET_ERROR)
//			return false;
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt))==SOCKET_ERROR)
			return false;
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&opt, sizeof(opt))==SOCKET_ERROR)
			return false;

		struct sockaddr_in addr;
		memset((void *)&addr, 0, sizeof(addr));
		addr.sin_family				= AF_INET;
		addr.sin_port				= htons(usPort);
	    if(szHost == NULL) {
			addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	    }
	    else {
		    addr.sin_addr.s_addr	= inet_addr(szHost);
		    if(addr.sin_addr.s_addr == INADDR_NONE) {
			    LPHOSTENT lpHosten = gethostbyname(szHost);
			    if(lpHosten == NULL) return false;
			    addr.sin_addr.s_addr  = ((LPIN_ADDR)lpHosten->h_addr)->s_addr;
		    }
	    }
		if(bind(m_hSocket, (struct sockaddr *)&addr, sizeof(addr))==SOCKET_ERROR)
			return false;
		if(listen(m_hSocket, 128)==SOCKET_ERROR)
			return false;
		if( g_Iocp.Associate(this)==false )
			return false;
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Listen") ) { return false; }

	m_byStatus = STATUS_LISTENED;
	return true;
}

bool CWin32Sock::Connect(LPCSTR szHost, unsigned short usPort)
{
    __try
    {
		struct linger lingerOpt;
		lingerOpt.l_onoff = 1;
		lingerOpt.l_linger = 0;

		setsockopt(m_hSocket, SOL_SOCKET, SO_LINGER, (char *)&lingerOpt, sizeof(lingerOpt));

		int opt=1;
//		if(setsockopt(m_hSocket, SOL_SOCKET, SO_DONTLINGER, (const char*)&opt, sizeof(opt))==SOCKET_ERROR)
//			return false;
		if(setsockopt(m_hSocket, SOL_SOCKET, SO_KEEPALIVE, (const char*)&opt, sizeof(opt))==SOCKET_ERROR)
			return false;
		struct sockaddr_in addr;
		memset((void *)&addr, 0, sizeof(addr));
		addr.sin_family			= AF_INET;
		addr.sin_port			= htons(usPort);
		addr.sin_addr.s_addr	= inet_addr(szHost);
	    if(addr.sin_addr.s_addr == INADDR_NONE) {
		    LPHOSTENT lpHosten = gethostbyname( szHost );
		    if(lpHosten == NULL) return false;
		    addr.sin_addr.s_addr = ((LPIN_ADDR)lpHosten->h_addr)->s_addr;
	    }
        if(connect(m_hSocket, (struct sockaddr*)&addr, sizeof(addr))==SOCKET_ERROR)
			return false;
		if(g_Iocp.Associate(this)==false)
			return false;
		if(Receive()==false)
			return false;
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Connect") ) { return false; }
	m_byStatus = STATUS_CONNECTED;
    return true;
}

bool CWin32Sock::Accept(CWin32Sock *lpClientSock)
{
    LPVOID lpDataBuff = NULL;
    __try
    {
		SOCKET hClientSocket = lpClientSock->GetSocketHandle();
		DWORD dwBuffSize = (DWORD)sizeof(IOCP_BUFFER);
		DWORD dwAddrSize = (DWORD)sizeof(sockaddr_in)+16;
		lpDataBuff = g_Iocp.m_MemoryPool.NewHeapMemory(dwBuffSize+dwAddrSize*2);
		LPIOCP_BUFFER lpOvlHead = (LPIOCP_BUFFER)lpDataBuff;
		memset(lpOvlHead, 0, dwBuffSize);
		LPWSAOVERLAPPED lpOvl = &(lpOvlHead->Overlapped);
		lpOvlHead->dwOperation = OVL_ACCEPT;
		lpOvlHead->lpAccepted = lpClientSock;
		char* lpData = ((char*)(lpOvlHead)) + dwBuffSize;
		DWORD dwBytes = 0;
		BOOL fResult = AcceptEx(m_hSocket, hClientSocket, lpData, 0, dwAddrSize, dwAddrSize, &dwBytes, lpOvl);
		DWORD dwErrorCode = ERROR_SUCCESS;
		if(fResult==FALSE) {
            dwErrorCode = WSAGetLastError();
            if(dwErrorCode != ERROR_IO_PENDING)
				g_Iocp.m_MemoryPool.DelHeapMemory(lpDataBuff);
	    }
        return (fResult||dwErrorCode==ERROR_IO_PENDING);
	}
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Accept") )
    {
		g_Iocp.m_MemoryPool.DelHeapMemory(lpDataBuff); return false;
    }
    return true;    
}

bool CWin32Sock::Send(char* lpData, DWORD dwBytes)
{
    LPVOID lpDataBuff = NULL;
    __try
    {
		if(m_hSocket==INVALID_SOCKET)
			return false;
        DWORD dwBuffSize = (DWORD)sizeof(IOCP_BUFFER);
		lpDataBuff = g_Iocp.m_MemoryPool.NewHeapMemory(dwBuffSize+dwBytes);
        LPIOCP_BUFFER lpOvlHead = (LPIOCP_BUFFER)lpDataBuff;
        memset(lpOvlHead, 0, dwBuffSize);
		lpOvlHead->dwOperation = OVL_SEND;
        lpOvlHead->OverlapBuf.len = dwBytes;
        lpOvlHead->OverlapBuf.buf = ((char*)lpOvlHead)+dwBuffSize;
		memcpy( lpOvlHead->OverlapBuf.buf, lpData, dwBytes );
		DWORD dwSended = 0;
        int nResult = WSASend(m_hSocket, &(lpOvlHead->OverlapBuf), 1, &dwSended, 0, &(lpOvlHead->Overlapped), NULL);
        DWORD dwErrorCode = ERROR_SUCCESS;
	    if(nResult == SOCKET_ERROR) {
            dwErrorCode = WSAGetLastError();
			if(dwErrorCode != ERROR_IO_PENDING) {
				g_Iocp.m_MemoryPool.DelHeapMemory(lpDataBuff);
				printf("Socket Send Error[%d]...\r\n", dwErrorCode);
				Close();
			}
	    }
        return (nResult != SOCKET_ERROR||dwErrorCode == ERROR_IO_PENDING);
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Send") )
    {
        g_Iocp.m_MemoryPool.DelHeapMemory( lpDataBuff ); return false;
    }
    return true;
}

bool CWin32Sock::Receive()
{
    LPVOID lpDataBuff = NULL;
    __try
    {
        DWORD dwBuffSize = (DWORD)sizeof(IOCP_BUFFER);
		lpDataBuff = g_Iocp.m_MemoryPool.NewHeapMemory(dwBuffSize+m_dwReadSize);
        LPIOCP_BUFFER lpOvlHead = (LPIOCP_BUFFER)lpDataBuff;
        memset(lpOvlHead, 0, dwBuffSize);
		lpOvlHead->dwOperation = OVL_RECEIVE;
        lpOvlHead->OverlapBuf.len = m_dwReadSize;
        lpOvlHead->OverlapBuf.buf = ((char*)lpOvlHead)+dwBuffSize;
        DWORD dwRecved = 0, dwFlags=0;
		int nResult = WSARecv(m_hSocket, &(lpOvlHead->OverlapBuf), 1, &dwRecved, &dwFlags, &(lpOvlHead->Overlapped), NULL);
	    DWORD dwErrorCode = ERROR_SUCCESS;
	    if(nResult == SOCKET_ERROR) {
            dwErrorCode = WSAGetLastError();
			if(dwErrorCode != ERROR_IO_PENDING) {
				g_Iocp.m_MemoryPool.DelHeapMemory(lpDataBuff);
				printf("Socket Recv Error[%d]...\r\n", dwErrorCode);
				Close();
			}
	    }
        return (nResult != SOCKET_ERROR||dwErrorCode == ERROR_IO_PENDING);
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::Receive") )
    {
        g_Iocp.m_MemoryPool.DelHeapMemory( lpDataBuff ); return false;
    }
    return true;
}

bool CWin32Sock::SetSNDBUF(DWORD dwBytes)
{
    __try
    {
         return (setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (char*)&dwBytes, sizeof(dwBytes)) != SOCKET_ERROR);
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::SetSNDBUF") ) { return false; }
    return true;
}

bool CWin32Sock::SetRCVBUF(DWORD dwBytes)
{
    __try
    {
         return (setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (char*)&dwBytes, sizeof(dwBytes)) != SOCKET_ERROR);
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::SetRCVBUF") ) { return false; }
    return true;
}

DWORD CWin32Sock::GetSNDBUF()
{
    __try
    {
		DWORD dwOptlen=0, dwSize=sizeof(dwOptlen);
		int retval = getsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (char*)&dwOptlen, (int*)&dwSize);
		if(retval!=SOCKET_ERROR)
			return dwOptlen;
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::GetSNDBUF") ) { return 0; }
    return 0;
}

DWORD CWin32Sock::GetRCVBUF()
{
    __try
    {
		DWORD dwOptlen=0, dwSize=sizeof(dwOptlen);
		int retval = getsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (char*)&dwOptlen, (int*)&dwSize);
		if(retval!=SOCKET_ERROR)
			return dwOptlen;
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::GetRCVBUF") ) { return 0; }
    return 0;
}

bool CWin32Sock::InheritContext(CWin32Sock* lpListenSock)
{
    __try
    {
		SOCKET hListenSocket = lpListenSock->GetSocketHandle();
	    if( setsockopt(m_hSocket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&hListenSocket, sizeof(hListenSocket)) == SOCKET_ERROR )
            return false;
	}
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::InheritContext") ) { return false; }
    return true;
}

bool CWin32Sock::GetPeerInfo(LPSTR szAddr, unsigned short &usPort)
{
    __try
    {
		struct sockaddr_in addr;
		int addrsize = sizeof(addr);
		memset((void *)&addr, 0, addrsize);
	    int nResult = getpeername(m_hSocket, (sockaddr*)&addr, &addrsize);
	    if(nResult == SOCKET_ERROR)
			return false;
		if(szAddr != NULL) {
			strcpy((char*)szAddr, inet_ntoa(addr.sin_addr));
			usPort = ntohs(addr.sin_port);
		}
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::GetPeerInfo") ) { return false; }
    return true;
}

bool CWin32Sock::GetSockInfo(LPSTR szAddr, unsigned short &usPort)
{
    __try
    {
		struct sockaddr_in addr;
		int addrsize = sizeof(addr);
		memset((void *)&addr, 0, addrsize);
	    int nResult = getsockname(m_hSocket, (sockaddr*)&addr, &addrsize);
	    if(nResult == SOCKET_ERROR)
			return false;
		if(szAddr != NULL) {
			strcpy((char*)szAddr, inet_ntoa(addr.sin_addr));
			usPort = ntohs(addr.sin_port);
		}
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::GetSockInfo") ) { return false; }
    return true;
}

SOCKET CWin32Sock::GetSocketHandle() 
{ 
	return m_hSocket;
}

void CWin32Sock::CloseProcess()
{
    __try
    {
		m_byStatus = STATUS_DISCONNECTED;
        if(m_hSocket != INVALID_SOCKET) {
			closesocket(m_hSocket);
			m_hSocket = INVALID_SOCKET;
        }
    }
    __except( ExceptionFilter(GetExceptionInformation(), "Win32Sock::CloseProcess") ) {}
}

DWORD CWin32Sock::CompressingData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len)
{
	return (lzf_compress(in_data, in_len, out_data, out_len));
}

DWORD CWin32Sock::DeCompressingData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len)
{
	return (lzf_decompress(in_data, in_len, out_data, out_len));
}

////////////////////////////////////////////////////////////////////////////////////////
// CPacketBuffer Implementation...
////////////////////////////////////////////////////////////////////////////////////////

CPacketBuffer::CPacketBuffer(DWORD dwBufferSize)
{
	m_dwHeadPos=0;
	m_dwTailPos=0;
	m_dwBufferSize=dwBufferSize;
	m_pBuffer = (char*)g_MemoryPool.NewHeapMemory(m_dwBufferSize);
}

CPacketBuffer::~CPacketBuffer()
{
	g_MemoryPool.DelHeapMemory((LPVOID)m_pBuffer);
}

bool CPacketBuffer::PutData(char* pData, DWORD length)
{
    if( !pData || (length>m_dwBufferSize) ) 
		return false;

    __try
    {
		while(IsOverflow(length))
			ReSize();
		if(m_dwTailPos+length >= m_dwBufferSize) {
			DWORD dwFirstBytes = m_dwBufferSize - m_dwTailPos;
			DWORD dwSecondBytes = length - dwFirstBytes;
			memcpy( m_pBuffer+m_dwTailPos, pData, dwFirstBytes );
			if(dwSecondBytes>0) {
				memcpy(m_pBuffer, pData+dwFirstBytes, dwSecondBytes);
				m_dwTailPos = dwSecondBytes;
			}
			else m_dwTailPos = 0;
		}
		else
		{
			memcpy(m_pBuffer+m_dwTailPos, pData, length);
			m_dwTailPos += length;
		}
	}
    __except( ExceptionFilter(GetExceptionInformation(), "CPacketBuffer::PutData") ) { return false;}
	return true;
}

bool CPacketBuffer::GetData(char* pData, DWORD length)
{
    if( !pData || (length>GetValidDataLength()) ) 
		return false;
    __try
    {
		DWORD dwSize = m_dwBufferSize-m_dwHeadPos;
		if(length <= dwSize) 
			memcpy(pData, m_pBuffer+m_dwHeadPos, length);
		else {
			memcpy(pData, m_pBuffer+m_dwHeadPos, dwSize);
			memcpy(pData+dwSize, m_pBuffer, length-dwSize);
		}
	}
    __except( ExceptionFilter(GetExceptionInformation(), "CPacketBuffer::GetData") ) { return false;}
	return true;
}

DWORD CPacketBuffer::GetValidDataLength()
{
    int nDataLength = m_dwTailPos-m_dwHeadPos;
    if(nDataLength<0) nDataLength = m_dwBufferSize+nDataLength;
    return (DWORD)nDataLength;
}

void CPacketBuffer::MoveHeadPos(DWORD length)
{
    if(length > GetValidDataLength()) 
		length = GetValidDataLength();
    m_dwHeadPos += length; 
	m_dwHeadPos %= m_dwBufferSize;
}

void CPacketBuffer::ReSize()
{
    __try
    {
		DWORD prevBufSize = m_dwBufferSize;
		m_dwBufferSize <<= 1;
		char* pNewData = (char*)g_MemoryPool.NewHeapMemory(m_dwBufferSize);
		memcpy(pNewData, m_pBuffer, prevBufSize);
		if(m_dwTailPos < m_dwHeadPos) {
			memcpy(pNewData+prevBufSize, m_pBuffer, m_dwTailPos );
			m_dwTailPos += prevBufSize;
		}
		g_MemoryPool.DelHeapMemory(m_pBuffer);
		m_pBuffer = pNewData;
	}
    __except( ExceptionFilter(GetExceptionInformation(), "CPacketBuffer::ReSize") ) {}
}

bool CPacketBuffer::IsOverflow(DWORD length)
{
    return ( length >= (m_dwBufferSize-GetValidDataLength()) );
}
