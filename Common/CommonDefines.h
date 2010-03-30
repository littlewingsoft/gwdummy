#ifndef __COMMONDEFINES__H__
#define __COMMONDEFINES__H__
#pragma once

#ifdef _WIN32
	#pragma pack( push ,1 )
#else
	#pragma pack(1)
#endif

#include <string>
using namespace std;

// Socket Define Values.
const BYTE TYPE_LISTEN = 0x01;
const BYTE TYPE_CLIENT = 0x02;
const BYTE TYPE_SERVER = 0x03;

const DWORD MAX_ACCEPTABLE_COUNT = 500;
const DWORD MIN_ACCEPTABLE_COUNT = 200;

const BYTE PACKET_START1	= 0x55;
const BYTE PACKET_START2	= 0xBB;
const BYTE PACKET_END1		= 0x55;
const BYTE PACKET_END2		= 0xBB;

#define RELAY_PORT			8291

#define PACKET_MTU			4096	// Max Packet Size...

// 문자열 길이에는 NULL 이 제외된 크기를 말합니다.
#define MAX_SESSION_KEY_SIZE	128	// 유저 인증 유일키 값
#define MAX_USER_ID_SIZE		20	// 유저 이름 길이
#define MAX_NICK_NAME_SIZE		20	// 닉네임 길이
#define MAX_CHAT_SIZE			256	// 채팅 길이
#define MAX_SERVER_NAME			20	// 서버ID 길이
#define MAX_SYSTEM_MSG			128	// 시스템 메세지 길이
#define MAX_IP_SIZE				20	// IPv4

#define MAX_SHARED_NAME			20	// 공유메모리 공유이름
#define MAX_DB_DSN				20	// ODBC Name
#define MAX_DB_UID				20	// ODBC Login ID
#define MAX_DB_PWD				20	// ODBC Login Pwd


#define FROM_CLIENT			0x01
#define FROM_SERVER			0x02

struct __USER_INFO 
{
	WORD	wSid;
	TCHAR	szUserID[MAX_USER_ID_SIZE];
	__USER_INFO() {
		memset(this, 0x00, sizeof(__USER_INFO));
	};
};

struct __MEMBER_INFO
{
	string strMemeberID;
	string strPasswd;
	__MEMBER_INFO() {
		memset(this, 0x00, sizeof(__MEMBER_INFO));
	}
};

enum eMAIN_PACKET_ID
{
	PKT_LOGIN		= 1,
	PKT_LOGIN_RE,
	PKT_LOGOUT,
	PKT_USERINFO,
	PKT_NEWUSER,
	PKT_CHAT,
};

typedef struct _PACKET_BASE
{
	BYTE			MPID;	// Main Packet ID
	BYTE			SPID;	// Sub Packet ID
	unsigned short	Len;	// Packet Size
	BYTE			FROM;	// Purpose of Packet 
} _PKT_BASE;

struct _PKT_LOGIN : _PACKET_BASE
{
	TCHAR	szUserID[MAX_USER_ID_SIZE];
	TCHAR	szPwd[MAX_USER_ID_SIZE];
	_PKT_LOGIN() {
		memset(this, 0x00, sizeof(_PKT_LOGIN));
	};
};

struct _PKT_LOGIN_RE : _PACKET_BASE
{
	WORD	wSid;
	_PKT_LOGIN_RE() {
		memset(this, 0x00, sizeof(_PKT_LOGIN_RE));
	}
};

struct _PKT_LOGOUT : _PACKET_BASE
{
	WORD	wSid;
	_PKT_LOGOUT() {
		memset(this, 0x00, sizeof(_PKT_LOGOUT));
	};
};

struct	_PKT_USERINFO :_PACKET_BASE
{
	DWORD	dwCount;
	char	pData[2048];
	_PKT_USERINFO() {
		memset(this, 0x00, sizeof(_PKT_USERINFO));
	};
};

struct _PKT_NEWUSER : _PACKET_BASE
{
	WORD	wSid;
	TCHAR	szUserID[MAX_USER_ID_SIZE];
	_PKT_NEWUSER() {
		memset(this, 0x00, sizeof(_PKT_NEWUSER));
	}
};

struct  _PKT_CHAT : _PACKET_BASE
{
	WORD	wSid;
	DWORD	dwLen;
	TCHAR	szChat[MAX_CHAT_SIZE];
	_PKT_CHAT() {
		memset(this, 0x00, sizeof(_PKT_CHAT));
	};
};


#pragma pack()

#endif//__COMMONDEFINES__H__