#ifndef _NETDLL_H
#define _NETDLL_H
#pragma once

#include "CommonDefines.h"

class CPacketBuffer {				// Received PacketData Queue Parsing Interface Class
public:
	CPacketBuffer();
	~CPacketBuffer();

	inline void PutData(char* pData, DWORD length);	// Input Received Data from Socket
	inline void GetData(char* pData, DWORD length);	// Output Data from Queue
	inline DWORD GetValidDataLength();				// Get Length of Valid Data from Queue 
	inline void MoveHeadPos(DWORD length);			// Data Current Head Pointer move an extent of length (for Data Delete)
	inline void ReSize();							// Resize Buffer from buffer overflow
	inline void SetInit() { m_dwHeadPos=0; m_dwTailPos=0;};
	inline bool IsOverflow(DWORD length);				// Estimation of Buffersize overflow
	inline DWORD GetHeadPos() { return m_dwHeadPos;};
	inline DWORD GetTailPos() { return m_dwTailPos;};

private:
	char* m_pBuffer;
	DWORD m_dwBufferSize;
	DWORD m_dwHeadPos;
	DWORD m_dwTailPos;
};

class CAsynSocket {
public:
	CAsynSocket(void);
	~CAsynSocket(void);
public:
	inline DWORD CompressData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len);
	inline DWORD DeCompressData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len);
	inline void  SetMaxSize(DWORD dwSendSize=1024, DWORD dwRecvSize=(1024*32));
	void  ReceivedData(char* pData, DWORD dwbytes);
	bool  PullOutCore(char* pGetBuff, DWORD &dwGetBytes);
    void  CloseSocket( void );    
	bool  ConnectSocket(char *host, int port);
	bool  IsConnected( int sec = 0);
    bool  IsDataArrived( int sec = 0);
	bool  SendData( LPVOID pData, DWORD dwLen );
	DWORD RecvData( LPVOID pData, DWORD dwLen );
	inline bool  SetSocketOpt(int level, int optname, const char *optval, int optlen); 

private:
	SOCKET m_Socket;
	fd_set m_RSet;
    fd_set m_WSet;
	DWORD  m_dwSendSize;
	DWORD  m_dwReadSize;
	CPacketBuffer	m_PacketBuffer;

private:
    bool CreateSocket( void ); 
	long ExceptionFilter(LPEXCEPTION_POINTERS pExceptionInfo, char *Info);
	long ExceptionFilter(LPEXCEPTION_POINTERS pExceptionInfo, DWORD Info);
};

#endif // _NETDLL_H
