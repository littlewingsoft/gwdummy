// NetDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "NetDll.h"
#include "lzfP.h"
#include "lzf.h"

CAsynSocket::CAsynSocket(void):
m_Socket(INVALID_SOCKET)
{
	WSADATA	wsaData;
	WSAStartup( MAKEWORD ( 2, 2 ), &wsaData );
	m_dwSendSize = 1024;
	m_dwReadSize = (1024*32);
}

CAsynSocket::~CAsynSocket(void)
{
	CloseSocket();
	WSACleanup();
}

bool CAsynSocket::CreateSocket( void )
{
	__try
	{
		m_Socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

		if (INVALID_SOCKET == m_Socket)
			return false;
		else
		{
			unsigned long ul = 1;

			if (SOCKET_ERROR == ioctlsocket(m_Socket, FIONBIO, &ul))
				return false;
		}
	}
	__except( ExceptionFilter(GetExceptionInformation(), "CreateSocket") )
	{
		return false;
	}

	return true;
}

void CAsynSocket::CloseSocket(void)
{
	__try
	{
	if (INVALID_SOCKET != m_Socket)
	{
		closesocket( m_Socket );
		m_Socket = INVALID_SOCKET;
	}
	}
	__except( ExceptionFilter(GetExceptionInformation(), "CloseSocket") )
	{
	}
}

bool CAsynSocket::ConnectSocket(char *host, int port)
{
	if (NULL == host || 0 > port )
		return false;

	CloseSocket();

	if(!CreateSocket()) 
		return false;

//	if (!SetSocketOpt(SOL_SOCKET, SO_SNDBUF, ( LPSTR )&m_dwSendSize, sizeof( m_dwSendSize ))) return false;

	__try
	{
		sockaddr_in In;

		ZeroMemory(&In, sizeof( In ));

		In.sin_family = AF_INET;

		In.sin_port = htons( port );

		In.sin_addr.s_addr = inet_addr( host );

		if ( In.sin_addr.s_addr == INADDR_NONE )
		{
			LPHOSTENT lpHosten = gethostbyname( host );
			if ( lpHosten == NULL ) return ( false );
			In.sin_addr.s_addr = ( ( LPIN_ADDR )lpHosten->h_addr )->s_addr;
		}

		int nResult = WSAConnect(m_Socket, (SOCKADDR*)&In, sizeof(In), NULL, NULL, NULL, NULL);

		if ( nResult == SOCKET_ERROR )
		{
			int err = WSAGetLastError();
			if ( err == WSAEWOULDBLOCK )
				return true;
			else
				return false;
		}

		int opt=1;
		if(SetSocketOpt(SOL_SOCKET, SO_DONTLINGER, (const char*)&opt, sizeof(opt))==false)
			return false;

	}
	__except( ExceptionFilter(GetExceptionInformation(), "ConnectSocket") )
	{
		return false;
	}

	return true;
}

/****************************************************************************/
//Establish the attribute of Socket  
//
//example:
//    setsockopt( SOL_SOCKET, SO_REUSEADDR, (char*)&fEnable, sizeof(fEnable);
/****************************************************************************/

bool CAsynSocket::SetSocketOpt(int level, int optname, const char *optval, int optlen)
{
	__try
	{
	return (SOCKET_ERROR == setsockopt( m_Socket, 
		                                level, 
										optname,
										optval,
										optlen)) ? false : true;
	}
    __except( ExceptionFilter(GetExceptionInformation(), "SetSocketOpt") )
	{
		return false;
	}
}

bool CAsynSocket::SendData(LPVOID pData, DWORD dwLen)
{
//	char *pData = &Data;

	if (NULL == pData || 0 == dwLen)
		return false;
//////////////////////////////////////////////////////////////////////////////////////////
// Packing Packet..
	char pTemp[2048]; memset(pTemp, 0, sizeof(pTemp));
	DWORD index=0;

	pTemp[index++] = (BYTE)_PACKET_START1;
	pTemp[index++] = (BYTE)_PACKET_START2;
	memcpy( pTemp+index, &dwLen, 2 );	// unsigned short
	index += 2;
	memcpy( pTemp+index, pData, dwLen );
	index += dwLen;
	pTemp[index++] = (BYTE)_PACKET_END1;
	pTemp[index++] = (BYTE)_PACKET_END2;
//////////////////////////////////////////////////////////////////////////////////////////
	char* pHead = (char*)pTemp;
	WSABUF pBuf;
    DWORD    n     = 0;
	DWORD  dwBytes = 0;

	__try
	{
		while (index > 0)
		{
			n = (index > m_dwSendSize) ? m_dwSendSize : index;
			pBuf.len = n;
			pBuf.buf = pHead;
			if ( SOCKET_ERROR == WSASend(m_Socket, &pBuf, 1, &dwBytes, 0, NULL, NULL))
				return false;

			index -= static_cast<int>(dwBytes);
			pHead += n;
		}
	}
	__except( ExceptionFilter(GetExceptionInformation(), "SendData") )
	{
		return false;
	}

    pData = NULL;
	return ( index == 0 );
}

