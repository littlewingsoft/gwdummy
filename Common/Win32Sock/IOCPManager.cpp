// IOCPortManager.cpp: implementation of the CIOCPManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Win32Sock.h"
#include "IOCPManager.h"
#include <process.h> 
///////////////////////////////////////////////////////
#include <time.h>
char g_szbuf[32];
char* GetTimeString(char* szbuf)
{
	struct tm when;
	__time64_t now;
	_time64(&now);
	when = *_localtime64(&now);
	sprintf(szbuf, "%d:%d:%d", when.tm_hour, when.tm_min, when.tm_sec);
	return szbuf;
}

void WriteLogFile(const char* szlog)
{
	char szLogFileName[256];
	memset( szLogFileName, 0, 256);
	FILE* pFile = NULL;
	struct tm when;
	__time64_t now;

	_time64( &now );
	when = *_localtime64( &now );
	char szFinalLog[512];
	memset(szFinalLog, 0, 512);
	sprintf(szFinalLog, "%d-%d-%d %d:%d:%d %s\r\n", \
		when.tm_year+1900, when.tm_mon+1, when.tm_mday, when.tm_hour, when.tm_min, when.tm_sec, szlog);
	strcpy(szLogFileName, "win32sock.log");
	pFile = fopen(szLogFileName, "a");
	if( !pFile )
		return;
	fseek(pFile, 0L, SEEK_END);
	fwrite(szFinalLog, strlen(szFinalLog), 1, pFile);
	fclose(pFile);
}

///////////////////////////////////////////////////////
CMemoryCatch::CMemoryCatch( void )
{
    InitializeCriticalSection( &m_CriticalLock );
    m_hPrivateHeap = HeapCreate( HEAP_NO_SERIALIZE, 0, 0 );
    DWORD dwBytes = sizeof( LPMEMORYDATA_HEAD[1024 * 32] );
    m_lpFreeMemory = ( LPMEMORYDATA_HEAD* )NewHeapMemory( dwBytes );
    ZeroMemory( m_lpFreeMemory, dwBytes );
#ifdef _MEMORIZE_BUSY
    m_lpBusyMemory = ( LPMEMORYDATA_HEAD* )NewHeapMemory( dwBytes );
    ZeroMemory( m_lpBusyMemory, dwBytes );
#endif
}

CMemoryCatch::~CMemoryCatch( void )
{
    if ( m_hPrivateHeap != NULL ) HeapDestroy( m_hPrivateHeap );
    DeleteCriticalSection( &m_CriticalLock );
}

LPVOID CMemoryCatch::NewHeapMemory( SIZE_T dwSize )
{
    SIZE_T dwHeadSize = sizeof( MEMORYDATA_HEAD );
    //SIZE_T dwSpare = ( dwSize + dwHeadSize ) % 1024;
    //SIZE_T dwBytes = ( dwSpare ) ? ( dwSize + dwHeadSize + 1024 - dwSpare ) : \
    //                               ( dwSize + dwHeadSize );
    //SIZE_T dwIndex = ( ( dwBytes >> 10 ) - 1 );
	SIZE_T dwIndex = ( dwSize + dwHeadSize - 1 ) >> 10;
	SIZE_T dwBytes = (dwIndex+1) << 10;
    LPMEMORYDATA_HEAD lpNodeMemory = NULL; LPVOID lpDataMemory = NULL;
    EnterCriticalSection( &m_CriticalLock );
    __try
    {
        if ( m_lpFreeMemory != NULL && m_lpFreeMemory[dwIndex] != NULL )
        {
            lpNodeMemory = m_lpFreeMemory[dwIndex];
            m_lpFreeMemory[dwIndex] = m_lpFreeMemory[dwIndex]->lpNext;
        }
        else if ( m_hPrivateHeap != NULL )
        {
            DWORD dwFlags = HEAP_NO_SERIALIZE;
            lpNodeMemory = ( LPMEMORYDATA_HEAD )HeapAlloc( m_hPrivateHeap, dwFlags, dwBytes );
            if ( lpNodeMemory != NULL ) lpNodeMemory->dwIndex = dwIndex;
        }
        if ( lpNodeMemory != NULL )
        {
            lpNodeMemory->fDelete = FALSE;
#ifdef _MEMORIZE_BUSY
            if ( m_lpBusyMemory != NULL )
            {
                lpNodeMemory->lpNext = m_lpBusyMemory[dwIndex];
                m_lpBusyMemory[dwIndex] = lpNodeMemory;
            }
#endif
            lpDataMemory = ( LPVOID )( ( ( LPSTR )lpNodeMemory ) + dwHeadSize );
        }
    }
    __except( ExceptionFilter( GetExceptionInformation(), "MemoryCatch::NewHeap") ) { }
    LeaveCriticalSection( &m_CriticalLock );
    return ( lpDataMemory );
}

