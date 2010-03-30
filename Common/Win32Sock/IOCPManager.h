
#ifndef _IOCPMANAGER_H
#define _IOCPMANAGER_H
#pragma once

// Overlapped operation flag
const DWORD OVL_ACCEPT		= 0x00000001;
const DWORD OVL_RECEIVE		= 0X00000002;
const DWORD OVL_SEND		= 0X00000003;
const DWORD OVL_CLOSE		= 0x00000004;

class CMemoryCatch {
public:
    CMemoryCatch( void ); ~CMemoryCatch( void );
public:
    inline LPVOID NewHeapMemory( SIZE_T dwSize );
    inline void DelHeapMemory( LPVOID lpData );
private:
    typedef struct tag_KERNEL_MEMORY_HEAD {
        tag_KERNEL_MEMORY_HEAD    *lpNext;
        BOOL                    fDelete;
        ULONG_PTR               dwIndex;
    } MEMORYDATA_HEAD, *LPMEMORYDATA_HEAD;
    HANDLE              m_hPrivateHeap;         // Private Memory Heap
    LPMEMORYDATA_HEAD*  m_lpFreeMemory;         // Free Memory Node Head
#ifdef _MEMORIZE_BUSY
    LPMEMORYDATA_HEAD*  m_lpBusyMemory;         // Busy Memory Node Head
#endif
    CRITICAL_SECTION    m_CriticalLock;         // Thread Single Visit Lock
};

class CWin32Sock;
class CSockManager;
typedef struct tag_IOCP_BUFFER {
    WSAOVERLAPPED   Overlapped;
    WSABUF          OverlapBuf;
    DWORD		    dwOperation;
    CWin32Sock*		lpAccepted;
} IOCP_BUFFER, *LPIOCP_BUFFER;

class CIOCPManager  
{
public:
	bool Associate(CWin32Sock *pSocket);
	bool StartUp(CSockManager* pSockManager, DWORD dwThreadNum=0, bool display=false);
	void CleanUp();
	CIOCPManager();
	virtual ~CIOCPManager();

	CMemoryCatch        m_MemoryPool;
	HANDLE				m_hIOCPort;
	CSockManager*		m_pSockManager;
	bool				m_bDisplay;
private:
	DWORD				m_dwThreadNum;
	HANDLE*				m_hWorkerThread;
};

#endif
