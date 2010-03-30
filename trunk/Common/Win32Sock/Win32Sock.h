// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the WIN32SOCK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// WIN32SOCK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifndef _WIN32SOCK_H
#define _WIN32SOCK_H
#pragma once

#ifdef WIN32SOCK_EXPORTS
#define WIN32SOCK_API __declspec(dllexport)
#else
#define WIN32SOCK_API __declspec(dllimport)
#endif

// Close type
#define LOGOUT_NORMAL			0x01
#define LOGOUT_ABNORMAL			0x02
#define LOGOUT_KICKOUT			0x03

// Socket Status
#define STATUS_DISCONNECTED		0x00
#define STATUS_CONNECTED		0x01
#define STATUS_LISTENED			0x02

// This class is exported from the Win32Sock.dll

class WIN32SOCK_API CWin32Sock {					// Each Socket Interface Class
public:
	CWin32Sock(void);
	virtual ~CWin32Sock(void);
	bool Create();											// Create Socket Handle
    void Close();											// Close Socket Connection
    bool Listen(LPCSTR szHost, unsigned short usPort);		// Accepting Listen from Client Socket
    bool Connect(LPCSTR szHost, unsigned short usPort);		// Conncting to the Host
    bool Accept(CWin32Sock *lpListenSock);					// Waiting Pool for Client Socket Connection 
    bool Send(char* lpData, DWORD dwBytes);					// Data Sending...
    bool Receive();											// Data Receiving an extent of m_dwReadSize
	bool GetPeerInfo(LPSTR szAddr, unsigned short &usPort);// Get IP from the other side
	bool GetSockInfo(LPSTR szAddr, unsigned short &usPort);// Get IP from this side
    void* operator new(size_t dwBytes);
    void* operator new[](size_t dwBytes);
    void operator delete(void* lpData);
    void operator delete[](void* lpData);
public:
	inline DWORD CompressingData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len);
	inline DWORD DeCompressingData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len);
	inline bool SetSNDBUF(DWORD dwBytes);					// Set Kernel Socket Send Buffer Size
	inline bool SetRCVBUF(DWORD dwBytes);					// Set Kernel Socket Recv Buffer Size
	inline DWORD GetSNDBUF();								// Get Kernel Socket Send Buffer Size
	inline DWORD GetRCVBUF();								// Get Kernel Socket Recv Buffer Size
	inline bool InheritContext(CWin32Sock *lpListenSock);	// Inherit attribute from Listen Socket at Accepting time..
    inline SOCKET GetSocketHandle();						// Get Socket Handle
	inline void SetReadSize(DWORD dwsize=8192){m_dwReadSize=dwsize;};
	inline BYTE GetSocketStatus() {return m_byStatus;};		// Get Socket Status( Connected, Disconnected or and so on..)
	inline void SetSocketStatus(BYTE status) {m_byStatus=status;};
	inline BYTE GetType() {return m_byType;};
	inline void SetType(BYTE type) {m_byType=type;};
	inline void CloseProcess();								// Socket Handle Close...
private:
	SOCKET				m_hSocket;
	BYTE				m_byStatus;
	BYTE				m_byType;
protected:
	DWORD				m_dwReadSize;
};

class WIN32SOCK_API CSockManager {				// Socket Management Interface Class
public:
	CSockManager() {};
	virtual~CSockManager() {};

	virtual void OnDataReceived(CWin32Sock* pSocket, char* pData, DWORD dwbytes) {}; // Data have Received Procedure for the Socket
	virtual void OnDataSended(CWin32Sock* pSocket, DWORD dwbytes) {};				 // Data have Sended Procedure for the Socket
	virtual void OnAccepted(CWin32Sock* pListenSocket, CWin32Sock* pClientSocket) {};// Socket have Accepted Procedure
	virtual void OnClosed(CWin32Sock* pSocket, DWORD dwCloseType) {};				 // Socket have Closed Procedure	
	virtual void OnException(CWin32Sock* pSocket, DWORD dwErrorCode) {};			 // Socket Operation have Excepted Procedure
};

class WIN32SOCK_API CPacketBuffer {				// Received PacketData Queue Parsing Interface Class
public:
	CPacketBuffer(DWORD dwBufferSize=16384);
	~CPacketBuffer();

	inline bool PutData(char* pData, DWORD length);	// Input to BufferQueue Received Data from Socket
	inline bool GetData(char* pData, DWORD length);	// Output Data from BufferQueue. length is requesting data size
	inline DWORD GetValidDataLength();				// Get Length of Valid Data from BufferQueue 
	inline void MoveHeadPos(DWORD length);			// Data Current Head Pointer move an extent of length (for Data Delete)
	inline void ReSize();							// Resize BufferQueue for BufferQueue overflow
	inline void SetInit() { m_dwHeadPos=0; m_dwTailPos=0;};
	inline bool IsOverflow(DWORD length);			// Estimation of Buffersize overflow
	inline DWORD GetHeadPos() { return m_dwHeadPos;};
	inline DWORD GetTailPos() { return m_dwTailPos;};

private:
	char* m_pBuffer;
	DWORD m_dwBufferSize;
	DWORD m_dwHeadPos;
	DWORD m_dwTailPos;
};

extern "C" WIN32SOCK_API bool IOCPStartup(CSockManager* pSockManager, DWORD dwThreadsCount, bool display=true);
extern "C" WIN32SOCK_API void IOCPCleanup();
extern "C" WIN32SOCK_API LONG ExceptionFilter( LPEXCEPTION_POINTERS pExceptionInfo, LPCSTR szPosition );

#endif // _WIN32SOCK_H