void CMemoryCatch::DelHeapMemory( LPVOID lpData )
{
    EnterCriticalSection( &m_CriticalLock );
    __try
    {
        SIZE_T dwHeadSize = sizeof( MEMORYDATA_HEAD );
        LPMEMORYDATA_HEAD lpNodeMemory = ( LPMEMORYDATA_HEAD )( ( ( LPSTR )lpData ) - dwHeadSize );
        SIZE_T dwIndex = lpNodeMemory->dwIndex;
#ifdef _MEMORIZE_BUSY
        LPMEMORYDATA_HEAD lpTempMemory = NULL, lpLastMemory = NULL;
        if ( m_lpBusyMemory != NULL && m_lpBusyMemory[dwIndex] != NULL )
        {
            lpTempMemory = m_lpBusyMemory[dwIndex];
            while ( lpTempMemory != NULL )
            {
                if ( lpTempMemory != lpNodeMemory )
                {
                    lpLastMemory = lpTempMemory;
                    lpTempMemory = lpTempMemory->lpNext;
                    continue;
                }
                if ( lpLastMemory == NULL )
                {
                    m_lpBusyMemory[dwIndex] = lpNodeMemory->lpNext;
                }
                else
                {
                    lpLastMemory->lpNext = lpNodeMemory->lpNext;
                }
#endif
                if ( m_lpFreeMemory != NULL && lpNodeMemory->fDelete == FALSE )
                {
                    lpNodeMemory->fDelete = TRUE;
                    lpNodeMemory->lpNext = m_lpFreeMemory[dwIndex];
                    m_lpFreeMemory[dwIndex] = lpNodeMemory;
                }
#ifdef _MEMORIZE_BUSY
                break;
            }
        }
#endif
    }
	__except( ExceptionFilter( GetExceptionInformation(), "MemoryCatch::DelHeap" ) ) { }
    LeaveCriticalSection( &m_CriticalLock );
}

