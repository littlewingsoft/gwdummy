#ifndef __PROTOCOL__H__
#define __PROTOCOL__H__

#ifdef _WIN32
	#pragma pack( push ,1 )
#else
	#pragma pack(1)
#endif

enum eRESULT_ERROR
{
	ERR_OK	= 0,
};

enum eFROM_NO
{
	FROM_USER		= 0,
	FROM_MANAGEMENT,
	FROM_DIRECT,
};

enum eMAIN_PACKET_ID
{
	MM2_LOGIN		= 0,
	MM2_LOGOUT,
};

typedef struct _PACKET_BASE
{
	BYTE			MPID;	// Main Packet ID
	BYTE			SPID;	// Sub Packet ID
	unsigned short	Len;	// Packet Size
	BYTE			FROM;	// Purpose of Packet 

	_PACKET_BASE(BYTE mpid, unsigned short len, byte from, BYTE spid=0) 
	{
		MPID = mpid;
		Len = len;
		FROM = from;
		SPID = spid;
	};
} _PKT_BASE;



#pragma pack()

#endif	//__PROTOCOL__H__