DWORD CAsynSocket::RecvData(LPVOID pData, DWORD dwLen)
{
//	char *pData = &Data;

	if (NULL == pData || 0 == dwLen)
		return SOCKET_ERROR;

	WSABUF pBuf;
	DWORD  dwBytes = 0;

    DWORD tLen = (dwLen > m_dwReadSize) ? m_dwReadSize : dwLen;

	pBuf.len = tLen;
	pBuf.buf = (char*)pData;
	DWORD dwFlags = 0;

	__try
	{
		if (SOCKET_ERROR == WSARecv(m_Socket, &pBuf, 1, &dwBytes, &dwFlags, NULL, NULL))
			return SOCKET_ERROR;
		else
			return dwBytes;
	}
	__except(ExceptionFilter(GetExceptionInformation(), "RecvData"))
	{
		return SOCKET_ERROR;
	}
}

bool CAsynSocket::IsConnected( int sec)
{
	__try
	{
		FD_ZERO( &m_WSet );
		FD_SET( m_Socket, &m_WSet );
		struct timeval t;
		t.tv_sec = sec;
		t.tv_usec = 0;
		select( 0, NULL, &m_WSet, NULL, &t );
		if ( FD_ISSET(m_Socket, &m_WSet) )
			return true;
		else 
			return false;
	}
	__except( ExceptionFilter(GetExceptionInformation(), "IsConnected") )
	{
		return false;
	}
}

bool CAsynSocket::IsDataArrived( int sec)
{
	__try
	{
		FD_ZERO( &m_RSet );
		FD_SET( m_Socket, &m_RSet );
		struct timeval t;
		t.tv_sec = sec;
		t.tv_usec = 0;
		select( 0, &m_RSet, NULL, NULL, &t );
		if ( FD_ISSET( m_Socket, &m_RSet ) )
			return true;
		else
			return false;
	}
	__except(ExceptionFilter(GetExceptionInformation(), "IsDataArrived"))
	{
		return false;
	}
}

void CAsynSocket::SetMaxSize(DWORD dwSendSize, DWORD dwReadSize)
{
	m_dwSendSize = dwSendSize;
	m_dwReadSize = dwReadSize;
}

bool CAsynSocket::PullOutCore(char* pGetBuff, DWORD &dwGetBytes)
{
	DWORD			DataLen=0;
	bool			foundCore=false;
	unsigned short	slen=0;

	DataLen = m_PacketBuffer.GetValidDataLength();
	if(DataLen <= 4) return false;							// START1, START2, END1, END2
	BYTE pTempBuff[(1024*32)];	memset(pTempBuff, 0x00, sizeof(pTempBuff));
	if(DataLen>sizeof(pTempBuff))
		DataLen = sizeof(pTempBuff);
	m_PacketBuffer.GetData((char*)pTempBuff, DataLen);

	DWORD	sPos=0, ePos=0;									// start position and end position...
	for(register DWORD i=0; i<DataLen; i++) {
		if(i+2 >= DataLen) break;
		if(pTempBuff[i] == _PACKET_START1 && pTempBuff[i+1] == _PACKET_START2) {
			if(i!=0)	m_PacketBuffer.MoveHeadPos(i);		// set current position for valid position
			sPos = i+2;										// after PACKET_START1+PACKET_START2
			memcpy(&slen, &pTempBuff[sPos], 2);				// length data
			if(slen>m_dwReadSize) {
				m_PacketBuffer.MoveHeadPos(2);				// wrong size
				return false;
			}
			else if(slen>DataLen)							// this packet don`t have received yet...
				return false;
			ePos = sPos+slen +2;							// end parity checking position ( 2 : length size )
			if( (ePos+2)>DataLen )							// 2 : PACKET_END1 + PACKET_END2
				return false;								// this packet don`t have received yet...
			if(pTempBuff[ePos] == _PACKET_END1 && pTempBuff[ePos+1] == _PACKET_END2) {
				dwGetBytes = slen;							// real packet size
				memcpy(pGetBuff, (const void*)(pTempBuff+sPos+2), dwGetBytes);
				foundCore = true;
				m_PacketBuffer.MoveHeadPos(6+dwGetBytes);	// 6bytes : header 2bytes + end 2bytes + length 2bytes
				break;
			}
			else {											// Packet Wrapping Error!!
				m_PacketBuffer.MoveHeadPos(2);				// refind from next position...
				break;
			}
		}
	}
	return foundCore;
}