unsigned __stdcall WorkerThreadProc(void *lp)
{
	CIOCPManager* pIocport = (CIOCPManager*) lp;

	BOOL				b=FALSE;
	LPIOCP_BUFFER		pOvl=NULL;
	DWORD				dwbytes=0;
	DWORD				dwFlag=0;
	CWin32Sock*			pSocket=NULL;

	while(true) {
		__try {
			if(pOvl) 
				pIocport->m_MemoryPool.DelHeapMemory((LPVOID)pOvl);
			pOvl=NULL; pSocket=NULL; dwbytes=0;
			b = GetQueuedCompletionStatus(pIocport->m_hIOCPort, &dwbytes, (PULONG_PTR)&pSocket, (LPOVERLAPPED*)&pOvl, INFINITE);
			if(b && !pOvl && !pSocket) {
				printf("[0x%x]Thread End...\r\n", GetCurrentThreadId());
				break;
			}
			if(!b && !pOvl ) {
				DWORD dwError = GetLastError();
				printf("abnormal terminationA...[%d]\r\n", dwError);
				if(pSocket) {
					pSocket->CloseProcess();
					pIocport->m_pSockManager->OnClosed(pSocket, LOGOUT_ABNORMAL);
				}
				continue;
			}
			if(!b && pOvl && pSocket) {
				DWORD dwError = GetLastError();
				if(dwError==ERROR_OPERATION_ABORTED || dwError==ERROR_NETNAME_DELETED) {
					if(pSocket->GetSocketStatus() != STATUS_DISCONNECTED) {
						printf("the other side close...\r\n");
						pSocket->CloseProcess();
						pIocport->m_pSockManager->OnClosed(pSocket, LOGOUT_NORMAL);
					}
					continue;
				}
				printf("abnormal terminationB...[%d]\r\n", dwError);
				pSocket->CloseProcess();
				pIocport->m_pSockManager->OnClosed(pSocket, LOGOUT_ABNORMAL);
				continue;
			}
			if(pOvl && pSocket) {
				switch(pOvl->dwOperation) {
					case OVL_ACCEPT:
						printf("IOCP Accepted...\r\n");
						if(pOvl->lpAccepted->InheritContext(pSocket)==false || pIocport->Associate(pOvl->lpAccepted)==false) {
							DWORD dwSocketErr = WSAGetLastError();
							pIocport->m_pSockManager->OnException(pOvl->lpAccepted, dwSocketErr);
							continue;
						}
						if(pOvl->lpAccepted->Receive()==false) {
							DWORD dwSocketErr = WSAGetLastError();
							pIocport->m_pSockManager->OnException(pOvl->lpAccepted, dwSocketErr);
							continue;
						}
						pOvl->lpAccepted->SetSocketStatus(STATUS_CONNECTED);
						pIocport->m_pSockManager->OnAccepted(pSocket, pOvl->lpAccepted);
						break;
					case OVL_RECEIVE:
						if(dwbytes==0) {
							printf("closed by 0 byte return...\r\n");
							pSocket->CloseProcess();
							pIocport->m_pSockManager->OnClosed(pSocket, LOGOUT_NORMAL);
							continue;
						}
						if(pIocport->m_bDisplay) {
							memset(g_szbuf, 0, sizeof(g_szbuf));
							printf("[%s]IOCP %d bytes Received...\r\n", GetTimeString(g_szbuf), dwbytes);
						}
						pIocport->m_pSockManager->OnDataReceived(pSocket, pOvl->OverlapBuf.buf, dwbytes);
						if(pSocket->Receive()==false) {
							DWORD dwSocketErr = WSAGetLastError();
							if(dwSocketErr!=WSAENOTSOCK)
								pIocport->m_pSockManager->OnException(pSocket, dwSocketErr);
							continue;
						}
						break;
					case OVL_SEND:
						if(pIocport->m_bDisplay) {
							memset(g_szbuf, 0, sizeof(g_szbuf));
							printf("[%s]IOCP %d bytes Sended...\r\n", GetTimeString(g_szbuf), dwbytes);
						}
						pIocport->m_pSockManager->OnDataSended(pSocket, dwbytes);
						break;
					case OVL_CLOSE:
						printf("IOCP Closed by Close() Received...\r\n");
						pSocket->CloseProcess();
						pIocport->m_pSockManager->OnClosed(pSocket, LOGOUT_KICKOUT);
						break;
					default:
						break;
				}
			}
		}
        __except( ExceptionFilter(GetExceptionInformation(), "IOCPThread") )
        {
			if(pOvl && pOvl->dwOperation==OVL_RECEIVE) {
				if(pSocket) {
					if(pSocket->Receive()==false) {
						DWORD dwSocketErr = WSAGetLastError();
//						if(dwSocketErr!=WSAENOTSOCK)
							pIocport->m_pSockManager->OnException(pSocket, dwSocketErr);
						continue;
					}
				}
			}
            DWORD dwSocketErrorCode = WSAGetLastError();
			char szlog[256]; memset(szlog, 0, sizeof(szlog));
			if(pOvl)
				sprintf(szlog, "IOCPThread Exception : [%d] Info(%d,0X%p,%d,0X%p,%d)...", dwSocketErrorCode, b, pSocket, pOvl->dwOperation, pOvl->OverlapBuf.buf, dwbytes);
			else
				sprintf(szlog, "IOCPThread Exception : [%d] Info(%d,0X%p,%d)...", dwSocketErrorCode, b, pSocket, dwbytes);
			WriteLogFile(szlog);
            __try
            {
				if(pOvl != NULL && pOvl->dwOperation == OVL_ACCEPT) {
					if(pOvl->lpAccepted != NULL) 
						pIocport->m_pSockManager->OnException(pOvl->lpAccepted, dwSocketErrorCode);
                }
                else {
                    if(pSocket != NULL)
						pIocport->m_pSockManager->OnException(pSocket, dwSocketErrorCode);
                }
            }
            __except( EXCEPTION_EXECUTE_HANDLER ) { }
        }
	}

	return 1;
}