void CAsynSocket::ReceivedData(char* pData, DWORD dwbytes)
{
	m_PacketBuffer.PutData(pData, dwbytes);
}

DWORD CAsynSocket::CompressData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len)
{
	return (lzf_compress(in_data, in_len, out_data, out_len));
}

DWORD CAsynSocket::DeCompressData(const char* in_data, DWORD in_len, char* out_data, DWORD out_len)
{
	return (lzf_decompress(in_data, in_len, out_data, out_len));
}

long CAsynSocket::ExceptionFilter(LPEXCEPTION_POINTERS pExceptionInfo, char *Info)
{
	PEXCEPTION_RECORD pRecord = pExceptionInfo->ExceptionRecord;


	char strExceptionDescription[512];
	sprintf( strExceptionDescription, "The system takes place the exception in the 0x%p while run function of %s,error code: 0x%08X",
									   (pRecord->ExceptionAddress), 
									   Info,
		                               pRecord->ExceptionCode);

	MessageBox(NULL, strExceptionDescription, 0, MB_OK);

	return EXCEPTION_EXECUTE_HANDLER;
}

long CAsynSocket::ExceptionFilter(LPEXCEPTION_POINTERS pExceptionInfo, DWORD Info)
{
	PEXCEPTION_RECORD pRecord = pExceptionInfo->ExceptionRecord;


	char strExceptionDescription[512];
	sprintf( strExceptionDescription, "The system takes place the exception in the 0x%p while run function of 0x%08X,error code: 0x%08X",
									   (pRecord->ExceptionAddress), 
		                               Info,
		                               pRecord->ExceptionCode);

	MessageBox(NULL, strExceptionDescription, 0, MB_OK);

	return EXCEPTION_EXECUTE_HANDLER;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CPacketBuffer Implementation...
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CPacketBuffer::CPacketBuffer()
{
	m_dwHeadPos=0;
	m_dwTailPos=0;
	m_dwBufferSize=(1024*32);
	m_pBuffer = new char[m_dwBufferSize];
}

CPacketBuffer::~CPacketBuffer()
{
	if(m_pBuffer) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

void CPacketBuffer::PutData(char* pData, DWORD length)
{
    if( !pData || (length>m_dwBufferSize) ) return;
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

void CPacketBuffer::GetData(char* pData, DWORD length)
{
    if( !pData || (length>GetValidDataLength()) ) return;
    DWORD dwSize = m_dwBufferSize-m_dwHeadPos;
	if(length <= dwSize) 
		memcpy(pData, m_pBuffer+m_dwHeadPos, length);
	else {
		memcpy(pData, m_pBuffer+m_dwHeadPos, dwSize);
		memcpy(pData+dwSize, m_pBuffer, length-dwSize);
	}
}

DWORD CPacketBuffer::GetValidDataLength()
{
    int nDataLength = m_dwTailPos-m_dwHeadPos;
    if(nDataLength<0) nDataLength = m_dwBufferSize+nDataLength;
    return (DWORD)nDataLength;
}

void CPacketBuffer::MoveHeadPos(DWORD length)
{
    if(length > GetValidDataLength()) length = GetValidDataLength();
    m_dwHeadPos += length; 
	m_dwHeadPos %= m_dwBufferSize;
}

void CPacketBuffer::ReSize()
{
    DWORD prevBufSize = m_dwBufferSize;
	m_dwBufferSize <<= 1;
	char* pNewData = new char[m_dwBufferSize];
	memcpy(pNewData, m_pBuffer, prevBufSize);
	if(m_dwTailPos < m_dwHeadPos) {
		memcpy(pNewData+prevBufSize, m_pBuffer, m_dwTailPos );
		m_dwTailPos += prevBufSize;
	}
	delete[] m_pBuffer;
	m_pBuffer = pNewData;
}

bool CPacketBuffer::IsOverflow(DWORD length)
{
    return ( length > (m_dwBufferSize-GetValidDataLength()) );
}