CIOCPManager::CIOCPManager()
{
	m_hIOCPort=NULL;
	m_hWorkerThread=NULL;
	m_pSockManager=NULL;
	m_dwThreadNum = 0;
}

CIOCPManager::~CIOCPManager()
{
	CleanUp();
}

bool CIOCPManager::StartUp(CSockManager* pSockManager, DWORD dwThreadNum, bool display)
{
	if(!pSockManager)
		return false;
    CleanUp();
	m_pSockManager = pSockManager;
	m_bDisplay = display;
	bool bStart=false;
    __try
	{
        WSADATA WsaData;
        if( WSAStartup(WINSOCK_VERSION, &WsaData) != 0 ) __leave;
        
		m_hIOCPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
        if(m_hIOCPort==NULL) __leave;
		if(dwThreadNum==0) {
			SYSTEM_INFO SystemInfo; 
			GetSystemInfo(&SystemInfo);
			dwThreadNum = 2*SystemInfo.dwNumberOfProcessors;
		}
		m_hWorkerThread = new HANDLE[dwThreadNum];
		if(m_hWorkerThread==NULL) __leave;
		UINT WorkerId=0;
		for( register DWORD i=0; i<dwThreadNum; i++ ) {
			m_hWorkerThread[i] = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, WorkerThreadProc, (LPVOID)this, 0, &WorkerId));
//			m_hWorkerThread[i] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)WorkerThreadProc, this, 0, NULL );
			if(m_hWorkerThread[i] == NULL) break;
			m_dwThreadNum++;
			SetThreadPriority(m_hWorkerThread[i], THREAD_PRIORITY_ABOVE_NORMAL);
		}
		bStart = (m_dwThreadNum == dwThreadNum);
	}
	__finally
	{
		if(bStart == false) CleanUp();
	}
    return bStart;
}

void CIOCPManager::CleanUp()
{
    if(m_hWorkerThread != NULL) {
		if(m_dwThreadNum > 0) {
			for( register DWORD i=0; i<m_dwThreadNum; i++) {
				if(m_hWorkerThread[i] == NULL) 
					continue;
				PostQueuedCompletionStatus(m_hIOCPort, 0, 0, NULL);
			}
//			int retval = WaitForMultipleObjects( m_dwThreadNum, m_hWorkerThread, TRUE, INFINITE );
			for( register DWORD j=0; j<m_dwThreadNum; j++) {
				if(m_hWorkerThread[j] == NULL)
					continue;
				CloseHandle(m_hWorkerThread[j]);
			}
		}
		delete[] m_hWorkerThread;
		m_hWorkerThread = NULL;
		m_dwThreadNum = 0;
	}
    if(m_hIOCPort != NULL) {
        CloseHandle(m_hIOCPort); 
		m_hIOCPort = NULL;
    }
    WSACleanup();
}

bool CIOCPManager::Associate(CWin32Sock *pSocket)
{
	HANDLE hTemp;
	hTemp = CreateIoCompletionPort(reinterpret_cast<HANDLE>(pSocket->GetSocketHandle()), m_hIOCPort, (ULONG_PTR)pSocket, 0);
	if(hTemp!=m_hIOCPort) {
		int err = GetLastError();
		printf("Socket Associate Fail...[%d]\r\n", err);
	}		
	return (hTemp == m_hIOCPort);
}
