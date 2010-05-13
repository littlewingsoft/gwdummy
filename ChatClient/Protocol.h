#pragma once

////////////////////////////////////////////////////
// Designed for T.C.G by Timothy.
////////////////////////////////////////////////////
//v.1.0

#include "CommonDefines.h"

#ifdef _WIN32
	#pragma pack( push ,1 )
#else
	#pragma pack(1)
#endif

#ifdef _DEBUG
//#pragma pack( show )
#endif

#define _PROTOCOL_VERSION 1003

// 방 변경사항 플래그 값
enum eROOM_MODIFY_FLAG
{
	_ROOM_MOD_NAME			= 0x00000001,	// 방 이름변경
	_ROOM_MOD_PASSWD		= 0x00000002,	// 방 비번변경
	_ROOM_MOD_LEVEL			= 0x00000004,   // 방 레벨제한변경
	_ROOM_MOD_RULE			= 0x00000008,	// 방 규칙변경(덱전, 체력전)
	_ROOM_MOD_MAXCNT		= 0x00000010,	// 방 최대인원
	_ROOM_MOD_CURRENTCNT	= 0x00000020,	// 방 현재인원
	_ROOM_MOD_MAP			= 0x00000040,	// 맵 변경
	_ROOM_MOD_TOTAL			= 0x000000ff,	// 모든 항목 변경
};

// packet result error codes.
enum ePACKET_RESULT
{
	_ERR_NONE = 0,		// Error is not occured.
	_ERR_NOTREGISTERED,	// Not registered User.
	_ERR_PWD,			// Wrong Password.
	_ERR_NETWORK,		// User socket error occured.
	_ERR_PROTOCOL,		// denied for invalid protocol version
	_ERR_OCCUR,			// 에러발생
	_ERR_DISABLE,		// 불가능
	_ERR_LOGINED,		// 로그인시 이미 로그인 되었을때
};

enum eRoomPassword
{
	_ROOM_PASSWORD_NO = 0,	/// 공개방
	_ROOM_PASSWORD_OK,		/// 비번방
};

enum eTRADE_CARD_MOVE
{
	_TRADE_CARD_MOVE_NONE = 0,	
	_TRADE_CARD_MOVE_INVEN,		/// 획득한 카드 가방으로
	_TRADE_CARD_MOVE_MAILBOX,	/// 획득한 카드 메일함으로
};

enum eCHATTYPE				/// 커뮤니티 종류값
{
	_CHAT_PERSON = 0,		/// 개인 메시지(귓속말)
	_CHAT_ROOM,				/// 방 메시지
	_CHAT_CHANNEL,			/// 채널 메시지
	_CHAT_DUNGEON,			/// 던전 메시지
	_CHAT_GUILD,			/// 길드 메시지
	_CHAT_SYSTEM,			/// 시스템 메시지
	_CHAT_GAME_MANAGER,		/// 운영자 메시지
	_CHAT_GAME_NOTIFY,		/// 전체공지 메시지
	_CHAT_MAX
};

enum eTRADING				/// 거래 상태값
{
	_TRADING_NONE = 0,		/// 거래중 : 없음
	_TRADING_PERSON,		/// 거래중 : 개인
	_TRADING_PERSON_READY,	/// 거래중 : 개인(준비)
	_TRADING_PERSON_START,	/// 거래중 : 개인(시작)
	_TRADING_PERSON_WAIT,   /// 거래중 : 개인거래 신청받음
	_TRADING_BOOSTER,		/// 거래중 : 부스터
	_TRADING_SHOP,			/// 거래중 : 상점
	_TRADING_MIX,			/// 거래중 : 조합
	_TRADING_PRODUCT,		/// 거래중 : 제작
	_TRADING_DISSOLVE,		/// 거래중 : 분해
	_TRADING_AUCTION,		/// 거래중 : 경매
	_TRADING_MAX
};
// common packet data
typedef struct PACKET_BASE
{
	unsigned short	MPID;	// Main Packet ID
	unsigned short	SPID;	// Sub Packet ID
	unsigned short	Len;	// Packet Size
	unsigned short	FROM;	// Purpose of Packet 
} _PKT_BASE;

//Tony; RE-ORDERING so login server is first, lobby is second.

// login server packet id enum list.
enum eLS_PACKET_ID
{
	_LS_PKT_LOGIN = 10000,
	_LS_PKT_LOGIN_RE,
	_LS_PKT_SERVER_LIST,
	_LS_PKT_SERVER_LIST_RE,
	_LS_PKT_CHANNEL_LIST,
	_LS_PKT_CHANNEL_LIST_RE,
};

// lobby server main packet id enum list.
enum eLB_MAIN_PACKET_ID
{
	_GS_PKT_LOGIN = 1,					/// 게임서버 로그인
	_GS_PKT_LOGIN_RE,					/// 게임서버 로그인 응답
	_GS_PKT_LOGOUT,						/// 게임서버 로그아웃
	_GS_PKT_SERVER_LIST,				/// 서버리스트 요청
	_GS_PKT_SERVER_LIST_RE,
	_GS_PKT_CHANNEL_LIST,				/// 해당 서버의 채널 리스트 요청
	_GS_PKT_CHANNEL_LIST_RE,

	_GS_PKT_CHAR_COUNT,					/// 캐릭터관리: 유저의 캐릭터 중복확인
	_GS_PKT_CHAR_COUNT_RE,
	_GS_PKT_MYCHAR_GET,					/// 캐릭터관리: 유저의 캐릭터 요청
	_GS_PKT_MYCHAR_GET_RE,
	_GS_PKT_MYCHAR_ADD,					/// 캐릭터관리: 유저의 캐릭터 생성
	_GS_PKT_MYCHAR_ADD_RE,
	_GS_PKT_MYCHAR_DEL,					/// 캐릭터관리: 유저의 캐릭터 삭제
	_GS_PKT_MYCHAR_DEL_RE,
	_GS_PKT_MYCHAR_ENTREE,				/// 마을로비: 입장
	_GS_PKT_MYCHAR_ENTREE_RE,			/// 마을로비: 입장응답
	_GS_PKT_MYCHAR_ENTREE_LOAD_END,		/// 마을로비: 데이타 로딩완료
	_GS_PKT_USERINFO,					/// (안쓰임)
	_GS_PKT_NEWUSER,					/// 마을로비: 캐릭터 추가
	_GS_PKT_GETUSER,					/// 마을로비: 캐릭터 리스트 요청
	_GS_PKT_ADDUSER,					/// 마을로비: 캐릭터 리스트 응답
	_GS_PKT_DELUSER,					/// 마을로비: 캐릭터 삭제
	_GS_PKT_MOVE,						/// 마을로비: 이동
	_GS_PKT_STOP,						/// 마을로비: 멈춤
	_GS_PKT_CHAT,						/// (안쓰임)
	_GS_PKT_MYCHAR_PARTS_GET,			/// (안쓰임)
	_GS_PKT_MYCHAR_PARTS_GET_RE,		/// 캐릭터 파츠정보
	_GS_PKT_MYCHAR_DECKS_GET,			/// (안쓰임)
	_GS_PKT_MYCHAR_DECKS_GET_RE,		/// 캐릭터 데크정보
	_GS_PKT_MYCHAR_INVENTORY_GET,		/// (안쓰임)
	_GS_PKT_MYCHAR_INVENTORY_GET_RE,	/// 캐릭터 가방정보
	_GS_PKT_CHAR_GET,					/// 캐릭터 정보
	_GS_PKT_CHAR_GET_RE,
	_GS_PKT_CHAR_INVEN_GET,				/// 캐릭터 가방정보
	_GS_PKT_CHAR_INVEN_GET_RE,
	_GS_PKT_MYCHAR_CARD_MOVE,			/// 인벤토리, 파츠, 데크 간의 카드 이동 패킷
	_GS_PKT_TEST_GAME_MESSAGE,			/// 클라이언트 테스트용 패킷(안쓰임)

	_GS_PKT_1V1_INVITE,					/// 일대일 신청: 
	_GS_PKT_1V1_INVITE_RE,				/// 일대일 신청: 
	_GS_PKT_1V1_RESULT,					/// 일대일 신청: 
	_GS_PKT_1V1_RESULT_RE,				/// 일대일 신청: 
	_GS_PKT_1V1_CANCEL,					/// 일대일 신청: 
	_GS_PKT_1V1_CANCEL_RE,				/// 일대일 신청: 

	_GS_PKT_CREATEROOM,					/// 방: 생성
	_GS_PKT_ENTERROOM,					/// 방: 입장
	_GS_PKT_CREATEROOM_RE,				/// 방:
	_GS_PKT_ENTERROOM_RE,				/// 방:
	_GS_PKT_LEAVEROOM,					/// 방: 퇴장
	_GS_PKT_LEAVEROOM_RE,				/// 방: 
	_GS_PKT_NEW_LEADER,					/// 방: 새로운 방장 알림
	_GS_PKT_NEWUSER_INROOM,				/// 방: 입장한 방원정보 보내기
	_GS_PKT_ADDROOM,					/// 방: 방목록에서 방 추가하기
	_GS_PKT_DELROOM,					/// 방: 방목록에서 방 제거하기
	_GS_PKT_ROOM_INVITE,				/// 대기방: 게임방 유저초대
	_GS_PKT_ROOM_INVITE_REJECT,			/// 대기방: 게임방 유저초대 거절
	_GS_PKT_MODIFYROOM,					/// 대기방: 방 변경
	_GS_PKT_ROOM_DEPORTATION,			/// 대기방: 방원 추방
	_GS_PKT_CHG_PLAYER_SLOT,			/// 대기방: 플레이어 슬롯 변경
	_GS_PKT_CHG_PLAYER_DECK,			/// 플레이어 덱 변경
	_GS_PKT_CHG_PLAYER_READY,			/// 대기방: 방 안에서의 게임 준비완료
	_GS_PKT_GETROOMINFO,				/// 방: 정보보기
	_GS_PKT_GETROOMINFO_RE,				/// 방: 
	_GS_PKT_OBSERVER_ENTERROOM,			/// 방: 관전자 입장
	_GS_PKT_OBSERVER_ENTERROOM_RE,		/// 방:
	_GS_PKT_OBSERVER_LEAVEROOM,			/// 방: 관전자 퇴장
	_GS_PKT_OBSERVER_LEAVEROOM_RE,		/// 방: 
	_GS_PKT_LEVELUP,					/// 캐릭터 레벨 상승
	_GS_PKT_START_GAME,
	_GS_PKT_START_GAME_RE,
	_GS_PKT_RESOURCE_COMPLETE,
	_GS_PKT_RESOURCE_COMPLETE_RE,
	_GS_PKT_RESOURCE_ALL_COMPLETE,
	_GS_PKT_SCENE_COMPLETE,
	_GS_PKT_SCENE_COMPLETE_RE,
	_GS_PKT_SCENE_ALL_COMPLETE,
	_GS_PKT_REQ_SELECT_DECKCARD,
	_GS_PKT_REQ_SELECT_DECKCARD_RE,
	_GS_PKT_HANDCARD_LIST,
	_GS_PKT_NATURE_ATTRIBUTE,
	_GS_PKT_OTHERPLAYER_INFO,
	_GS_PKT_NEW_HANDCARD,
	_GS_PKT_SKILL_ATTACK,
	_GS_PKT_SKILL_ATTACK_RE,
	_GS_PKT_CREATURE_SKILL,
	_GS_PKT_CREATURE_SKILL_RE,
	_GS_PKT_COUNTERBLOW,
	_GS_PKT_CREATURE_MOVE,
	_GS_PKT_CREATURE_MOVE_RE,
	_GS_PKT_PROVOCATION,
	_GS_PKT_PROVOCATION_RE,
	_GS_PKT_CREATURE_CANCELIST,
	_GS_PKT_CREATURE_CANCELIST_RE,
	_GS_PKT_GRAVE,
	_GS_PKT_GRAVE_RE,
	_GS_PKT_USR_MP_UPDATE,
	_GS_PKT_USR_HP_UPDATE,
	_GS_PKT_CREATURE_EP_UPDATE,
	_GS_PKT_CREATURE_HP_UPDATE,
	_GS_PKT_CREATURE_DEAD,
	_GS_PKT_UPDATE_GRAVE_CNT,
	_GS_PKT_UPDATE_DECK_CNT,
	_GS_PKT_HANDCARD_USE,
	_GS_PKT_CREATURE_SUMMON,
	_GS_PKT_MAGICCARD_USE,
	_GS_PKT_ENHANCECARD_USE,
	_GS_PKT_EQUIPCARD_USE,
	_GS_PKT_UPDATE_USERSTATS,
	_GS_PKT_OBSERVER_LIST,				/// 대기방: 관전자 리스트 요청
	_GS_PKT_OBSERVER_LIST_RE,			/// 대기방: 관전자 리스트 응답
	_GS_PKT_DMG,
	_GS_PKT_GAMEOVER,
	_GS_PKT_ALIVE,
	_GS_PKT_UPDATE_USER_STATS,
	_GS_PKT_UPDATE_CREATURE_STATS,
	_GS_PKT_SHUFFLE,
	_GS_PKT_SHUFFLE_RE,
	_GS_PKT_KILL_CREATURE,

	_GS_PKT_COMM_CHAT,					/// 커뮤니티 : XML 채팅패킷
	_GS_PKT_ZONE_ENTREE,				/// 워프 입장 요청
	_GS_PKT_ZONE_ENTREE_RE,				/// 워프 입장 응답
	_GS_PKT_ZONE_ENTREE_LOAD_END,		/// 워프 입장 데이타 로딩완료

	_GS_PKT_TRADE_BOOSTER_USE,			/// 카드거래(부스터) : 사용
	_GS_PKT_TRADE_BOOSTER_VIEW,			/// 카드거래(부스터) : 카드보기
	_GS_PKT_TRADE_BOOSTER_VIEW_RE,		/// 카드거래(부스터) : 카드보기
	_GS_PKT_TRADE_BOOSTER_RESULT,		/// 카드거래(부스터) : 결과	
	_GS_PKT_TRADE_PERSON_INVITE,		/// 카드거래(개인) : 신청
	_GS_PKT_TRADE_PERSON_ACCEPT,		/// 카드거래(개인) : 승락
	_GS_PKT_TRADE_PERSON_CANCEL,		/// 카드거래(개인) : 취소
	_GS_PKT_TRADE_PERSON_CONDITION,		/// 카드거래(개인) : 조건(card,GP)
	_GS_PKT_TRADE_PERSON_READY,			/// 카드거래(개인) : 준비
	_GS_PKT_TRADE_PERSON_START,			/// 카드거래(개인) : 시작
	_GS_PKT_TRADE_PERSON_RESULT,		/// 카드거래(개인) : 결과
	_GS_PKT_TRADE_SHOP_BUY,				/// 카드거래(상점) : 카드구입
	_GS_PKT_TRADE_SHOP_BUY_RE,			/// 카드거래(상점) : 카드구입 결과
	_GS_PKT_TRADE_SHOP_SELL,			/// 카드거래(상점) : 카드판매
	_GS_PKT_TRADE_SHOP_SELL_RE,			/// 카드거래(상점) : 카드판매 결과
	_GS_PKT_TRADE_MIX_EXE,				/// 카드거래(조합) : 실행
	_GS_PKT_TRADE_MIX_CONDITION,		/// 카드거래(조합) : 조건(카드, gp...)

	_GS_PKT_DEL_CARD,					/// 핸드 카드 삭제
	_GS_PKT_ATTACK,
	_GS_PKT_ATTACK_RE,
	_GS_PKT_ATTACK_MOVE,
	_GS_PKT_ATTACK_MOVE_RE,
	_GS_PKT_DEL_CARD_RE,				/// 카드를 무덤으로 보낸다.
	_GS_PKT_MISS,
	_GS_PKT_CHARSEL_ENTREE,				/// 워프 캐릭터 선택 입장요청
	_GS_PKT_CHARSEL_ENTREE_RE,			/// 워프 캐릭터 선택 입장응답
	_GS_PKT_CHARSEL_ENTREE_LOAD_END,	/// 워프 캐릭터 선택 데이타 로딩완료

	_GS_PKT_ROOM_LIST,					/// 방: 방리스트 요청
	_GS_PKT_ROOM_LIST_RE,				/// 방: 방리스트 응답
	
	_GS_PKT_NPC_CREATE,					//// NPC 생성
	_GS_PKT_NPC_MOVE,					//// NPC 이동
	_GS_PKT_NPC_WAIT,					//// NPC 대기
	_GS_PKT_NPC_ATTACK,					//// NPC 공격
	_GS_PKT_NPC_DEATH,					//// NPC 사망
	_GS_PKT_USER_ATTACK_NPC,			//// 유저가 NPC를 공격

	_GS_PKT_TRADE_MIX_RESULT,			/// 카드거래(조합) : 결과
	_GS_PKT_TRADE_PRODUCT_EXE,			/// 카드거래(제작) : 실행
	_GS_PKT_TRADE_PRODUCT_CONDITION,	/// 카드거래(제작) : 조건(카드, gp...)
	_GS_PKT_TRADE_PRODUCT_RESULT,		/// 카드거래(제작) : 결과
	_GS_PKT_TRADE_DISSOLVE_EXE,			/// 카드거래(분해) : 실행
	_GS_PKT_TRADE_DISSOLVE_CONDITION,	/// 카드거래(분해) : 조건(카드, gp...)
	_GS_PKT_TRADE_DISSOLVE_RESULT,		/// 카드거래(분해) : 결과
	_GS_PKT_TRADE_AUTION,				/// 카드거래(경매) :
	_GS_PKT_DUNGEON_ENTREE,				/// 던전 입장 요청
	_GS_PKT_DUNGEON_ENTREE_RE,			/// 던전 입장 응답
	_GS_PKT_DUNGEON_ENTREE_LOAD_END,	/// 던전 입장 데이타 로딩완료
	_GS_PKT_DUNGEON_LEAVE,				/// 던전 퇴장
	_GS_PKT_DUNGEON_LEAVE_RE,			/// 던전 퇴장
	_GS_PKT_PICKUP_CARD,				/// 카드 줍기
	_GS_PKT_PICKUP_CARD_RE,				/// 카드 줍기
	_GS_PKT_AWARD,						/// 게임 보상
	_GS_PKT_BATTLE_SESSION,				/// pve 전투 시작
	_GS_PKT_NPC_TRACE,					/// NPC추적
	_GS_PKT_TRADE_SELLEDCARD_BUY,		/// 카드거래(상점) : 판매한 카드 재구입
	_GS_PKT_TRADE_SELLEDCARD_BUY_RE,	/// 카드거래(상점) : 판매한 카드 재구입 결과
	_GS_PKT_TEST,
	_GS_PKT_TRADE_SHOP_CANCEL,			/// 카드거래(상점) : 취소
	_GS_PKT_TRADE_MIX_CANCEL,			/// 카드거래(조합) : 취소
	_GS_PKT_TRADE_PRODUCT_CANCEL,		/// 카드거래(제작) : 취소
	_GS_PKT_TRADE_DISSOLVE_CANCEL,		/// 카드거래(분해) : 취소
	_GS_PKT_TRADE_BOOSTER_CANCEL,		/// 카드거래(부스터) : 취소
	_GS_PKT_TRADE_SHOP_OPEN,			/// 카드거래(상점) : 시작
	_GS_PKT_TRADE_MIX_OPEN,				/// 카드거래(조합) : 시작
	_GS_PKT_TRADE_PRODUCT_OPEN,			/// 카드거래(제작) : 시작
	_GS_PKT_TRADE_DISSOLVE_OPEN,		/// 카드거래(분해) : 시작
	_GS_PKT_TRADE_BOOSTER_OPEN,			/// 카드거래(부스터) : 시작
	_GS_PKT_MP_BEGIN,
	_GS_PKT_EP_BEGIN,
	_GS_PKT_USER_MONEY_UPDATE,
	_GS_PKT_USER_EXP_UPDATE,
	_GS_PKT_COMPENSATION,
	_GS_PKT_ACQUIRE_CARD_IN_COMBAT,
	_GS_PKT_SELECT_COMPENSATION_CARD,
	_GS_PKT_SELECT_COMPENSATION_CARD_RE,
	//파티 찾기 ui
	_GS_PKT_CREATE_PARTY,				///파티 생성
	_GS_PKT_CREATE_PARTY_RE,			///파티 생성 결과
	_GS_PKT_INVITE_PARTY,				///파티 초대
	_GS_PKT_INVITE_PARTY_RE,			///파티 초대 결과
	_GS_PKT_NEW_PARTY_MEMBER,			///새로들어온 파티원 //기존에 잇는 파티원에게 전송
	_GS_PKT_ENTER_PARTY,				///파티 입장
	_GS_PKT_ENTER_PARTY_RE,				///파티 입장 결과
	_GS_PKT_LEAVE_PARTY,				///파티 퇴장
	_GS_PKT_LEAVE_PARTY_RE,				///파티 퇴장 결과
	_GS_PKT_NEW_PARTY_LEADER,			///새로운 파티장 선출
	_GS_PKT_SEARCH_PARTY,				///파티 찾기
	//
	_GS_PKT_CHG_PARTY_OPT,				//파티 옵션 변경
	_GS_PKT_CHG_PARTY_OPT_RE,			//파티 옵션 변경

	_GS_PKT_READY_PARTY,
	_GS_PKT_READY_PARTY_RE,

	_GS_PKT_START_PARTY,
	_GS_PKT_START_PARTY_RE,

	_GS_PKT_HOLY_PLACE,					//던전의 성소에서의 사용한 카드 복구
	_GS_PKT_HOLY_PLACE_RE,			

	_GS_PKT_RESURRECTION,				//부활 요청
	_GS_PKT_RESURRECTION_RE,			//부활 요청 처리 결과

	_GS_PKT_USER_DEATH,

	_GS_PKT_UPDATE_LIFE_PT,				//유저가 가지고 잇는 라이프 포인트 전송

	_GS_PKT_UPDATE_TOKEN,				///토큰 갱신
	_GS_PKT_BATTLE_SESSION_END,			/// pve 전투 종료
//#ifdef SUB_CHANNEL
	_GS_PKT_CHANGE_SUBCHANNEL,			//sub channel 변경 요청
//#endif
	_GS_PKT_CHG_PLAYER_DECK_RE,			/// 플레이어 덱 변경 결과 

	_GS_PKT_CLICK_NPC,
};

//////////////////////////////////////////////////////////////////////
// Login server packet defines.
// Created by Timothy 2009.05.16.
//////////////////////////////////////////////////////////////////////
//Client->Server
struct LS_PKT_LOGIN : PACKET_BASE
{
	char	szUserID[_MAX_USER_ID_SIZE];	/// 아이디
	char	szPwd[_MAX_PWD_SIZE];			/// 패스워드
	unsigned short wProtocolVersion;
	LS_PKT_LOGIN() {
		memset(this, 0x00, sizeof(LS_PKT_LOGIN));
		MPID = _LS_PKT_LOGIN;
		Len = sizeof(LS_PKT_LOGIN);
	};
};

//Server->Client
struct LS_PKT_LOGIN_RE : PACKET_BASE
{
	WORD		wResult;
	char		szSessionKey[_MAX_SESSION_KEY_SIZE];
	LS_PKT_LOGIN_RE() {
		memset(this, 0x00, sizeof(LS_PKT_LOGIN_RE));
		MPID = _LS_PKT_LOGIN_RE;
		Len = sizeof(LS_PKT_LOGIN_RE);
	};
};

//Client->Server
struct LS_PKT_SERVER_LIST : PACKET_BASE
{
	LS_PKT_SERVER_LIST() {
		memset(this, 0x00, sizeof(LS_PKT_SERVER_LIST));
		MPID = _LS_PKT_SERVER_LIST;
		Len = sizeof(LS_PKT_SERVER_LIST);
	};
};

//Server->Client
struct LS_PKT_SERVER_LIST_RE : PACKET_BASE
{
	unsigned short wCount;
	char pData[_MAX_DEFINED_DATA];
	LS_PKT_SERVER_LIST_RE() {
		memset(this, 0x00, sizeof(LS_PKT_SERVER_LIST_RE));
		MPID = _LS_PKT_SERVER_LIST_RE;
		Len = sizeof(LS_PKT_SERVER_LIST_RE);
	};
};

//Client->Server
struct LS_PKT_CHANNEL_LIST : PACKET_BASE
{
	WCHAR szServerName[_MAX_SERVER_NAME];
	LS_PKT_CHANNEL_LIST() {
		memset(this, 0x00, sizeof(LS_PKT_CHANNEL_LIST));
		MPID = _LS_PKT_CHANNEL_LIST;
		Len = sizeof(LS_PKT_CHANNEL_LIST);
	};
};

//Server->Client
struct LS_PKT_CHANNEL_LIST_RE : PACKET_BASE
{
	unsigned short wCount;
	char pData[_MAX_DEFINED_DATA];	// include CHANNEL_INFO structure size X wCounts
	LS_PKT_CHANNEL_LIST_RE() {
		memset(this, 0x00, sizeof(LS_PKT_CHANNEL_LIST_RE));
		MPID = _LS_PKT_CHANNEL_LIST_RE;
		Len = sizeof(LS_PKT_CHANNEL_LIST_RE);
	};
};

//////////////////////////////////////////////////////////////////////
// Game server packet defines.
// Created by Timothy 2009.05.18.
//////////////////////////////////////////////////////////////////////

//Client->Server
struct GS_PKT_LOGIN : PACKET_BASE
{
	char			szUserID[_MAX_USER_ID_SIZE];			/// 아이디
	char			szSessionKey[_MAX_SESSION_KEY_SIZE];	/// 인증키
	unsigned short	wProtocolVersion;
	GS_PKT_LOGIN() {
		memset(this, 0x00, sizeof(GS_PKT_LOGIN));
		MPID = _GS_PKT_LOGIN;
		Len = sizeof(GS_PKT_LOGIN);
	};
};

//Server->Client
struct GS_PKT_LOGIN_RE : PACKET_BASE
{
	WORD		wSid;									/// 고유번호
	WORD		wResult;								/// 결과값
	WORD		wChannelID;								/// 접속 채널
	WORD		wMaxUserCount;							/// 접속 채널의 동접 최대수
	WORD		wCharCount;								/// 캐릭터 갯수
	char		szCharNames[_MAX_CHAR_ID_SIZE*_MAX_USER_CHAR_SIZE*2]; /// 캐릭터이름 리스트, 단위: char(20)
	int			nCP;									/// 현금포인트
	GS_PKT_LOGIN_RE() {
		memset(this, 0x00, sizeof(GS_PKT_LOGIN_RE));
		MPID = _GS_PKT_LOGIN_RE;
		Len = sizeof(GS_PKT_LOGIN_RE);
	};
};

//Server<->Client
struct GS_PKT_LOGOUT : PACKET_BASE
{
	WORD		wSid;									/// 고유번호
	GS_PKT_LOGOUT() {
		memset(this, 0x00, sizeof(GS_PKT_LOGOUT));
		MPID = _GS_PKT_LOGOUT;
		Len = sizeof(GS_PKT_LOGOUT);
	};
};

//Server->Client
struct	GS_PKT_USERINFO : PACKET_BASE
{
	DWORD		dwCount;								/// 유저의 갯수
	char		pData[_MAX_DEFINED_DATA];				/// 단위: 고유번호(WORD)+캐릭터(CHAR_DATA)+원래위치(float[3])+목표위치(float[3])
	GS_PKT_USERINFO() {
		memset(this, 0x00, sizeof(GS_PKT_USERINFO));
		MPID = _GS_PKT_USERINFO;
		Len = sizeof(GS_PKT_USERINFO);
	};
};

//Server->Client
struct GS_PKT_NEWUSER : PACKET_BASE
{
	WORD		wSid;									/// 고유번호
	CHAR_DATA	Character;								/// 캐릭터
	GS_PKT_NEWUSER() {
		memset(this, 0x00, sizeof(GS_PKT_NEWUSER));
		MPID = _GS_PKT_NEWUSER;
		Len = sizeof(GS_PKT_NEWUSER);
	};
};

//Client->Server
struct GS_PKT_GETUSER : PACKET_BASE
{
	WORD		wReqSid;								/// 요청 번호
	GS_PKT_GETUSER() {
		memset(this, 0x00, sizeof(GS_PKT_GETUSER));
		MPID = _GS_PKT_GETUSER;
		Len = sizeof(GS_PKT_GETUSER);
	};
};

//Server->Client
struct GS_PKT_ADDUSER : PACKET_BASE
{
	WORD		wReqSid;								/// 다음요청번호:양수 ,  받기완료:0
	WORD		wCount;									/// 보낸 유저의 갯수
	char		pData[_MAX_DEFINED_DATA];				/// 단위: 고유번호(WORD)+캐릭터(CHAR_DATA)+원래위치(float[3])+목표위치(float[3])
	GS_PKT_ADDUSER() {
		memset(this, 0x00, sizeof(GS_PKT_ADDUSER));
		MPID = _GS_PKT_ADDUSER;
		Len = sizeof(GS_PKT_ADDUSER);
	};
};

//Server->Client
struct GS_PKT_DELUSER : PACKET_BASE
{
	WORD		wSid;									/// 로비에서 제거되는 유저
	GS_PKT_DELUSER() {
		memset(this, 0x00, sizeof(GS_PKT_DELUSER));
		MPID = _GS_PKT_DELUSER;
		Len = sizeof(GS_PKT_DELUSER);
	};
};

//Server<-Client
struct GS_PKT_CHAR_COUNT : PACKET_BASE
{
	WCHAR			szName[_MAX_CHAR_ID_SIZE];			/// 캐릭터 이름 중복확인
	GS_PKT_CHAR_COUNT() {
		memset(this, 0, sizeof(GS_PKT_CHAR_COUNT));
		MPID = _GS_PKT_CHAR_COUNT;
		Len = sizeof(GS_PKT_CHAR_COUNT);
	};
};

struct GS_PKT_CHAR_COUNT_RE : PACKET_BASE
{
	WORD	wCount;										/// 요청한 캐릭터의 이름 갯수
	WORD	wResult;
	GS_PKT_CHAR_COUNT_RE() {
		memset(this, 0, sizeof(GS_PKT_CHAR_COUNT_RE));
		MPID = _GS_PKT_CHAR_COUNT_RE;
		Len = sizeof(GS_PKT_CHAR_COUNT_RE);
	};
};

//Server<-Client
struct GS_PKT_MYCHAR_GET : PACKET_BASE
{
	WCHAR			szName[_MAX_CHAR_ID_SIZE];			/// 이름
	GS_PKT_MYCHAR_GET() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_GET));
		MPID = _GS_PKT_MYCHAR_GET;
		Len = sizeof(GS_PKT_MYCHAR_GET);
	};
};

//Server->Client
struct GS_PKT_MYCHAR_GET_RE : PACKET_BASE
{
	CHAR_DATA		Character;							/// 캐릭터
	WORD			wResult;							/// 결과값
	GS_PKT_MYCHAR_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_GET_RE));
		MPID = _GS_PKT_MYCHAR_GET_RE;
		Len = sizeof(GS_PKT_MYCHAR_GET_RE);
	};
};

//Server<-Client
struct  GS_PKT_MYCHAR_ADD : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];				/// 이름
	BYTE		byAttr;									/// 속성 물,불...
	BYTE		byRace;									/// 종족
	BYTE		bySex;									/// 성별
	BYTE		byHead;									/// 머리(얼굴)
	BYTE		byHair;									/// 머리털
	BYTE		byDummy;
	int			nSkinColor;								/// 피부 색
	int			nHairColor;								/// 머리털 색
	GS_PKT_MYCHAR_ADD() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ADD));
		MPID = _GS_PKT_MYCHAR_ADD;
		Len = sizeof(GS_PKT_MYCHAR_ADD);
	};
};

//Server->Client
struct  GS_PKT_MYCHAR_ADD_RE : PACKET_BASE
{
	CHAR_DATA	Character;								/// 캐릭터
	WORD		wResult;								/// 결과값
	GS_PKT_MYCHAR_ADD_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ADD_RE));
		MPID = _GS_PKT_MYCHAR_ADD_RE;
		Len = sizeof(GS_PKT_MYCHAR_ADD_RE);
	};
};

//Server<-Client
struct  GS_PKT_MYCHAR_DEL : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];				/// 캐릭터 이름
	GS_PKT_MYCHAR_DEL() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_DEL));
		MPID = _GS_PKT_MYCHAR_DEL;
		Len = sizeof(GS_PKT_MYCHAR_DEL);
	};
};

//Server->Client
struct  GS_PKT_MYCHAR_DEL_RE : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];				/// 캐릭터 이름
	WORD		wResult;
	GS_PKT_MYCHAR_DEL_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_DEL_RE));
		MPID = _GS_PKT_MYCHAR_DEL_RE;
		Len = sizeof(GS_PKT_MYCHAR_DEL_RE);
	};
};

//Server<-Client
struct  GS_PKT_MYCHAR_ENTREE : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];
	GS_PKT_MYCHAR_ENTREE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ENTREE));
		MPID = _GS_PKT_MYCHAR_ENTREE;
		Len = sizeof(GS_PKT_MYCHAR_ENTREE);
	};
};

//Server->Client
struct  GS_PKT_MYCHAR_ENTREE_RE : PACKET_BASE
{
	int		nIdxMap;
	WORD	wResult;
	GS_PKT_MYCHAR_ENTREE_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ENTREE_RE));
		MPID = _GS_PKT_MYCHAR_ENTREE_RE;
		Len = sizeof(GS_PKT_MYCHAR_ENTREE_RE);
	};
};
//Client->Server
struct  GS_PKT_MYCHAR_ENTREE_LOAD_END : PACKET_BASE
{
	GS_PKT_MYCHAR_ENTREE_LOAD_END() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ENTREE_LOAD_END));
		MPID = _GS_PKT_MYCHAR_ENTREE_LOAD_END;
		Len = sizeof(GS_PKT_MYCHAR_ENTREE_LOAD_END);
	};
};
//Server<->Client
struct  GS_PKT_MOVE : PACKET_BASE
{
	WORD		wSid;
	WORD		wFlag;
	float		fSpeed;
	float		fPosOrig[3];	/// 원래위치
	float		fPosGoal[3];	/// 목표위치
	GS_PKT_MOVE() {
		memset(this, 0, sizeof(GS_PKT_MOVE));
		MPID = _GS_PKT_MOVE;
		Len = sizeof(GS_PKT_MOVE);
	};
};

//Server<->Client
struct  GS_PKT_STOP : PACKET_BASE
{
	WORD		wSid;
	float		fPosStop[3];	/// 정지위치
	GS_PKT_STOP() {
		memset(this, 0, sizeof(GS_PKT_STOP));
		MPID = _GS_PKT_STOP;
		Len = sizeof(GS_PKT_STOP);
	};
};
////----------------------------------------------------------------------------------
//Server<->Client
struct  GS_PKT_CHAT : PACKET_BASE
{
	WORD		wSid;
	WORD		dwLen;
	WORD		wChatType;
	WORD		wSidDest;
	char		szChat[_MAX_CHAT_SIZE];
	GS_PKT_CHAT() {
		memset(this, 0, sizeof(GS_PKT_CHAT));
		MPID = _GS_PKT_CHAT;
		Len = sizeof(GS_PKT_CHAT);
	};
};
//Server<-Client
struct  GS_PKT_MYCHAR_PARTS_GET : PACKET_BASE
{
	GS_PKT_MYCHAR_PARTS_GET() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_PARTS_GET));
		MPID = _GS_PKT_MYCHAR_PARTS_GET;
		Len = sizeof(GS_PKT_MYCHAR_PARTS_GET);
	};
};
//Server->Client
struct  GS_PKT_MYCHAR_PARTS_GET_RE : PACKET_BASE
{
	CHAR_PARTS		Parts;							/// 파츠
	GS_PKT_MYCHAR_PARTS_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_PARTS_GET_RE));
		MPID = _GS_PKT_MYCHAR_PARTS_GET_RE;
		Len = sizeof(GS_PKT_MYCHAR_PARTS_GET_RE);
	};
};
//Server<-Client
struct  GS_PKT_MYCHAR_DECKS_GET : PACKET_BASE
{
	GS_PKT_MYCHAR_DECKS_GET() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_DECKS_GET));
		MPID = _GS_PKT_MYCHAR_DECKS_GET;
		Len = sizeof(GS_PKT_MYCHAR_DECKS_GET);
	};
};
//Server->Client
struct  GS_PKT_MYCHAR_DECKS_GET_RE : PACKET_BASE
{
	CHAR_DECK		Decks[_MAX_CHAR_DECK_SIZE/3];	/// 데크
	//unsigned short wCount;
	//char pData[_MAX_DEFINED_DATA];
	GS_PKT_MYCHAR_DECKS_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_DECKS_GET_RE));
		MPID = _GS_PKT_MYCHAR_DECKS_GET_RE;
		Len = sizeof(GS_PKT_MYCHAR_DECKS_GET_RE);
	};
};
//Server<-Client
struct  GS_PKT_MYCHAR_INVENTORY_GET : PACKET_BASE
{
	GS_PKT_MYCHAR_INVENTORY_GET() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_INVENTORY_GET));
		MPID = _GS_PKT_MYCHAR_INVENTORY_GET;
		Len = sizeof(GS_PKT_MYCHAR_INVENTORY_GET);
	};
};
//Server->Client
struct  GS_PKT_MYCHAR_INVENTORY_GET_RE : PACKET_BASE
{
	CHAR_INVENTORY	Inventory;						/// 가방
	GS_PKT_MYCHAR_INVENTORY_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_INVENTORY_GET_RE));
		MPID = _GS_PKT_MYCHAR_INVENTORY_GET_RE;
		Len = sizeof(GS_PKT_MYCHAR_INVENTORY_GET_RE);
	};
};

//Server<-Client
struct  GS_PKT_CHAR_GET : PACKET_BASE
{
	WORD		wSid;			// 유저 고유번호
	GS_PKT_CHAR_GET() {
		memset(this, 0, sizeof(GS_PKT_CHAR_GET));
		MPID = _GS_PKT_CHAR_GET;
		Len = sizeof(GS_PKT_CHAR_GET);
	};
};

//Client<-Server
struct  GS_PKT_CHAR_GET_RE : PACKET_BASE
{
	CHAR_DATA	Character;			// 유저 캐릭터
	GS_PKT_CHAR_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_CHAR_GET_RE));
		MPID = _GS_PKT_CHAR_GET_RE;
		Len = sizeof(GS_PKT_CHAR_GET_RE);
	};
};

//Server<-Client
struct  GS_PKT_CHAR_INVEN_GET : PACKET_BASE
{
	WORD		wSid;				// 유저 고유번호
	GS_PKT_CHAR_INVEN_GET() {
		memset(this, 0, sizeof(GS_PKT_CHAR_INVEN_GET));
		MPID = _GS_PKT_CHAR_INVEN_GET;
		Len = sizeof(GS_PKT_CHAR_INVEN_GET);
	};
};

//Client<-Server
struct  GS_PKT_CHAR_INVEN_GET_RE : PACKET_BASE
{
	CHAR_INVENTORY	Inventory;		// 유저 캐릭터 가방
	GS_PKT_CHAR_INVEN_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_CHAR_INVEN_GET_RE));
		MPID = _GS_PKT_CHAR_INVEN_GET_RE;
		Len = sizeof(GS_PKT_CHAR_INVEN_GET_RE);
	};
};

//Server<->Client
struct  GS_PKT_MYCHAR_CARD_MOVE : PACKET_BASE
{
	WORD			wSid;			// 유저 고유번호, 받는 값
	int				nMoveKind;		// enum eCHAR_CAED_MOVE_KIND{}; 값중에 하나, 주고 받는 값
	DWORD			nIdxCard;		// 대상 카드, 받는 값
	WORD			wOrigSlot;		// 원래 슬롯, 주고 받는 값
	WORD			wGoalSlot;		// 목표 슬롯, 주고 받는 값
	WORD			wResult;		// 0이면 성공, 0이 아니면 실패, 받는값
	GS_PKT_MYCHAR_CARD_MOVE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_CARD_MOVE));
		MPID = _GS_PKT_MYCHAR_CARD_MOVE;
		Len = sizeof(GS_PKT_MYCHAR_CARD_MOVE);
	};
};
//Server<->Client
struct  GS_PKT_TEST_GAME_MESSAGE : PACKET_BASE
{
	char szCmd[_MAX_CHAT_SIZE];
	GS_PKT_TEST_GAME_MESSAGE() {
		memset(this, 0, sizeof(GS_PKT_TEST_GAME_MESSAGE));
		MPID = _GS_PKT_TEST_GAME_MESSAGE;
		Len = sizeof(GS_PKT_TEST_GAME_MESSAGE);
	};
};
//Server<->Client
struct GS_PKT_COMM_CHAT : PACKET_BASE
{
	WORD	wFrom;
	WORD	wTo;
	WORD	wType;
	WCHAR	szCmd[_MAX_CHAT_SIZE*2];
	GS_PKT_COMM_CHAT() {
		memset(this, 0, sizeof(GS_PKT_COMM_CHAT));
		MPID = _GS_PKT_COMM_CHAT;
		Len = sizeof(GS_PKT_COMM_CHAT);
	};
};
//Server<-Client
struct GS_PKT_ZONE_ENTREE : PACKET_BASE
{
	int		nMapIdx;	/// 입장할 맵 인덱스
	GS_PKT_ZONE_ENTREE() {
		memset(this, 0, sizeof(GS_PKT_ZONE_ENTREE));
		MPID = _GS_PKT_ZONE_ENTREE;
		Len = sizeof(GS_PKT_ZONE_ENTREE);
	};
};
//Server->Client
struct GS_PKT_ZONE_ENTREE_RE : PACKET_BASE
{
	WORD	wResult;	/// _ERR_NONE이면 성공
	int		nMapIdx;	/// 입장할 맵 인덱스
	GS_PKT_ZONE_ENTREE_RE() {
		memset(this, 0, sizeof(GS_PKT_ZONE_ENTREE_RE));
		MPID = _GS_PKT_ZONE_ENTREE_RE;
		Len = sizeof(GS_PKT_ZONE_ENTREE_RE);
	};
};
//Server<-Client
struct GS_PKT_ZONE_ENTREE_LOAD_END : PACKET_BASE
{
	GS_PKT_ZONE_ENTREE_LOAD_END() {
		memset(this, 0, sizeof(GS_PKT_ZONE_ENTREE_LOAD_END));
		MPID = _GS_PKT_ZONE_ENTREE_LOAD_END;
		Len = sizeof(GS_PKT_ZONE_ENTREE_LOAD_END);
	};
};
//Server<-Client
struct GS_PKT_DUNGEON_ENTREE : PACKET_BASE
{
	int		nMapIdx;	/// 입장할 맵 인덱스
	GS_PKT_DUNGEON_ENTREE() {
		memset(this, 0, sizeof(GS_PKT_DUNGEON_ENTREE));
		MPID = _GS_PKT_DUNGEON_ENTREE;
		Len = sizeof(GS_PKT_DUNGEON_ENTREE);
	};
};
//Server->Client
struct GS_PKT_DUNGEON_ENTREE_RE : PACKET_BASE
{
	int		nMapIdx;	/// 입장할 맵 인덱스
	WORD	wResult;	/// _ERR_NONE이면 성공
	GS_PKT_DUNGEON_ENTREE_RE() {
		memset(this, 0, sizeof(GS_PKT_DUNGEON_ENTREE_RE));
		MPID = _GS_PKT_DUNGEON_ENTREE_RE;
		Len = sizeof(GS_PKT_DUNGEON_ENTREE_RE);
	};
};
//Server<-Client
struct GS_PKT_DUNGEON_ENTREE_LOAD_END : PACKET_BASE
{
	GS_PKT_DUNGEON_ENTREE_LOAD_END() {
		memset(this, 0, sizeof(GS_PKT_DUNGEON_ENTREE_LOAD_END));
		MPID = _GS_PKT_DUNGEON_ENTREE_LOAD_END;
		Len = sizeof(GS_PKT_DUNGEON_ENTREE_LOAD_END);
	};
};

//Server<-Client
struct GS_PKT_DUNGEON_LEAVE : PACKET_BASE
{
	GS_PKT_DUNGEON_LEAVE() {
		memset(this, 0, sizeof(GS_PKT_DUNGEON_LEAVE));
		MPID = _GS_PKT_DUNGEON_LEAVE;
		Len = sizeof(GS_PKT_DUNGEON_LEAVE);
	};
};
//Server<-Client
struct GS_PKT_DUNGEON_LEAVE_RE : PACKET_BASE
{
	GS_PKT_DUNGEON_LEAVE_RE() {
		memset(this, 0, sizeof(GS_PKT_DUNGEON_LEAVE_RE));
		MPID = _GS_PKT_DUNGEON_LEAVE_RE;
		Len = sizeof(GS_PKT_DUNGEON_LEAVE_RE);
	};

	WORD wSid;
	WORD Result;
};	

//Server<-Client
struct GS_PKT_CHARSEL_ENTREE : PACKET_BASE
{
	GS_PKT_CHARSEL_ENTREE() {
		memset(this, 0, sizeof(GS_PKT_CHARSEL_ENTREE));
		MPID = _GS_PKT_CHARSEL_ENTREE;
		Len = sizeof(GS_PKT_CHARSEL_ENTREE);
	};
};

//Server->Client
struct GS_PKT_CHARSEL_ENTREE_RE : PACKET_BASE
{
	WORD	wResult;	/// _ERR_NONE이면 성공
	GS_PKT_CHARSEL_ENTREE_RE() {
		memset(this, 0, sizeof(GS_PKT_CHARSEL_ENTREE_RE));
		MPID = _GS_PKT_CHARSEL_ENTREE_RE;
		Len = sizeof(GS_PKT_CHARSEL_ENTREE_RE);
	};
};

//Server<-Client
struct GS_PKT_CHARSEL_ENTREE_LOAD_END : PACKET_BASE
{
	GS_PKT_CHARSEL_ENTREE_LOAD_END() {
		memset(this, 0, sizeof(GS_PKT_CHARSEL_ENTREE_LOAD_END));
		MPID = _GS_PKT_CHARSEL_ENTREE_LOAD_END;
		Len = sizeof(GS_PKT_CHARSEL_ENTREE_LOAD_END);
	};
};
//Server<-Client
struct GS_PKT_PICKUP_CARD : PACKET_BASE
{
	DWORD	dwCardIndex;
	GS_PKT_PICKUP_CARD() {
		memset(this, 0, sizeof(GS_PKT_PICKUP_CARD));
		MPID = _GS_PKT_PICKUP_CARD;
		Len = sizeof(GS_PKT_PICKUP_CARD);
	};
};
//Server->Client
struct GS_PKT_PICKUP_CARD_RE : PACKET_BASE
{
	CHAR_GAIN_CARD	GetCard;	/// 추가카드정보
	WORD			wSlot;		/// 추가카드의 인벤토리의 슬롯
	WORD			wResult;	/// 결과: 0이 아니면 실패
	GS_PKT_PICKUP_CARD_RE() {
		memset(this, 0, sizeof(GS_PKT_PICKUP_CARD_RE));
		MPID = _GS_PKT_PICKUP_CARD_RE;
		Len = sizeof(GS_PKT_PICKUP_CARD_RE);
	};
};
//Server->Client
struct GS_PKT_AWARD : PACKET_BASE
{
	CHAR_DATA		Character;						/// 캐릭터
	CHAR_GAIN_CARD	Card[_MAX_AWARD_CARD_SIZE];		/// 추가카드정보
	WORD			wSlot[_MAX_AWARD_CARD_SIZE];	/// 추가카드의 인벤토리의 슬롯
	WORD			wDest[_MAX_AWARD_CARD_SIZE];	/// 이동위치[0: 없음, 1:가방, 2:메일함], eTRADE_CARD_MOVE의 값
	GS_PKT_AWARD() {
		memset(this, 0, sizeof(GS_PKT_AWARD));
		MPID = _GS_PKT_AWARD;
		Len = sizeof(GS_PKT_AWARD);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_INVITE : PACKET_BASE
{
	WORD	wFrom;		/// 신청자
	WORD	wDest;		/// 대상자
	WORD	wResult;	/// 결과: 0이 아니면 실패
	GS_PKT_TRADE_PERSON_INVITE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_INVITE));
		MPID = _GS_PKT_TRADE_PERSON_INVITE;
		Len = sizeof(GS_PKT_TRADE_PERSON_INVITE);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_ACCEPT : PACKET_BASE
{
	WORD	wFrom;		/// 신청자
	WORD	wDest;		/// 대상자
	WORD	wIsok;		/// 승락찬성: 1, 승락거절: 0
	WORD	wResult;	/// 결과: 0이 아니면 실패
	GS_PKT_TRADE_PERSON_ACCEPT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_ACCEPT));
		MPID = _GS_PKT_TRADE_PERSON_ACCEPT;
		Len = sizeof(GS_PKT_TRADE_PERSON_ACCEPT);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_CANCEL : PACKET_BASE
{
	WORD			wSid;		/// 받는값
	int				nGP;		/// 받는값
	WORD			wDest[_MAX_TRADE_CARD_PERSON];	/// 이동위치[0: 없음, 1:가방, 2:메일함], eTRADE_CARD_MOVE의 값
	WORD			wSlot[_MAX_TRADE_CARD_PERSON];	/// 받는값 (복귀카드 인벤번호), -1이면 카드없음
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PERSON];	/// 받는값 (복귀카드)
	WORD			wResult;	/// 받는값 (결과: 0이 아니면 실패)
	GS_PKT_TRADE_PERSON_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_CANCEL));
		MPID = _GS_PKT_TRADE_PERSON_CANCEL;
		Len = sizeof(GS_PKT_TRADE_PERSON_CANCEL);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_CONDITION : PACKET_BASE
{
	WORD			wSid;		/// 고유번호
	int				nMoveKind;	/// enum eCHAR_CAED_MOVE_KIND{}; 값중에 하나, 주고 받는 값, 카드이동 없이 게임포인트만 적용시(nMoveKind = _CHAR_CAED_MOVE_NONE) 
	WORD			wOrigSlot;	/// 원래 슬롯, 주고 받는 값
	WORD			wGoalSlot;	/// 목표 슬롯, 주고 받는 값
	int				nTradeGP;	/// 거래 게임포인트, 주고 받는 값
	int				nGP;		/// 캐릭터 게임포임트
	CHAR_GAIN_CARD	Card;		/// 대상 카드, 받는 값
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패, 받는값
	GS_PKT_TRADE_PERSON_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_CONDITION));
		MPID = _GS_PKT_TRADE_PERSON_CONDITION;
		Len = sizeof(GS_PKT_TRADE_PERSON_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_READY : PACKET_BASE
{
	WORD			wSid;		/// 고유번호, 받는값
	WORD			wReady;		/// 안쓰임(0:준비 비활성, 1:준비 활성)
	GS_PKT_TRADE_PERSON_READY() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_READY));
		MPID = _GS_PKT_TRADE_PERSON_READY;
		Len = sizeof(GS_PKT_TRADE_PERSON_READY);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_START : PACKET_BASE
{
	WORD			wSid;		/// 고유번호, 받는값
	WORD			wStart;		/// 안쓰임(0:시작 비활성, 1:시작 활성)
	GS_PKT_TRADE_PERSON_START() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_START));
		MPID = _GS_PKT_TRADE_PERSON_START;
		Len = sizeof(GS_PKT_TRADE_PERSON_START);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_RESULT : PACKET_BASE
{
	WORD			wDest[_MAX_TRADE_CARD_PERSON];	/// 이동위치[0: 없음, 1:가방, 2:메일함], eTRADE_CARD_MOVE의 값
	WORD			wSlot[_MAX_TRADE_CARD_PERSON];	/// 얻은 카드의 인벤토리 슬롯번호 -1이면 카드없음
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PERSON];	/// 얻은 카드
	int				nGetGP;		/// 게임포인트
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_PERSON_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_RESULT));
		MPID = _GS_PKT_TRADE_PERSON_RESULT;
		Len = sizeof(GS_PKT_TRADE_PERSON_RESULT);
	};
};
//Server->Client
struct GS_PKT_TRADE_SHOP_OPEN : PACKET_BASE
{
	WORD			wResult;							/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_SHOP_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_OPEN));
		MPID = _GS_PKT_TRADE_SHOP_OPEN;
		Len = sizeof(GS_PKT_TRADE_SHOP_OPEN);
	};
};
//Server<->Client
struct GS_PKT_TRADE_SHOP_CANCEL : PACKET_BASE
{
	WORD			wResult;							/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_SHOP_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_CANCEL));
		MPID = _GS_PKT_TRADE_SHOP_CANCEL;
		Len = sizeof(GS_PKT_TRADE_SHOP_CANCEL);
	};
};
//Server<-Client
struct GS_PKT_TRADE_SHOP_BUY : PACKET_BASE
{
	DWORD			dwCardIndex;	/// 구매할 카드인덱스
	DWORD			dwCount;		/// 구매할 카드수량
	GS_PKT_TRADE_SHOP_BUY() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_BUY));
		MPID = _GS_PKT_TRADE_SHOP_BUY;
		Len = sizeof(GS_PKT_TRADE_SHOP_BUY);
	};
};
//Server->Client
struct GS_PKT_TRADE_SHOP_BUY_RE : PACKET_BASE
{
	CHAR_GAIN_CARD	Card[_MAX_INVENTORY_CARD_SIZE];		/// 구매한 카드의 정보
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// 구매한 카드의 가방슬롯
	DWORD			dwSlotTotal;						/// 구입된 슬롯의 갯수
	int				nGP;								/// 구매후 남은 포인트
	WORD			wResult;							/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_SHOP_BUY_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_BUY_RE));
		MPID = _GS_PKT_TRADE_SHOP_BUY_RE;
		Len = sizeof(GS_PKT_TRADE_SHOP_BUY_RE);
	};
};
//Server<-Client
struct GS_PKT_TRADE_SELLEDCARD_BUY : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// 구매할 재구입목록의 슬롯번호
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];	/// 각 슬롯에서 구입할 갯수
	DWORD			dwSlotTotal;						/// 재구입할 슬롯의 갯수
	GS_PKT_TRADE_SELLEDCARD_BUY() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SELLEDCARD_BUY));
		MPID = _GS_PKT_TRADE_SELLEDCARD_BUY;
		Len = sizeof(GS_PKT_TRADE_SELLEDCARD_BUY);
	};
};
//Server->Client
struct GS_PKT_TRADE_SELLEDCARD_BUY_RE : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// 삽입될 가방 슬롯번호
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];	/// 각 슬롯에서 구입할 갯수
	DWORD			dwSlotTotal;						/// 재구입할 슬롯의 갯수
	CHAR_GAIN_CARD	Card[_MAX_INVENTORY_CARD_SIZE];		/// 재구입한 카드정보
	int				nGP;								/// 구매후 남은 포인트
	WORD			wResult;							/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_SELLEDCARD_BUY_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SELLEDCARD_BUY_RE));
		MPID = _GS_PKT_TRADE_SELLEDCARD_BUY_RE;
		Len = sizeof(GS_PKT_TRADE_SELLEDCARD_BUY_RE);
	};
};
//Server<-Client
struct GS_PKT_TRADE_SHOP_SELL : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// 판매할 인벤토리 슬롯번호
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];	/// 각 슬롯에서 판매할 갯수
	DWORD			dwSlotTotal;						/// 판매할 슬롯의 갯수
	GS_PKT_TRADE_SHOP_SELL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_SELL));
		MPID = _GS_PKT_TRADE_SHOP_SELL;
		Len = sizeof(GS_PKT_TRADE_SHOP_SELL);
	};
};
//Server->Client
struct GS_PKT_TRADE_SHOP_SELL_RE : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];		/// 판매된 인벤토리 슬롯번호
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];		/// 각 슬롯에서 판매할 갯수
	WORD			wSelledSlot[_MAX_INVENTORY_CARD_SIZE];	/// 판매한 카드가 들어갈 재구입리스트 슬롯번호
	DWORD			dwSlotTotal;							/// 판매한 슬롯의 갯수
	int				nGP;									/// 판매후 남은 포인트
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_SHOP_SELL_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_SELL_RE));
		MPID = _GS_PKT_TRADE_SHOP_SELL_RE;
		Len = sizeof(GS_PKT_TRADE_SHOP_SELL_RE);
	};
};
//Client->Server
struct GS_PKT_TRADE_MIX_EXE : PACKET_BASE
{
	GS_PKT_TRADE_MIX_EXE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_EXE));
		MPID = _GS_PKT_TRADE_MIX_EXE;
		Len = sizeof(GS_PKT_TRADE_MIX_EXE);
	};
};
//Client->Server
struct GS_PKT_TRADE_MIX_OPEN : PACKET_BASE
{
	WORD			wResult;							/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_MIX_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_OPEN));
		MPID = _GS_PKT_TRADE_MIX_OPEN;
		Len = sizeof(GS_PKT_TRADE_MIX_OPEN);
	};
};
//Client->Server
struct GS_PKT_TRADE_MIX_CONDITION : PACKET_BASE
{
	int				nMoveKind;	/// enum eTRADE_CARD_MOVE{}; 값중에 하나, 주고 받는 값
	WORD			wOrigSlot;	/// 원래 슬롯, 주고 받는 값
	WORD			wGoalSlot;	/// 목표 슬롯, 주고 받는 값
	CHAR_GAIN_CARD	Card;		/// 대상 카드, 받는 값
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패, 받는값
	GS_PKT_TRADE_MIX_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_CONDITION));
		MPID = _GS_PKT_TRADE_MIX_CONDITION;
		Len = sizeof(GS_PKT_TRADE_MIX_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_MIX_CANCEL : PACKET_BASE
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_MIX];	/// 받는값, 거래카드
	WORD			wSlot[_MAX_TRADE_CARD_MIX];	/// 받는값, 대상슬롯번호
	WORD			wDest[_MAX_TRADE_CARD_MIX];	/// 받는값, eTRADE_CARD_MOVE의 값
	WORD			wResult;					/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_MIX_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_CANCEL));
		MPID = _GS_PKT_TRADE_MIX_CANCEL;
		Len = sizeof(GS_PKT_TRADE_MIX_CANCEL);
	};
};
//Server->Client
struct GS_PKT_TRADE_MIX_RESULT : PACKET_BASE
{
	WORD			wDest;		/// 이동위치[0: 없음, 1:가방, 2:메일함], eTRADE_CARD_MOVE의 값
	WORD			wSlot;		/// 대상슬롯번호
	CHAR_GAIN_CARD	Card;		/// 조합한 카드
	WORD			wResult;	/// 0이면 성공, 받는값
	GS_PKT_TRADE_MIX_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_RESULT));
		MPID = _GS_PKT_TRADE_MIX_RESULT;
		Len = sizeof(GS_PKT_TRADE_MIX_RESULT);
	};
};
//Client->Server
struct GS_PKT_TRADE_PRODUCT_OPEN : PACKET_BASE
{
	WORD			wResult;					/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_PRODUCT_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_OPEN));
		MPID = _GS_PKT_TRADE_PRODUCT_OPEN;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_OPEN);
	};
};
//Client->Server
struct GS_PKT_TRADE_PRODUCT_EXE : PACKET_BASE
{
	DWORD			dwCard;		/// 제작할 카드
	GS_PKT_TRADE_PRODUCT_EXE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_EXE));
		MPID = _GS_PKT_TRADE_PRODUCT_EXE;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_EXE);
	};
};
//Client->Server
struct GS_PKT_TRADE_PRODUCT_CONDITION : PACKET_BASE
{
	int				nMoveKind;	/// enum eTRADE_CARD_MOVE{}; 값중에 하나, 주고 받는 값
	WORD			wOrigSlot;	/// 원래 슬롯, 주고 받는 값
	WORD			wGoalSlot;	/// 목표 슬롯, 주고 받는 값
	CHAR_GAIN_CARD	Card;		/// 대상 카드, 받는 값
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패, 받는값
	GS_PKT_TRADE_PRODUCT_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_CONDITION));
		MPID = _GS_PKT_TRADE_PRODUCT_CONDITION;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PRODUCT_CANCEL : PACKET_BASE
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PRODUCT];	/// 받는값, 재료카드
	WORD			wSlot[_MAX_TRADE_CARD_PRODUCT]; /// 받는값, 대상슬롯번호
	WORD			wDest[_MAX_TRADE_CARD_PRODUCT];	/// 받는값, eTRADE_CARD_MOVE의 값
	WORD			wResult;					/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_PRODUCT_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_CANCEL));
		MPID = _GS_PKT_TRADE_PRODUCT_CANCEL;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_CANCEL);
	};
};
//Server->Client
struct GS_PKT_TRADE_PRODUCT_RESULT : PACKET_BASE
{
	WORD			wDest;		/// 이동위치[0: 없음, 1:가방, 2:메일함], eTRADE_CARD_MOVE의 값
	WORD			wSlot;		/// 대상슬롯번호
	CHAR_GAIN_CARD	Card;		/// 제작한 카드
	int				nGP;		/// 소비되고 남은 포인트
	WORD			wResult;	/// 0이면 성공, 받는값
	GS_PKT_TRADE_PRODUCT_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_RESULT));
		MPID = _GS_PKT_TRADE_PRODUCT_RESULT;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_RESULT);
	};
};
//Client->Server
struct GS_PKT_TRADE_DISSOLVE_OPEN : PACKET_BASE
{
	WORD			wResult;					/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_DISSOLVE_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_OPEN));
		MPID = _GS_PKT_TRADE_DISSOLVE_OPEN;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_OPEN);
	};
};
//Client->Server
struct GS_PKT_TRADE_DISSOLVE_EXE : PACKET_BASE
{
	DWORD			dwCard;		/// 분해할 카드
	GS_PKT_TRADE_DISSOLVE_EXE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_EXE));
		MPID = _GS_PKT_TRADE_DISSOLVE_EXE;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_EXE);
	};
};
//Client->Server
struct GS_PKT_TRADE_DISSOLVE_CONDITION : PACKET_BASE
{
	int				nMoveKind;	/// enum eTRADE_CARD_MOVE{}; 값중에 하나, 주고 받는 값
	WORD			wOrigSlot;	/// 원래 슬롯, 주고 받는 값
	WORD			wGoalSlot;	/// 목표 슬롯, 주고 받는 값
	CHAR_GAIN_CARD	Card;		/// 대상 카드, 받는 값
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패, 받는값
	GS_PKT_TRADE_DISSOLVE_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_CONDITION));
		MPID = _GS_PKT_TRADE_DISSOLVE_CONDITION;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_DISSOLVE_CANCEL : PACKET_BASE
{
	CHAR_GAIN_CARD	Dissolve;	/// 받는값, 분해카드
	WORD			wSlot;		/// 받는값, 대상슬롯번호
	WORD			wDest;		/// 받는값, eTRADE_CARD_MOVE의 값
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_DISSOLVE_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_CANCEL));
		MPID = _GS_PKT_TRADE_DISSOLVE_CANCEL;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_CANCEL);
	};
};
//Server->Client
struct GS_PKT_TRADE_DISSOLVE_RESULT : PACKET_BASE
{
	WORD			wDest[_MAX_TRADE_CARD_DISSOLVE];/// 이동위치[0: 없음, 1:가방, 2:메일함], eTRADE_CARD_MOVE의 값
	WORD			wSlot[_MAX_TRADE_CARD_DISSOLVE];/// 대상슬롯번호
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_DISSOLVE];	/// 제작한 카드
	int				nGP;							/// 소비되고 남은 포인트
	WORD			wResult;						/// 0이면 성공, 받는값
	GS_PKT_TRADE_DISSOLVE_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_RESULT));
		MPID = _GS_PKT_TRADE_DISSOLVE_RESULT;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_RESULT);
	};
};
//Server<-Client
struct GS_PKT_TRADE_BOOSTER_OPEN : PACKET_BASE
{
	WORD			wResult;					/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_BOOSTER_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_OPEN));
		MPID = _GS_PKT_TRADE_BOOSTER_OPEN;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_OPEN);
	};
};
//Server<-Client
struct GS_PKT_TRADE_BOOSTER_CANCEL : PACKET_BASE
{
	WORD			wResult;					/// 0이면 성공, 0이 아니면 실패
	GS_PKT_TRADE_BOOSTER_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_CANCEL));
		MPID = _GS_PKT_TRADE_BOOSTER_CANCEL;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_CANCEL);
	};
};
//Server<->Client
struct GS_PKT_TRADE_BOOSTER_USE : PACKET_BASE
{
	WORD			wSlot;		/// 사용카드의 인벤토리 슬롯번호
	GS_PKT_TRADE_BOOSTER_USE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_USE));
		MPID = _GS_PKT_TRADE_BOOSTER_USE;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_USE);
	};
};
//Server<-Client
struct GS_PKT_TRADE_BOOSTER_VIEW : PACKET_BASE
{
	WORD			wSlot;		/// 사용카드의 인벤토리 슬롯번호
	GS_PKT_TRADE_BOOSTER_VIEW() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_VIEW));
		MPID = _GS_PKT_TRADE_BOOSTER_VIEW;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_VIEW);
	};
};
//Server->Client
struct GS_PKT_TRADE_BOOSTER_VIEW_RE : PACKET_BASE
{
	DWORD			nIdxCard[_MAX_BOOSTER_CARD_SIZE]; /// 8자리 이하이면 자동테이블, 클라이언트에서는 ?표시
	WORD			wResult;	/// 0이면 성공, 아니면 실패
	GS_PKT_TRADE_BOOSTER_VIEW_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_VIEW_RE));
		MPID = _GS_PKT_TRADE_BOOSTER_VIEW_RE;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_VIEW_RE);
	};
};

//Server<->Client
struct GS_PKT_TRADE_BOOSTER_RESULT : PACKET_BASE
{
	WORD			wDest[_MAX_BOOSTER_GAIN_SIZE];	/// 이동위치[0: 없음, 1:가방, 2:메일함], eBOOSTER_DEST의 값
	WORD			wSlot[_MAX_BOOSTER_GAIN_SIZE];	/// 슬롯번호
	WORD			wUsedSlot;						/// 슬롯번호
	CHAR_GAIN_CARD	Card[_MAX_BOOSTER_GAIN_SIZE];	/// 획득한 카드
	WORD			wCount;		/// 획득한 카드의 갯수
	WORD			wResult;	/// 0이면 성공, 0이 아니면 실패, 받는값
	GS_PKT_TRADE_BOOSTER_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_RESULT));
		MPID = _GS_PKT_TRADE_BOOSTER_RESULT;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_RESULT);
	};
};
//Server<->Client
struct GS_PKT_1V1_INVITE : PACKET_BASE
{
	GS_PKT_1V1_INVITE()	{
		ZeroMemory(this,sizeof(GS_PKT_1V1_INVITE));
		MPID = _GS_PKT_1V1_INVITE;
		Len = sizeof(GS_PKT_1V1_INVITE);
	}
	WORD	wSid;		//신청 대상자 번호
};

struct GS_PKT_1V1_CANCEL : PACKET_BASE
{
	GS_PKT_1V1_CANCEL()
	{
		ZeroMemory(this,sizeof(GS_PKT_1V1_CANCEL));
		MPID = _GS_PKT_1V1_CANCEL;
		Len = sizeof(GS_PKT_1V1_CANCEL);
	}
	WORD   wSid;
};

struct GS_PKT_1V1_CANCEL_RE : PACKET_BASE
{
	GS_PKT_1V1_CANCEL_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_1V1_CANCEL_RE));
		MPID = _GS_PKT_1V1_CANCEL_RE;
		Len = sizeof(GS_PKT_1V1_CANCEL_RE);
	}
};

struct GS_PKT_1V1_INVITE_RE : PACKET_BASE
{
	GS_PKT_1V1_INVITE_RE()	{
		ZeroMemory(this,sizeof(GS_PKT_1V1_INVITE_RE));
		MPID = _GS_PKT_1V1_INVITE_RE;
		Len = sizeof(GS_PKT_1V1_INVITE_RE);
	}
	WORD	wSid;
};

struct GS_PKT_1V1_RESULT : PACKET_BASE
{
	GS_PKT_1V1_RESULT()	{
		ZeroMemory(this,sizeof(GS_PKT_1V1_RESULT));
		MPID = _GS_PKT_1V1_RESULT;
		Len = sizeof(GS_PKT_1V1_RESULT);
	}
	WORD	wSid;
	WORD	bRet;
};

struct GS_PKT_1V1_RESULT_RE : PACKET_BASE
{
	GS_PKT_1V1_RESULT_RE()	{
		ZeroMemory(this,sizeof(GS_PKT_1V1_RESULT_RE));
		MPID = _GS_PKT_1V1_RESULT_RE;
		Len = sizeof(GS_PKT_1V1_RESULT_RE);
	}
	WORD bRet;
	WORD EmemywSid;
};

struct  CREATE_ROOM_INFO
{
	CREATE_ROOM_INFO()
	{
		ZeroMemory(this,sizeof(CREATE_ROOM_INFO));
	}
	DWORD	idx;				/// 고유번호
	DWORD	mapIdx;				/// 월드번호
	WORD	MaxCnt;				/// 최대인원
	WORD	CurrCnt;			/// 현재인원
	WORD	RoomLeaderIdx;		/// 방장 캐릭터 번호
	WORD	GameRule;			/// 게임룰: 덱전, 체력전
	WORD	LevelLimit;			/// 레벨제한
	WORD	State;				/// 대기중, 게임중
	DWORD	Password;			/// 0:공개방, 1: 비번방
	DWORD	Type;				/// PVP=0 PVE=1
	DWORD	BattleSessionID;	/// Monster File DB ID
	WCHAR	Name[MAX_ROOM_NAME];/// 
};
//Server<-Client
struct GS_PKT_CREATEROOM : PACKET_BASE
{
	GS_PKT_CREATEROOM()	
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATEROOM));
		MPID = _GS_PKT_CREATEROOM;
		Len = sizeof(GS_PKT_CREATEROOM);
	}
//	WORD	ChannelSN;				/// 메인채널번호(안쓰임)
//	WORD	SubChannelSN;			/// 보조채널번호(안쓰임)
	WORD	MaxCnt;					/// 인원제한
	WORD	LevelLimit;				/// 레벨제한
	WORD	GameRule;				/// 게임방식:체력전,덱전
	DWORD	MapIdx;					/// 전투맵
	WCHAR	Passwd[MAX_ROOM_PASSWD];/// 비번
	WCHAR	Name[MAX_ROOM_NAME];	/// 방명
};
//Serve->Client
struct GS_PKT_CREATEROOM_RE : PACKET_BASE
{
	GS_PKT_CREATEROOM_RE()	{
		ZeroMemory(this,sizeof(GS_PKT_CREATEROOM_RE));
		MPID = _GS_PKT_CREATEROOM_RE;
		Len = sizeof(GS_PKT_CREATEROOM_RE);
	}
	CREATE_ROOM_INFO	RoomData;
	DWORD				Result;
//	GS_INROOM_USERDATA CreateUserData;
};
//Server<-Client
struct GS_PKT_ROOM_LIST : PACKET_BASE
{
	GS_PKT_ROOM_LIST()	{
		ZeroMemory(this,sizeof(GS_PKT_ROOM_LIST));
		MPID = _GS_PKT_ROOM_LIST;
		Len = sizeof(GS_PKT_ROOM_LIST);
	}
};
//Serve->Client
struct GS_PKT_ROOM_LIST_RE : PACKET_BASE
{
	GS_PKT_ROOM_LIST_RE()	{
		ZeroMemory(this,sizeof(GS_PKT_ROOM_LIST_RE));
		MPID = _GS_PKT_ROOM_LIST_RE;
		Len = sizeof(GS_PKT_ROOM_LIST_RE);
	}
	int Total;	// 전체 갯수
	int Page;   // 0이면 다 받았음
	int Count;	// 전송된 갯수
	CREATE_ROOM_INFO RoomList[MAX_ROOM_LIST];
};
//Server<-Client
struct GS_PKT_OBSERVER_LIST : PACKET_BASE
{
	int nRoomIdx;
	GS_PKT_OBSERVER_LIST() {
		memset(this, 0x00, sizeof(GS_PKT_OBSERVER_LIST));
		MPID = _GS_PKT_OBSERVER_LIST;
		Len = sizeof(GS_PKT_OBSERVER_LIST);
	};
};
//Server->Client
struct GS_PKT_OBSERVER_LIST_RE : PACKET_BASE
{
	WORD		wCount;						/// 보낸 관전자의 갯수
	WORD		wOffset;					/// 읽는 단위
	char		pData[_MAX_DEFINED_DATA];	/// 캐릭터명들
	GS_PKT_OBSERVER_LIST_RE() {
		memset(this, 0x00, sizeof(GS_PKT_OBSERVER_LIST_RE));
		MPID = _GS_PKT_OBSERVER_LIST_RE;
		Len = sizeof(GS_PKT_OBSERVER_LIST_RE);
	};
};

struct GS_INROOM_USERDATA
{
	GS_INROOM_USERDATA()
	{
		ZeroMemory(this,sizeof(GS_INROOM_USERDATA));
	}

	WORD		wSid;
	BYTE		SeatNumber;	/// 좌석번호
	BYTE		Type;		/// 입장 타입 0.플레이어 1.옵져버
	BYTE		DeckType;			
	BYTE		IsReady;	/// TRUE 준비완료 FALSE 대기중
	BYTE		PartyIdx;	/// 팀번호
	BYTE		Dummy;
	CHAR_DATA	Character;	/// 캐릭터 데이타
};

struct GS_PKT_ENTERROOM : PACKET_BASE
{
	GS_PKT_ENTERROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_ENTERROOM));
		MPID = _GS_PKT_ENTERROOM;
		Len = sizeof(GS_PKT_ENTERROOM);
	}
	DWORD	RoomIdx;
	WCHAR	Passwd[MAX_ROOM_PASSWD];
};

struct GS_PKT_ENTERROOM_RE  : PACKET_BASE
{
	GS_PKT_ENTERROOM_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_ENTERROOM_RE));
		MPID = _GS_PKT_ENTERROOM_RE;
		Len = sizeof(GS_PKT_ENTERROOM_RE);
	}
	DWORD				Result;
	CREATE_ROOM_INFO	RoomInfo;
	GS_INROOM_USERDATA	PlayerList[MAX_PLAYER_INROOM];
};

struct GS_PKT_OBSERVER_ENTERROOM : PACKET_BASE
{
	GS_PKT_OBSERVER_ENTERROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_OBSERVER_ENTERROOM));
		MPID = _GS_PKT_OBSERVER_ENTERROOM;
		Len = sizeof(GS_PKT_OBSERVER_ENTERROOM);
	}
	DWORD	RoomIdx;
	WCHAR	Passwd[MAX_ROOM_PASSWD];
};

struct GS_PKT_OBSERVER_ENTERROOM_RE : PACKET_BASE
{
	GS_PKT_OBSERVER_ENTERROOM_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_OBSERVER_ENTERROOM_RE));
		MPID = _GS_PKT_OBSERVER_ENTERROOM_RE;
		Len = sizeof(GS_PKT_OBSERVER_ENTERROOM_RE);
	}
	DWORD Result;
	CREATE_ROOM_INFO	 RoomInfo;
	GS_INROOM_USERDATA	 PlayerList[MAX_PLAYER_INROOM];
};
/*
	_GS_PKT_OBSERVER_LEAVEROOM,
	_GS_PKT_OBSERVER_LEAVEROOM_RE
*/
struct GS_PKT_NEWUSER_INROOM : PACKET_BASE
{
	GS_PKT_NEWUSER_INROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_NEWUSER_INROOM));
		MPID = _GS_PKT_NEWUSER_INROOM;
		Len = sizeof(GS_PKT_NEWUSER_INROOM);
	}
	GS_INROOM_USERDATA	PlayerInfo;
};
//Serve->Client
struct GS_PKT_ADDROOM : PACKET_BASE
{
	GS_PKT_ADDROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_ADDROOM));
		MPID = _GS_PKT_ADDROOM;
		Len = sizeof(GS_PKT_ADDROOM);
	}
	CREATE_ROOM_INFO	Room;
};
//Serve->Client
struct GS_PKT_DELROOM : PACKET_BASE
{
	GS_PKT_DELROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_DELROOM));
		MPID = _GS_PKT_DELROOM;
		Len = sizeof(GS_PKT_DELROOM);
	}
	DWORD	dwRoomIdx;	///  방번호
};
//Serve<->Client
struct GS_PKT_CHG_PLAYER_SLOT : PACKET_BASE
{
	GS_PKT_CHG_PLAYER_SLOT()
	{
		ZeroMemory(this,sizeof(GS_PKT_CHG_PLAYER_SLOT));
		MPID = _GS_PKT_CHG_PLAYER_SLOT;
		Len = sizeof(GS_PKT_CHG_PLAYER_SLOT);
	}
	WORD wSid;					/// 유저 고유번호
	WORD wTeam;					/// 팀  번호( 0:팀, 1:팀, 2:관전자 )
	WORD wSeat;					/// 좌석번호(0,1,2...)
	WORD wResult;				/// 0이면 성공
};
//Serve<->Client
struct GS_PKT_CHG_PLAYER_DECK : PACKET_BASE
{
	GS_PKT_CHG_PLAYER_DECK()
	{
		ZeroMemory(this,sizeof(GS_PKT_CHG_PLAYER_DECK));
		MPID = _GS_PKT_CHG_PLAYER_DECK;
		Len = sizeof(GS_PKT_CHG_PLAYER_DECK);
	}
	WORD	wDeckIdx;			/// 덱 인덱스:0~5
	WCHAR	szDeckName[10];		/// 덱 이름
};

//Serve<->Client
struct GS_PKT_CHG_PLAYER_DECK_RE : PACKET_BASE
{
	GS_PKT_CHG_PLAYER_DECK_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_CHG_PLAYER_DECK_RE));
		MPID = _GS_PKT_CHG_PLAYER_DECK_RE;
		Len = sizeof(GS_PKT_CHG_PLAYER_DECK_RE);
	}
	WORD	Result;
	WORD	wDeckIdx;			/// 덱 인덱스:0~5
	DWORD	wSid;				/// 유저 고유번호
	WCHAR	szDeckName[10];		/// 덱 이름

};
//Serve<->Client
struct GS_PKT_CHG_PLAYER_READY : PACKET_BASE
{
	GS_PKT_CHG_PLAYER_READY()
	{
		ZeroMemory(this,sizeof(GS_PKT_CHG_PLAYER_READY));
		MPID = _GS_PKT_CHG_PLAYER_READY;
		Len = sizeof(GS_PKT_CHG_PLAYER_READY);
	}
	WORD wSid;					/// 유저 고유번호
	WORD wState;				/// 0:준비아닌 상태, 1:준비된 상태
};

struct GS_PKT_ROOM_INVITE : PACKET_BASE
{
	GS_PKT_ROOM_INVITE()
	{
		ZeroMemory(this, sizeof(GS_PKT_ROOM_INVITE));
		MPID = _GS_PKT_ROOM_INVITE;
		Len = sizeof(GS_PKT_ROOM_INVITE);
	}
	WORD	wRoomreader;	/// 방장 고유번호
	int		nRoomIdx;		/// 방 고유번호
};

struct GS_PKT_ROOM_INVITE_REJECT : PACKET_BASE
{
	GS_PKT_ROOM_INVITE_REJECT()
	{
		ZeroMemory(this, sizeof(GS_PKT_ROOM_INVITE_REJECT));
		MPID = _GS_PKT_ROOM_INVITE_REJECT;
		Len = sizeof(GS_PKT_ROOM_INVITE_REJECT);
	}
	WORD	wRoomreader;	/// 방장 고유번호
	int		nRoomIdx;		/// 방 고유번호
};

struct GS_PKT_ROOM_DEPORTATION : PACKET_BASE
{
	GS_PKT_ROOM_DEPORTATION()
	{
		ZeroMemory(this,sizeof(GS_PKT_ROOM_DEPORTATION));
		MPID = _GS_PKT_ROOM_DEPORTATION;
		Len = sizeof(GS_PKT_ROOM_DEPORTATION);
	}
	WORD wSid;
};

struct GS_PKT_MODIFYROOM : PACKET_BASE
{
	GS_PKT_MODIFYROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_MODIFYROOM));
		MPID = _GS_PKT_MODIFYROOM;
		Len = sizeof(GS_PKT_MODIFYROOM);
	}
	DWORD				Flag;						/// 변경 플래그(eROOM_MODIFY_FLAG의 값)
	CREATE_ROOM_INFO	Room;						/// 변경 값
	WCHAR				Passwd[MAX_ROOM_PASSWD];	/// 방 비번, 비번 변경,기입할 경우만 주는값
};

struct GS_PKT_START_GAME : PACKET_BASE
{
	GS_PKT_START_GAME()
	{
		ZeroMemory(this,sizeof(GS_PKT_START_GAME));
		MPID = _GS_PKT_START_GAME;
		Len = sizeof(GS_PKT_START_GAME);
	}
};

struct GS_PKT_START_GAME_RE : PACKET_BASE
{
	GS_PKT_START_GAME_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_START_GAME_RE));
		MPID = _GS_PKT_START_GAME_RE;
		Len = sizeof(GS_PKT_START_GAME_RE);
	}
	WORD bRet;
};

struct GS_PKT_LEAVEROOM : PACKET_BASE
{
	GS_PKT_LEAVEROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_LEAVEROOM));
		MPID = _GS_PKT_LEAVEROOM;
		Len = sizeof(GS_PKT_LEAVEROOM);
	}
};

struct GS_PKT_LEAVEROOM_RE : PACKET_BASE
{
	GS_PKT_LEAVEROOM_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_LEAVEROOM_RE));
		MPID = _GS_PKT_LEAVEROOM_RE;
		Len = sizeof(GS_PKT_LEAVEROOM_RE);
	}
	WORD Result;
	WORD SeatNumber;
	WORD wSid;
};

struct GS_PKT_OBSERVER_LEAVEROOM : PACKET_BASE
{
	GS_PKT_OBSERVER_LEAVEROOM()
	{
		ZeroMemory(this,sizeof(GS_PKT_OBSERVER_LEAVEROOM));
		MPID = _GS_PKT_OBSERVER_LEAVEROOM;
		Len = sizeof(GS_PKT_OBSERVER_LEAVEROOM);
	}
};

struct GS_PKT_OBSERVER_LEAVEROOM_RE : PACKET_BASE
{
	GS_PKT_OBSERVER_LEAVEROOM_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_OBSERVER_LEAVEROOM_RE));
		MPID = _GS_PKT_OBSERVER_LEAVEROOM_RE;
		Len = sizeof(GS_PKT_OBSERVER_LEAVEROOM_RE);
	}
	WORD Result;
	WORD wSid;
};

struct CARD_ID_INFO
{
	DWORD FILE_DB_ID;
	DWORD  DeckIndex;
};

struct GS_PKT_HANDCARD_LIST : PACKET_BASE
{
	GS_PKT_HANDCARD_LIST()
	{
		ZeroMemory(this,sizeof(GS_PKT_HANDCARD_LIST));
		MPID = _GS_PKT_HANDCARD_LIST;
		Len = sizeof(GS_PKT_HANDCARD_LIST);
	}
	CARD_ID_INFO	HandCardList[6];
	DWORD			Result;
};

struct GS_PKT_NATURE_ATTRIBUTE : PACKET_BASE
{
	GS_PKT_NATURE_ATTRIBUTE()
	{
		ZeroMemory(this,sizeof(GS_PKT_NATURE_ATTRIBUTE));
		MPID = _GS_PKT_NATURE_ATTRIBUTE;
		Len = sizeof(GS_PKT_NATURE_ATTRIBUTE);
	}

	int	FireQuantity;
	int WaterQuantity;
	int EarthQuantity;
	int WindQuantity;
	int LightQuantity;
	int DarkQuantity;
	int TotalQuantity;
	int DeckCnt;
	int GraveCnt;
};

struct GS_PKT_OTHERPLAYER_INFO : PACKET_BASE
{
	GS_PKT_OTHERPLAYER_INFO()
	{
		ZeroMemory(this,sizeof(GS_PKT_OTHERPLAYER_INFO));
		MPID = _GS_PKT_OTHERPLAYER_INFO;
		Len = sizeof(GS_PKT_OTHERPLAYER_INFO);
	}
	WORD wSid;
	BYTE DeckCnt;
	BYTE GraveCnt;
};

struct GS_PKT_USR_MP_UPDATE : PACKET_BASE
{
	GS_PKT_USR_MP_UPDATE()
	{
		ZeroMemory(this,sizeof(GS_PKT_USR_MP_UPDATE));
		MPID = _GS_PKT_USR_MP_UPDATE;
		Len = sizeof(GS_PKT_USR_MP_UPDATE);
	}
	WORD wSid;
	WORD MP;
};

struct GS_PKT_USR_HP_UPDATE : PACKET_BASE
{
	GS_PKT_USR_HP_UPDATE()
	{
		ZeroMemory(this,sizeof(GS_PKT_USR_HP_UPDATE));
		MPID = _GS_PKT_USR_HP_UPDATE;
		Len = sizeof(GS_PKT_USR_HP_UPDATE);
	}
	WORD wSid;
	WORD HP;
};

struct GS_PKT_CREATURE_EP_UPDATE : PACKET_BASE
{
	GS_PKT_CREATURE_EP_UPDATE()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_EP_UPDATE));
		MPID = _GS_PKT_CREATURE_EP_UPDATE;
		Len = sizeof(GS_PKT_CREATURE_EP_UPDATE);
	}
	WORD wSid;
	WORD FieldSlotIdx;
	WORD EP;
};

struct GS_PKT_NEW_LEADER : PACKET_BASE
{
	GS_PKT_NEW_LEADER()
	{
		ZeroMemory(this,sizeof(GS_PKT_NEW_LEADER));
		MPID = _GS_PKT_NEW_LEADER;
		Len = sizeof(GS_PKT_NEW_LEADER);
	}
	WORD SeatIdx;
	WORD wSid;
};
	
struct GS_PKT_CREATURE_DEAD : PACKET_BASE
{
	GS_PKT_CREATURE_DEAD()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_DEAD));
		MPID = _GS_PKT_CREATURE_DEAD;
		Len = sizeof(GS_PKT_CREATURE_DEAD);
	}
	WORD wSid;
	WORD FieldSlotIdx;
	WORD Result;
};

struct GS_PKT_CREATURE_HP_UPDATE : PACKET_BASE
{
	GS_PKT_CREATURE_HP_UPDATE()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_HP_UPDATE));
		MPID = _GS_PKT_CREATURE_HP_UPDATE;
		Len = sizeof(GS_PKT_CREATURE_HP_UPDATE);
	}
	WORD wSid;
	WORD FieldSlotIdx;
	WORD HP;
};

struct GS_PKT_COUNTERBLOW : PACKET_BASE
{
	GS_PKT_COUNTERBLOW()
	{
		ZeroMemory(this,sizeof(GS_PKT_COUNTERBLOW));
		MPID = _GS_PKT_COUNTERBLOW;
		Len = sizeof(GS_PKT_COUNTERBLOW);
	}
	WORD AttackwSid;
	WORD AttackFieldSlotIdx;
	WORD TargetwSid;
	WORD TargetFieldSlotIdx;
	WORD Dmg;
};

struct GS_PKT_UPDATE_GRAVE_CNT : PACKET_BASE
{
	GS_PKT_UPDATE_GRAVE_CNT()
	{
		ZeroMemory(this,sizeof(GS_PKT_UPDATE_GRAVE_CNT));
		MPID = _GS_PKT_UPDATE_GRAVE_CNT;
		Len = sizeof(GS_PKT_UPDATE_GRAVE_CNT);
	}
	WORD wSid;
	WORD Cnt;
};

struct GS_PKT_UPDATE_DECK_CNT : PACKET_BASE
{
	GS_PKT_UPDATE_DECK_CNT()
	{
		ZeroMemory(this,sizeof(GS_PKT_UPDATE_DECK_CNT));
		MPID = _GS_PKT_UPDATE_DECK_CNT;
		Len = sizeof(GS_PKT_UPDATE_DECK_CNT);
	}
	WORD wSid;
	WORD Cnt;
};

struct GS_PKT_NEW_HANDCARD : PACKET_BASE
{
	GS_PKT_NEW_HANDCARD()
	{
		ZeroMemory(this,sizeof(GS_PKT_NEW_HANDCARD));
		MPID = _GS_PKT_NEW_HANDCARD;
		Len = sizeof(GS_PKT_NEW_HANDCARD);
	}
	DWORD FileDBIdx;
	WORD  DeckIndex;
	WORD  HandSlotIdx;
};

struct GS_PKT_HANDCARD_USE : PACKET_BASE
{
	GS_PKT_HANDCARD_USE()
	{
		ZeroMemory(this,sizeof(GS_PKT_HANDCARD_USE));
		MPID = _GS_PKT_HANDCARD_USE;
		Len = sizeof(GS_PKT_HANDCARD_USE);
		for(int i=0;i<MAX_TARGET_LIST;i++) FieldSlotIdx[i] = SCHAR_MAX;
	}

	BYTE DeckIndex;
	BYTE Dummy;
	WORD TargetwSid;
	BYTE FieldSlotIdx[MAX_TARGET_LIST];
};

struct GS_PKT_CREATURE_SUMMON : PACKET_BASE
{
	GS_PKT_CREATURE_SUMMON()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_SUMMON));
		MPID = _GS_PKT_CREATURE_SUMMON;
		Len = sizeof(GS_PKT_CREATURE_SUMMON);
	}
	WORD Result;
	WORD wSid;
	DWORD FILE_DB_ID;
	WORD FieldSlotIdx;
	WORD DeckIndex;
};

struct GS_PKT_GAMEOVER : PACKET_BASE
{
	GS_PKT_GAMEOVER()
	{
		ZeroMemory(this,sizeof(GS_PKT_GAMEOVER));
		MPID = _GS_PKT_GAMEOVER;
		Len = sizeof(GS_PKT_GAMEOVER);
	}
	WORD Result;
};

struct GS_PKT_ALIVE : PACKET_BASE
{
	GS_PKT_ALIVE()
	{
		ZeroMemory(this,sizeof(GS_PKT_ALIVE));
		MPID = _GS_PKT_ALIVE;
		Len = sizeof(GS_PKT_ALIVE);
	}
};


struct GS_PKT_CREATURE_MOVE : PACKET_BASE
{
	GS_PKT_CREATURE_MOVE()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_MOVE));
		MPID = _GS_PKT_CREATURE_MOVE;
		Len = sizeof(GS_PKT_CREATURE_MOVE);
	}

	BYTE SrcSlotIdx;
	BYTE DstSlotIdx;
};

struct GS_PKT_CREATURE_MOVE_RE : PACKET_BASE
{
	GS_PKT_CREATURE_MOVE_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_MOVE_RE));
		MPID = _GS_PKT_CREATURE_MOVE_RE;
		Len = sizeof(GS_PKT_CREATURE_MOVE_RE);
	}
	WORD		     Result;
	WORD wSid;
	BYTE SrcSlotIdx;
	BYTE DstSlotIdx;
};

struct GS_PKT_GRAVE : PACKET_BASE
{
	GS_PKT_GRAVE()
	{
		ZeroMemory(this,sizeof(GS_PKT_GRAVE));
		MPID = _GS_PKT_GRAVE;
		Len = sizeof(GS_PKT_GRAVE);
	}

	WORD SlotIdx;
};

struct GS_PKT_GRAVE_RE : PACKET_BASE
{
	GS_PKT_GRAVE_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_GRAVE_RE));
		MPID = _GS_PKT_GRAVE_RE;
		Len = sizeof(GS_PKT_GRAVE_RE);
	}
	WORD wSid;
	WORD SlotIdx;
};

struct GS_PKT_SKILL_ATTACK : PACKET_BASE
{
	GS_PKT_SKILL_ATTACK()
	{
		ZeroMemory(this,sizeof(GS_PKT_SKILL_ATTACK));
		MPID = _GS_PKT_SKILL_ATTACK;
		Len = sizeof(GS_PKT_SKILL_ATTACK);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetSlotIdx[i] = SCHAR_MAX;
	}
	BYTE SlotIdx;				//공격자 슬롯 번호
	BYTE Dummy;
	WORD TargetwSid;			//타겟 유저번호
	BYTE TargetSlotIdx[MAX_TARGET_LIST];		//타겟 리스트  순서대로 들어가며 타겟이 없을경우 -1(127)를 넣어준다.
};

struct GS_PKT_SKILL_ATTACK_RE : PACKET_BASE
{
	GS_PKT_SKILL_ATTACK_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_SKILL_ATTACK_RE));
		MPID = _GS_PKT_SKILL_ATTACK_RE;
		Len = sizeof(GS_PKT_SKILL_ATTACK_RE);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetSlotIdx[i] = SCHAR_MAX;
	}
	WORD		     Result;
	WORD			 AttackerwSid;
	WORD			 AttackerSlotIdx;
	WORD			 TargetwSid;
	WORD			 TargetSlotIdx[MAX_TARGET_LIST];
	DWORD			 SkillSN;
};

struct STATS_DATA
{
	STATS_DATA()
	{
		ZeroMemory(this,sizeof(STATS_DATA));
	}
	int m_CurrMP;
	int m_MaxMP;
	int m_CurrHP;
	int m_MaxHP;
	int m_AP;
	int m_DP;
	int m_CurrEP;
	int m_MaxEP;
	int m_QP;
	int m_CP;
	int m_CR;

	int m_StatusMore;		//상태이상

};

struct GS_PKT_UPDATE_USER_STATS : PACKET_BASE
{
	GS_PKT_UPDATE_USER_STATS()
	{
		ZeroMemory(this,sizeof(GS_PKT_UPDATE_USER_STATS));
		MPID = _GS_PKT_UPDATE_USER_STATS;
		Len = sizeof(GS_PKT_UPDATE_USER_STATS);
	}
	WORD       wSid;
	WORD	   Dummy;
	DWORD	   SkillSN;
	STATS_DATA data;
};

struct GS_PKT_UPDATE_CREATURE_STATS : PACKET_BASE
{
	GS_PKT_UPDATE_CREATURE_STATS()
	{
		ZeroMemory(this,sizeof(GS_PKT_UPDATE_USER_STATS));
		MPID = _GS_PKT_UPDATE_CREATURE_STATS;
		Len = sizeof(GS_PKT_UPDATE_CREATURE_STATS);
	}
	WORD       TargetwSid;
	WORD	   TargetSlotIdx;

	WORD       AttackerwSid;
	WORD	   AttackerSlotIdx;

	DWORD	   SkillSN;
	
	STATS_DATA data;
};
	
struct GS_PKT_RESOURCE_COMPLETE : PACKET_BASE
{
	GS_PKT_RESOURCE_COMPLETE()
	{
		ZeroMemory(this,sizeof(GS_PKT_RESOURCE_COMPLETE));
		MPID = _GS_PKT_RESOURCE_COMPLETE;
		Len = sizeof(GS_PKT_RESOURCE_COMPLETE);
	}
};

struct GS_PKT_RESOURCE_COMPLETE_RE : PACKET_BASE
{
	GS_PKT_RESOURCE_COMPLETE_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_RESOURCE_COMPLETE_RE));
		MPID = _GS_PKT_RESOURCE_COMPLETE_RE;
		Len = sizeof(GS_PKT_RESOURCE_COMPLETE_RE);
	}
	WORD       wSid;
};

struct GS_PKT_RESOURCE_ALL_COMPLETE : PACKET_BASE
{
	GS_PKT_RESOURCE_ALL_COMPLETE()
	{
		ZeroMemory(this,sizeof(GS_PKT_RESOURCE_ALL_COMPLETE));
		MPID = _GS_PKT_RESOURCE_ALL_COMPLETE;
		Len = sizeof(GS_PKT_RESOURCE_ALL_COMPLETE);
	}
};

struct GS_PKT_SCENE_COMPLETE : PACKET_BASE
{
	GS_PKT_SCENE_COMPLETE()
	{
		ZeroMemory(this,sizeof(GS_PKT_SCENE_COMPLETE));
		MPID = _GS_PKT_SCENE_COMPLETE;
		Len = sizeof(GS_PKT_SCENE_COMPLETE);
	}
};
struct GS_PKT_SCENE_COMPLETE_RE : PACKET_BASE
{
	GS_PKT_SCENE_COMPLETE_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_SCENE_COMPLETE_RE));
		MPID = _GS_PKT_SCENE_COMPLETE_RE;
		Len = sizeof(GS_PKT_SCENE_COMPLETE_RE);
	}
	WORD       wSid;
};
struct GS_PKT_SCENE_ALL_COMPLETE : PACKET_BASE
{
	GS_PKT_SCENE_ALL_COMPLETE()
	{
		ZeroMemory(this,sizeof(GS_PKT_SCENE_ALL_COMPLETE));
		MPID = _GS_PKT_SCENE_ALL_COMPLETE;
		Len = sizeof(GS_PKT_SCENE_ALL_COMPLETE);
	}
};
struct GS_PKT_REQ_SELECT_DECKCARD : PACKET_BASE
{
	GS_PKT_REQ_SELECT_DECKCARD()
	{
		ZeroMemory(this,sizeof(GS_PKT_REQ_SELECT_DECKCARD));
		MPID = _GS_PKT_REQ_SELECT_DECKCARD;
		Len = sizeof(GS_PKT_REQ_SELECT_DECKCARD);
	}

	WORD       wSid;

};
struct GS_PKT_REQ_SELECT_DECKCARD_RE : PACKET_BASE
{
	GS_PKT_REQ_SELECT_DECKCARD_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_REQ_SELECT_DECKCARD_RE));
		MPID = _GS_PKT_REQ_SELECT_DECKCARD_RE;
		Len = sizeof(GS_PKT_REQ_SELECT_DECKCARD_RE);
	}
	WORD    wSid;
	BYTE	SelectedDeckIdx;
	CHAR_GAIN_CARD	CardList[50];
};

struct GS_PKT_DMG : PACKET_BASE
{
	GS_PKT_DMG()
	{
		ZeroMemory(this,sizeof(GS_PKT_DMG));
		MPID = _GS_PKT_DMG;
		Len = sizeof(GS_PKT_DMG);
	}
	WORD wSid;
	BYTE FieldSlotIdx;
	int Dmg;
	BYTE IsCritical;
	WORD IsCounterBlow;
};

struct GS_PKT_PROVOCATION : PACKET_BASE
{
	GS_PKT_PROVOCATION()
	{
		ZeroMemory(this,sizeof(GS_PKT_PROVOCATION));
		MPID = _GS_PKT_PROVOCATION;
		Len  = sizeof(GS_PKT_PROVOCATION);
	}

	WORD FieldSlotIdx;
};

struct GS_PKT_PROVOCATION_RE : PACKET_BASE
{
	GS_PKT_PROVOCATION_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_PROVOCATION_RE));
		MPID = _GS_PKT_PROVOCATION_RE;
		Len  = sizeof(GS_PKT_PROVOCATION_RE);
		FROM = _FROM_SERVER;
	}
	WORD Result;
	WORD wSid;
	WORD FieldSlotIdx;
	WORD Activate;		// 1 : 활성화 0 : 비활성화
};

struct GS_PKT_CREATURE_SKILL: PACKET_BASE
{
	GS_PKT_CREATURE_SKILL()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_SKILL));
		MPID = _GS_PKT_CREATURE_SKILL;
		Len = sizeof(GS_PKT_CREATURE_SKILL);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetSlotIdx[i] = SCHAR_MAX;
	}
	WORD			 AttackerwSid;
	WORD			 AttackerSlotIdx;
	WORD			 TargetwSid;
	WORD			 TargetSlotIdx[MAX_TARGET_LIST];
};

struct GS_PKT_CREATURE_SKILL_RE: PACKET_BASE
{
	GS_PKT_CREATURE_SKILL_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_CREATURE_SKILL_RE));
		MPID = _GS_PKT_CREATURE_SKILL_RE;
		Len = sizeof(GS_PKT_CREATURE_SKILL_RE);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetSlotIdx[i] = SCHAR_MAX;
	}
	WORD		     Result;
	WORD			 AttackerwSid;
	WORD			 AttackerSlotIdx;
	WORD			 TargetwSid;
	WORD			 TargetSlotIdx[MAX_TARGET_LIST];
	DWORD			 SkillSN;
};

struct GS_PKT_SHUFFLE : PACKET_BASE
{
	GS_PKT_SHUFFLE()
	{
		ZeroMemory(this,sizeof(GS_PKT_SHUFFLE));
		MPID = _GS_PKT_SHUFFLE;
		Len = sizeof(GS_PKT_SHUFFLE);
	};
};

struct GS_PKT_SHUFFLE_RE : PACKET_BASE
{
	GS_PKT_SHUFFLE_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_SHUFFLE_RE));
		MPID = _GS_PKT_SHUFFLE_RE;
		Len = sizeof(GS_PKT_SHUFFLE_RE);
	};
	CARD_ID_INFO	HandCardList[6];
};

struct GS_PKT_KILL_CREATURE  : PACKET_BASE
{
	GS_PKT_KILL_CREATURE()
	{
		ZeroMemory(this,sizeof(GS_PKT_KILL_CREATURE));
		MPID = _GS_PKT_KILL_CREATURE;
		Len = sizeof(GS_PKT_KILL_CREATURE);
	}
	WORD FieldSlotIdx;
};

struct GS_PKT_MAGICCARD_USE : PACKET_BASE
{
	GS_PKT_MAGICCARD_USE()
	{
		ZeroMemory(this,sizeof(GS_PKT_MAGICCARD_USE));
		MPID = _GS_PKT_MAGICCARD_USE;
		Len = sizeof(GS_PKT_MAGICCARD_USE);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetFieldSlotIdx[i] = SCHAR_MAX;
	}
	WORD AttackerwSid;
	WORD TargetwSid;
	BYTE TargetFieldSlotIdx[MAX_TARGET_LIST];
	BYTE DeckIndex;
	WORD Result;

};

struct GS_PKT_ENHANCECARD_USE : PACKET_BASE
{
	GS_PKT_ENHANCECARD_USE()
	{
		ZeroMemory(this,sizeof(GS_PKT_ENHANCECARD_USE));
		MPID = _GS_PKT_ENHANCECARD_USE;
		Len = sizeof(GS_PKT_ENHANCECARD_USE);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetFieldSlotIdx[i] = SCHAR_MAX;
	}
	WORD AttackerwSid;
	WORD TargetwSid;
	BYTE TargetFieldSlotIdx[MAX_TARGET_LIST];
	BYTE DeckIndex;
	WORD Result;
};

struct GS_PKT_EQUIPCARD_USE : PACKET_BASE
{
	GS_PKT_EQUIPCARD_USE()
	{
		ZeroMemory(this,sizeof(GS_PKT_EQUIPCARD_USE));
		MPID = _GS_PKT_EQUIPCARD_USE;
		Len = sizeof(GS_PKT_EQUIPCARD_USE);
		for(int i=0;i<MAX_TARGET_LIST;i++) TargetFieldSlotIdx[i] = SCHAR_MAX;
	}
	WORD AttackerwSid;
	WORD TargetwSid;
	DWORD FileDBID;
	WORD Result;
	BYTE TargetFieldSlotIdx[MAX_TARGET_LIST];
};

struct GS_PKT_DEL_CARD_RE : PACKET_BASE
{
	GS_PKT_DEL_CARD_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_DEL_CARD_RE));
		MPID = _GS_PKT_DEL_CARD_RE;
		Len = sizeof(GS_PKT_DEL_CARD_RE);
	}
	WORD wSid;				
	WORD DeckIndex;
	WORD Result;
};

struct GS_PKT_ATTACK : PACKET_BASE
{
	GS_PKT_ATTACK()
	{
		ZeroMemory(this,sizeof(GS_PKT_ATTACK));
		MPID = _GS_PKT_ATTACK;	
		Len = sizeof(GS_PKT_ATTACK);
	} 
	WORD AttackerwSid;
	WORD AttackFieldSlot; 
	WORD TargetwSid;
	WORD TargetFieldSlotIdx;    	
};

struct GS_PKT_ATTACK_MOVE : PACKET_BASE
{
	GS_PKT_ATTACK_MOVE()
	{
		ZeroMemory(this,sizeof(GS_PKT_ATTACK_MOVE));
		MPID = _GS_PKT_ATTACK_MOVE;	
		Len = sizeof(GS_PKT_ATTACK_MOVE);
	} 
	WORD AttackerwSid;
	WORD AttackFieldSlot;
	WORD TargetwSid;
	WORD TargetFieldSlotIdx;
};

struct GS_PKT_ATTACK_RE : PACKET_BASE
{
	GS_PKT_ATTACK_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_ATTACK_RE));
		MPID = _GS_PKT_ATTACK_RE;		
		Len = sizeof(GS_PKT_ATTACK_RE);
	}
	WORD AttackerwSid;
	WORD AttackFieldSlot; 
	WORD TargetwSid;
	WORD TargetFieldSlotIdx;    	
	WORD Critical;
	WORD Dmg;
	WORD Result;
};

struct GS_PKT_ATTACK_MOVE_RE : PACKET_BASE
{
	GS_PKT_ATTACK_MOVE_RE()
	{
		ZeroMemory(this,sizeof(GS_PKT_ATTACK_MOVE_RE));
		MPID = _GS_PKT_ATTACK_MOVE_RE;	
		Len = sizeof(GS_PKT_ATTACK_MOVE_RE);
	}
	WORD AttackerwSid;
	WORD AttackFieldSlot;
	WORD TargetwSid;
	WORD TargetFieldSlotIdx;
	WORD Result;
};

struct GS_PKT_DEL_CARD : PACKET_BASE
{
	GS_PKT_DEL_CARD()
	{
		ZeroMemory(this,sizeof(GS_PKT_DEL_CARD));
		MPID = _GS_PKT_DEL_CARD;	
		Len = sizeof(GS_PKT_DEL_CARD);
	}
	WORD DeckIndex;
};

struct GS_PKT_MISS : PACKET_BASE
{
	GS_PKT_MISS()
	{
		ZeroMemory(this,sizeof(GS_PKT_MISS));
		MPID = _GS_PKT_MISS;	
		Len = sizeof(GS_PKT_MISS);
	}
	WORD wSid;
	WORD FieldSlot;
};

struct	GS_PKT_NPC_CREATE : PACKET_BASE
{
	GS_PKT_NPC_CREATE()
	{
		memset(this, 0x00, sizeof(GS_PKT_NPC_CREATE));
		MPID = _GS_PKT_NPC_CREATE;
		Len = sizeof(GS_PKT_NPC_CREATE);
	}
	float x;
	float y;
	DWORD NPC_TableID;
};

struct	GS_PKT_NPC_MOVE : PACKET_BASE
{
	GS_PKT_NPC_MOVE() {
		memset(this, 0x00, sizeof(GS_PKT_NPC_MOVE));
		MPID = _GS_PKT_NPC_MOVE;
		Len = sizeof(GS_PKT_NPC_MOVE);
	};
	float x;
	float y;
	DWORD NPC_TableID;
};

struct	GS_PKT_NPC_WAIT : PACKET_BASE
{
	GS_PKT_NPC_WAIT() {
		memset(this, 0x00, sizeof(GS_PKT_NPC_WAIT));
		MPID = _GS_PKT_NPC_WAIT;
		Len = sizeof(GS_PKT_NPC_WAIT);
	};
	DWORD NPC_TableID;
};

struct	GS_PKT_NPC_ATTACK : PACKET_BASE					
{
	GS_PKT_NPC_ATTACK() {
		memset(this, 0x00, sizeof(GS_PKT_NPC_ATTACK));
		MPID = _GS_PKT_NPC_ATTACK;
		Len = sizeof(GS_PKT_NPC_ATTACK);
	};
	DWORD NPC_TableID;
	DWORD TargetSid;
};

struct	GS_PKT_NPC_DEATH : PACKET_BASE
{
	GS_PKT_NPC_DEATH() {
		memset(this, 0x00, sizeof(GS_PKT_NPC_DEATH));
		MPID = _GS_PKT_NPC_DEATH;
		Len = sizeof(GS_PKT_NPC_DEATH);
	};
	DWORD NPC_TableID;
};

struct	GS_PKT_USER_ATTACK_NPC : PACKET_BASE
{
	GS_PKT_USER_ATTACK_NPC() {
		memset(this, 0x00, sizeof(GS_PKT_USER_ATTACK_NPC));
		MPID = _GS_PKT_USER_ATTACK_NPC;
		Len = sizeof(GS_PKT_USER_ATTACK_NPC);
	};
	WORD NPC_TableID;
	WORD wSid;
};

struct GS_PKT_NPC_TRACE : PACKET_BASE
{
	GS_PKT_NPC_TRACE() {
		memset(this, 0x00, sizeof(GS_PKT_NPC_TRACE));
		MPID = _GS_PKT_NPC_TRACE;
		Len = sizeof(GS_PKT_NPC_TRACE);
	};
	WORD NPC_TableID;
	WORD wSid;
};

struct	GS_PKT_BATTLE_SESSION : PACKET_BASE
{
	GS_PKT_BATTLE_SESSION() {
		memset(this, 0x00, sizeof(GS_PKT_BATTLE_SESSION));
		MPID = _GS_PKT_BATTLE_SESSION;
		Len = sizeof(GS_PKT_BATTLE_SESSION);
	};
	
	DWORD NPC_ID;
	DWORD EvtID;
	DWORD RoomID;
	WORD Userlist[MAX_PARTY_MEMBER];
};

struct	GS_PKT_BATTLE_SESSION_END : PACKET_BASE
{
	GS_PKT_BATTLE_SESSION_END() {
		memset(this, 0x00, sizeof(GS_PKT_BATTLE_SESSION_END));
		MPID = _GS_PKT_BATTLE_SESSION_END;
		Len = sizeof(GS_PKT_BATTLE_SESSION_END);
	};
	
	DWORD NPC_ID;
	DWORD EvtID;
	DWORD RoomID;
	WORD Userlist[MAX_PARTY_MEMBER];
};

struct	GS_PKT_MP_BEGIN : PACKET_BASE
{
	GS_PKT_MP_BEGIN()
	{
		memset(this, 0x00, sizeof(GS_PKT_MP_BEGIN));
		MPID = _GS_PKT_MP_BEGIN;
		Len = sizeof(GS_PKT_MP_BEGIN);
	}

	WORD wSid;
	WORD InitMP;	//초기 설정값
	WORD Period;	//주기(초)
	double Quantity;	//올라가는 단위
};

struct	GS_PKT_EP_BEGIN : PACKET_BASE
{
	GS_PKT_EP_BEGIN()
	{
		memset(this, 0x00, sizeof(GS_PKT_EP_BEGIN));
		MPID = _GS_PKT_EP_BEGIN;
		Len = sizeof(GS_PKT_EP_BEGIN);
	}

	WORD wSid;
	WORD FieldSlot;
	WORD InitEP;	//초기 설정값
	WORD Period;	//주기(초)
	WORD Quantity;	//올라가는 단위
};
//유저 돈 획득
struct	GS_PKT_USER_MONEY_UPDATE : PACKET_BASE
{
	GS_PKT_USER_MONEY_UPDATE()
	{
		memset(this, 0x00, sizeof(GS_PKT_USER_MONEY_UPDATE));
		MPID = _GS_PKT_USER_MONEY_UPDATE;
		Len = sizeof(GS_PKT_USER_MONEY_UPDATE);
	}

	WORD    TargetSid;
	WORD    SrcSid;
	WORD	SlotIdx;
	DWORD   Money;
};
//유저 경험치 획득
struct	GS_PKT_USER_EXP_UPDATE : PACKET_BASE
{
	GS_PKT_USER_EXP_UPDATE()
	{
		memset(this, 0x00, sizeof(GS_PKT_USER_EXP_UPDATE));
		MPID = _GS_PKT_USER_EXP_UPDATE;
		Len = sizeof(GS_PKT_USER_EXP_UPDATE);
	}

	WORD    TargetSid;
	WORD    SrcSid;
	WORD	SlotIdx;
	DWORD   Exp;
};
//보상 카드 선택
struct GS_PKT_SELECT_COMPENSATION_CARD : PACKET_BASE
{
	GS_PKT_SELECT_COMPENSATION_CARD()
	{
		memset(this, 0x00, sizeof(GS_PKT_SELECT_COMPENSATION_CARD));
		MPID = _GS_PKT_SELECT_COMPENSATION_CARD;
		Len = sizeof(GS_PKT_SELECT_COMPENSATION_CARD);
	}

	BYTE SelPos;
};

//#ifdef SUB_CHANNEL
struct GS_PKT_CHANGE_SUBCHANNEL : PACKET_BASE
{
	GS_PKT_CHANGE_SUBCHANNEL()
	{
		memset(this, 0x00, sizeof(GS_PKT_CHANGE_SUBCHANNEL));
		MPID = _GS_PKT_CHANGE_SUBCHANNEL;
		Len = sizeof(GS_PKT_CHANGE_SUBCHANNEL);
	}
	WORD ChannelNum;
};
//#endif

struct COMPENSATION_INFO
{
	COMPENSATION_INFO()
	{
		memset(this, 0x00, sizeof(COMPENSATION_INFO));
	}

	WORD  Pos;
	WORD  InvenPos;

	CHAR_GAIN_CARD Card;
};
//보상 카드 선택 결과
struct GS_PKT_SELECT_COMPENSATION_CARD_RE : PACKET_BASE
{
	GS_PKT_SELECT_COMPENSATION_CARD_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_SELECT_COMPENSATION_CARD_RE));
		MPID = _GS_PKT_SELECT_COMPENSATION_CARD_RE;
		Len = sizeof(GS_PKT_SELECT_COMPENSATION_CARD_RE);
	}
	WORD Result;
	WORD    wSid;
	
	COMPENSATION_INFO FileDBID;
};
//보상창 띄우는 패킷 
struct GS_PKT_COMPENSATION : PACKET_BASE
{
	GS_PKT_COMPENSATION()
	{
		memset(this, 0x00, sizeof(GS_PKT_COMPENSATION));
		MPID = _GS_PKT_COMPENSATION;
		Len = sizeof(GS_PKT_COMPENSATION);
	}

	WORD wSid;
	WORD SelectCount;		//선택 가능 횟수.

	WORD CounterBlewCnt;
	WORD CriticalCnt;
	DWORD RemainDeckCnt;
	DWORD ClearTime;
	DWORD AcquireGold;
	DWORD AcquireExp;

};
//몬스터를 죽여 획득하는 카드
struct GS_PKT_ACQUIRE_CARD_IN_COMBAT : PACKET_BASE
{
	GS_PKT_ACQUIRE_CARD_IN_COMBAT()
	{
		memset(this, 0x00, sizeof(GS_PKT_ACQUIRE_CARD_IN_COMBAT));
		MPID = _GS_PKT_ACQUIRE_CARD_IN_COMBAT;
		Len = sizeof(GS_PKT_ACQUIRE_CARD_IN_COMBAT);
	}
	WORD SrcSid;		//카드 먹는 사람
	WORD TargetSid;		//몬스터를 죽인 사람
	WORD IvenPos;
	WORD SlotIdx;
	CHAR_GAIN_CARD Card;
};


struct GS_PKT_LEVELUP : PACKET_BASE
{
	GS_PKT_LEVELUP()
	{
		memset(this, 0x00, sizeof(GS_PKT_LEVELUP));
		MPID = _GS_PKT_LEVELUP;
		Len = sizeof(GS_PKT_LEVELUP);
	}
	WORD wSid;			// 유저 고유번호
	WORD wLev;			// 렙업한 결과 수치
};

struct GS_PKT_GETROOMINFO : PACKET_BASE
{
	GS_PKT_GETROOMINFO()
	{
		memset(this, 0x00, sizeof(GS_PKT_GETROOMINFO));
		MPID = _GS_PKT_GETROOMINFO;
		Len = sizeof(GS_PKT_GETROOMINFO);
	}
	int nRoomIdx;		// 렙업한 결과 수치
};

struct GS_PKT_GETROOMINFO_RE : PACKET_BASE
{
	GS_PKT_GETROOMINFO_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_GETROOMINFO_RE));
		MPID = _GS_PKT_GETROOMINFO_RE;
		Len = sizeof(GS_PKT_GETROOMINFO_RE);
	}
	//CREATE_ROOM_INFO	RoomInfo;
	GS_INROOM_USERDATA	PlayerList[MAX_PLAYER_INROOM];
	WORD				wResult;
};

struct GS_PKT_CREATE_PARTY : PACKET_BASE
{
	GS_PKT_CREATE_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_CREATE_PARTY));
		MPID = _GS_PKT_CREATE_PARTY;
		Len = sizeof(GS_PKT_CREATE_PARTY);
	}
	WORD				wSid;
};

struct GS_PKT_CREATE_PARTY_RE : PACKET_BASE
{
	GS_PKT_CREATE_PARTY_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_CREATE_PARTY_RE));
		MPID = _GS_PKT_CREATE_PARTY_RE;
		Len = sizeof(GS_PKT_CREATE_PARTY_RE);
	}
	DWORD				PartyIdx;
	WORD				wSid;		//파티장 번호
	WORD				wResult;	//결과값
};


struct GS_PKT_NEW_PARTY_LEADER : PACKET_BASE
{
	GS_PKT_NEW_PARTY_LEADER()
	{
		memset(this, 0x00, sizeof(GS_PKT_NEW_PARTY_LEADER));
		MPID = _GS_PKT_NEW_PARTY_LEADER;
		Len = sizeof(GS_PKT_NEW_PARTY_LEADER);
	}
	WORD				wSid;
};

struct GS_PKT_INVITE_PARTY : PACKET_BASE
{
	GS_PKT_INVITE_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_INVITE_PARTY));
		MPID = _GS_PKT_INVITE_PARTY;
		Len = sizeof(GS_PKT_INVITE_PARTY);
	}
	WORD				wSid;
};

struct GS_PKT_INVITE_PARTY_RE : PACKET_BASE
{
	GS_PKT_INVITE_PARTY_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_INVITE_PARTY_RE));
		MPID = _GS_PKT_INVITE_PARTY_RE;
		Len = sizeof(GS_PKT_INVITE_PARTY_RE);
	}

	WORD	Result;
	WORD				wSid;
};

struct GS_PKT_NEW_PARTY_MEMBER: PACKET_BASE
{
	GS_PKT_NEW_PARTY_MEMBER()
	{
		memset(this, 0x00, sizeof(GS_PKT_NEW_PARTY_MEMBER));
		MPID = _GS_PKT_NEW_PARTY_MEMBER;
		Len = sizeof(GS_PKT_NEW_PARTY_MEMBER);
	}
	PARTY_USER_INFO				data;
};

struct GS_PKT_LEAVE_PARTY : PACKET_BASE
{
	GS_PKT_LEAVE_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_LEAVE_PARTY));
		MPID = _GS_PKT_LEAVE_PARTY;
		Len = sizeof(GS_PKT_LEAVE_PARTY);
	}

	WORD				wSid;
};

struct GS_PKT_LEAVE_PARTY_RE : PACKET_BASE
{
	GS_PKT_LEAVE_PARTY_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_LEAVE_PARTY_RE));
		MPID = _GS_PKT_LEAVE_PARTY_RE;
		Len = sizeof(GS_PKT_LEAVE_PARTY_RE);
	}
	WORD				wSid;
	WORD				wResult;
};

struct GS_PKT_ENTER_PARTY : PACKET_BASE
{
	GS_PKT_ENTER_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_ENTER_PARTY));
		MPID = _GS_PKT_ENTER_PARTY;
		Len = sizeof(GS_PKT_ENTER_PARTY);
	}
	WORD				PartyIdx;
};

struct GS_PKT_ENTER_PARTY_RE : PACKET_BASE
{
	GS_PKT_ENTER_PARTY_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_ENTER_PARTY_RE));
		MPID = _GS_PKT_ENTER_PARTY_RE;
		Len = sizeof(GS_PKT_ENTER_PARTY_RE);
	}


	DWORD				PartyIdx;		//파티번호
	PARTY_USER_INFO		UserList[MAX_PARTY_MEMBER];
	WORD				PartyLeaderwSid;
};

struct GS_PKT_UPDATE_TOKEN : PACKET_BASE
{
	GS_PKT_UPDATE_TOKEN()
	{
		memset(this, 0x00, sizeof(GS_PKT_UPDATE_TOKEN));
		MPID = _GS_PKT_UPDATE_TOKEN;
		Len = sizeof(GS_PKT_UPDATE_TOKEN);
	}

	DWORD				nToken;		//현재 토큰 갯수
};

struct GS_PKT_SEARCH_PARTY : PACKET_BASE
{
	GS_PKT_SEARCH_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_SEARCH_PARTY));
		MPID = _GS_PKT_SEARCH_PARTY;
		Len = sizeof(GS_PKT_SEARCH_PARTY);
	}
	
	DWORD SenarioIdx;
	DWORD DungeonMapIdx;
};


struct GS_PKT_CHG_PARTY_OPT : PACKET_BASE
{
	GS_PKT_CHG_PARTY_OPT()
	{
		memset(this, 0x00, sizeof(GS_PKT_CHG_PARTY_OPT));
		MPID = _GS_PKT_CHG_PARTY_OPT;
		Len = sizeof(GS_PKT_CHG_PARTY_OPT);
	}

	WORD Senario;
	WORD DungeonIdx;
};

struct GS_PKT_CHG_PARTY_OPT_RE : PACKET_BASE
{
	GS_PKT_CHG_PARTY_OPT_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_CHG_PARTY_OPT_RE));
		MPID = _GS_PKT_CHG_PARTY_OPT_RE;
		Len = sizeof(GS_PKT_CHG_PARTY_OPT_RE);
	}

	WORD Result;
	WORD ErrorwSid;

	WORD Senario;
	WORD DungeonIdx;
};

struct GS_PKT_READY_PARTY : PACKET_BASE
{
	GS_PKT_READY_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_READY_PARTY));
		MPID = _GS_PKT_READY_PARTY;
		Len = sizeof(GS_PKT_READY_PARTY);
	}
};

struct GS_PKT_READY_PARTY_RE : PACKET_BASE
{
	GS_PKT_READY_PARTY_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_READY_PARTY_RE));
		MPID = _GS_PKT_READY_PARTY_RE;
		Len = sizeof(GS_PKT_READY_PARTY_RE);
	}

	WORD Result;
	WORD IsReady;		//0 : 준비않됨 1: 준비됨
	WORD wSid;
};

struct GS_PKT_START_PARTY : PACKET_BASE
{
	GS_PKT_START_PARTY()
	{
		memset(this, 0x00, sizeof(GS_PKT_START_PARTY));
		MPID = _GS_PKT_START_PARTY;
		Len = sizeof(GS_PKT_START_PARTY);
	}
};

struct GS_PKT_START_PARTY_RE : PACKET_BASE
{
	GS_PKT_START_PARTY_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_START_PARTY_RE));
		MPID = _GS_PKT_START_PARTY_RE;
		Len = sizeof(GS_PKT_START_PARTY_RE);
	}

	WORD Result;
};

struct GS_PKT_HOLY_PLACE : PACKET_BASE
{
	GS_PKT_HOLY_PLACE()
	{
		memset(this, 0x00, sizeof(GS_PKT_HOLY_PLACE));
		MPID = _GS_PKT_HOLY_PLACE;
		Len = sizeof(GS_PKT_HOLY_PLACE);
	}
};

struct GS_PKT_HOLY_PLACE_RE : PACKET_BASE
{
	GS_PKT_HOLY_PLACE_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_HOLY_PLACE_RE));
		MPID = _GS_PKT_HOLY_PLACE_RE;
		Len = sizeof(GS_PKT_HOLY_PLACE_RE);
	}

	WORD Result;
};

struct GS_PKT_RESURRECTION : PACKET_BASE
{
	GS_PKT_RESURRECTION()
	{
		memset(this, 0x00, sizeof(GS_PKT_RESURRECTION));
		MPID = _GS_PKT_RESURRECTION;
		Len = sizeof(GS_PKT_RESURRECTION);
	}

	WORD wSid;
};

struct GS_PKT_RESURRECTION_RE : PACKET_BASE
{
	GS_PKT_RESURRECTION_RE()
	{
		memset(this, 0x00, sizeof(GS_PKT_RESURRECTION_RE));
		MPID = _GS_PKT_RESURRECTION_RE;
		Len = sizeof(GS_PKT_RESURRECTION_RE);
	}

	WORD Result;
	WORD wSid;
};

struct GS_PKT_USER_DEATH : PACKET_BASE
{
	GS_PKT_USER_DEATH()
	{
		memset(this, 0x00, sizeof(GS_PKT_USER_DEATH));
		MPID = _GS_PKT_USER_DEATH;
		Len = sizeof(GS_PKT_USER_DEATH);
	}

	WORD wSid;
};

struct GS_PKT_UPDATE_LIFE_PT : PACKET_BASE
{
	GS_PKT_UPDATE_LIFE_PT()
	{
		memset(this, 0x00, sizeof(GS_PKT_UPDATE_LIFE_PT));
		MPID = _GS_PKT_UPDATE_LIFE_PT;
		Len = sizeof(GS_PKT_UPDATE_LIFE_PT);
	}

	WORD Cnt;
};


struct GS_PKT_CLICK_NPC : PACKET_BASE
{
	GS_PKT_CLICK_NPC()
	{
		memset(this, 0x00, sizeof(GS_PKT_CLICK_NPC));
		MPID = _GS_PKT_CLICK_NPC;
		Len = sizeof(GS_PKT_CLICK_NPC);
	}

	DWORD TableID;
};

#ifdef _SERVER
//////////////////////////////////////////////////////////////////////
// Middleware packet defines.
// Created by Timothy 2009.05.06.
////////////////////////////////////////////////////////////////////// MIDDLEWARE PROTOCOL

enum eMW_PACKET_ID {
	_MW_PKT_USER_LOGIN = 400,	/// 로그인
	_MW_PKT_USER_LOGIN_RE,
	_MW_PKT_USER_LOGOUT,		/// 로그아웃
	_MW_PKT_USER_LOGOUT_RE,
	_MW_PKT_USER_SAVE,			/// 유저 저장(안쓰임)
	_MW_PKT_USER_SAVE_RE,		/// 유저 저장(안쓰임)
	_MW_PKT_CHAR_CNT,			/// 캐릭터 갯수
	_MW_PKT_CHAR_CNT_RE,
	_MW_PKT_MYCHAR_GET,			/// 내 캐릭터 얻기
	_MW_PKT_MYCHAR_GET_RE,
	_MW_PKT_MYCHAR_ADD,			/// 내 캐릭터 추가
	_MW_PKT_MYCHAR_ADD_RE,
	_MW_PKT_MYCHAR_DEL,			/// 내 캐릭터 제거
	_MW_PKT_MYCHAR_DEL_RE,
	_MW_PKT_MYCHAR_ENTREE,		/// 내 캐릭터 마을입장
	_MW_PKT_MYCHAR_ENTREE_RE,
	_MW_PKT_MYCHAR_DECK_GET,	/// 덱 얻기(안쓰임)
	_MW_PKT_MYCHAR_DECK_GET_RE, /// 덱 얻기(안쓰임)
	_MW_PKT_MYCHAR_INVENTORY,	/// 인벤토리 얻기(안쓰임)
	_MW_PKT_MYCHAR_INVENTORY_RE,/// 인벤토리 얻기(안쓰임)
	_MW_PKT_CHARSEL_ENTREE,		/// 캐릭터 선택존 입장
	_MW_PKT_CHARSEL_ENTREE_RE,	
	_MW_PKT_DUNGEON_LEAVE,		/// 던전 퇴장(안쓰임)
	_MW_PKT_DUNGEON_LEAVE_RE,	/// 던전 퇴장(안쓰임)
	_MW_PKT_CHAR_SAVE,			/// 캐릭터 저장
	_MW_PKT_CHAR_SAVE_RE,	
	_MW_PKT_GET_EVT_TIME,
	_MW_PKT_GET_EVT_TIME_RE,
	_MW_PKT_GET_EVT_UPDATE_TIME,
	_MW_PKT_GET_EVT_UPDATE_TIME_RE,
	_MW_PKT_UPDATE_TOKEN_ALL_USERS,
	_MW_PKT_UPDATE_LOG_MSG
};

struct MW_PKT_USER_LOGIN : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wChannelID;
	char			szUserID[_MAX_USER_ID_SIZE];
	char			szSessionKey[_MAX_SESSION_KEY_SIZE];
	char			szLanIP[_MAX_IP_SIZE];
	MW_PKT_USER_LOGIN() {
		memset(this, 0, sizeof(MW_PKT_USER_LOGIN));
		MPID = _MW_PKT_USER_LOGIN;
		Len = sizeof(MW_PKT_USER_LOGIN);
	};
};

struct MW_PKT_USER_LOGIN_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wCharCount;
	char			szUserID[_MAX_USER_ID_SIZE];
	char			szLanIP[_MAX_IP_SIZE];
	char			szCharNames[_MAX_CHAR_ID_SIZE*_MAX_USER_CHAR_SIZE*2];
	int				nCP;
	unsigned short	wResult;
	MW_PKT_USER_LOGIN_RE() {
		memset(this, 0, sizeof(MW_PKT_USER_LOGIN_RE));
		MPID = _MW_PKT_USER_LOGIN_RE;
		Len = sizeof(MW_PKT_USER_LOGIN_RE);
	};
};

struct MW_PKT_USER_LOGOUT : PACKET_BASE
{
	unsigned short	wSid;
	char			szUserID[_MAX_USER_ID_SIZE];
	MW_PKT_USER_LOGOUT() {
		memset(this, 0, sizeof(MW_PKT_USER_LOGOUT));
		MPID = _MW_PKT_USER_LOGOUT;
		Len = sizeof(MW_PKT_USER_LOGOUT);
	};
};

struct MW_PKT_USER_LOGOUT_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	MW_PKT_USER_LOGOUT_RE() {
		memset(this, 0, sizeof(MW_PKT_USER_LOGOUT_RE));
		MPID = _MW_PKT_USER_LOGOUT_RE;
		Len = sizeof(MW_PKT_USER_LOGOUT_RE);
	};
};

struct MW_PKT_USER_SAVE : PACKET_BASE
{
	unsigned short	wSid;
	MW_PKT_USER_SAVE() {
		memset(this, 0, sizeof(MW_PKT_USER_SAVE));
		MPID = _MW_PKT_USER_SAVE;
		Len = sizeof(MW_PKT_USER_SAVE);
	};
};

struct MW_PKT_USER_SAVE_RE : PACKET_BASE
{
	unsigned short	wSid;
	MW_PKT_USER_SAVE_RE() {
		memset(this, 0, sizeof(MW_PKT_USER_SAVE_RE));
		MPID = _MW_PKT_USER_SAVE_RE;
		Len = sizeof(MW_PKT_USER_SAVE_RE);
	};
};

struct MW_PKT_CHAR_CNT : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_CHAR_CNT() {
		memset(this, 0, sizeof(MW_PKT_CHAR_CNT));
		MPID = _MW_PKT_CHAR_CNT;
		Len = sizeof(MW_PKT_CHAR_CNT);
	};
};

struct MW_PKT_CHAR_CNT_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wCount;
	MW_PKT_CHAR_CNT_RE() {
		memset(this, 0, sizeof(MW_PKT_CHAR_CNT_RE));
		MPID = _MW_PKT_CHAR_CNT_RE;
		Len = sizeof(MW_PKT_CHAR_CNT_RE);
	};
};

struct MW_PKT_MYCHAR_GET : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_MYCHAR_GET() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_GET));
		MPID = _MW_PKT_MYCHAR_GET;
		Len = sizeof(MW_PKT_MYCHAR_GET);
	};
};

struct MW_PKT_MYCHAR_GET_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	MW_PKT_MYCHAR_GET_RE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_GET_RE));
		MPID = _MW_PKT_MYCHAR_GET_RE;
		Len = sizeof(MW_PKT_MYCHAR_GET_RE);
	};
};

struct MW_PKT_MYCHAR_ADD : PACKET_BASE
{
	unsigned short	wSid;
	CHAR_DATA		Character;
	MW_PKT_MYCHAR_ADD() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_ADD));
		MPID = _MW_PKT_MYCHAR_ADD;
		Len = sizeof(MW_PKT_MYCHAR_ADD);
	};
};

struct MW_PKT_MYCHAR_ADD_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	CHAR_DATA		Character;
	MW_PKT_MYCHAR_ADD_RE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_ADD_RE));
		MPID = _MW_PKT_MYCHAR_ADD_RE;
		Len = sizeof(MW_PKT_MYCHAR_ADD_RE);
	};
};

struct MW_PKT_MYCHAR_DEL : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_MYCHAR_DEL() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_DEL));
		MPID = _MW_PKT_MYCHAR_DEL;
		Len = sizeof(MW_PKT_MYCHAR_DEL);
	};
};

struct MW_PKT_MYCHAR_DEL_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_MYCHAR_DEL_RE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_DEL_RE));
		MPID = _MW_PKT_MYCHAR_DEL_RE;
		Len = sizeof(MW_PKT_MYCHAR_DEL_RE);
	};
};

struct MW_PKT_MYCHAR_ENTREE : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_MYCHAR_ENTREE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_ENTREE));
		MPID = _MW_PKT_MYCHAR_ENTREE;
		Len = sizeof(MW_PKT_MYCHAR_ENTREE);
	};
};

struct MW_PKT_MYCHAR_ENTREE_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_MYCHAR_ENTREE_RE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_ENTREE_RE));
		MPID = _MW_PKT_MYCHAR_ENTREE_RE;
		Len = sizeof(MW_PKT_MYCHAR_ENTREE_RE);
	};
};

struct MW_PKT_CHARSEL_ENTREE : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_CHARSEL_ENTREE() {
		memset(this, 0, sizeof(MW_PKT_CHARSEL_ENTREE));
		MPID = _MW_PKT_CHARSEL_ENTREE;
		Len = sizeof(MW_PKT_CHARSEL_ENTREE);
	};
};

struct MW_PKT_CHARSEL_ENTREE_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	MW_PKT_CHARSEL_ENTREE_RE() {
		memset(this, 0, sizeof(MW_PKT_CHARSEL_ENTREE_RE));
		MPID = _MW_PKT_CHARSEL_ENTREE_RE;
		Len = sizeof(MW_PKT_CHARSEL_ENTREE_RE);
	};
};

struct MW_PKT_DUNGEON_LEAVE : PACKET_BASE
{
	unsigned short	wSid;
	MW_PKT_DUNGEON_LEAVE() {
		memset(this, 0, sizeof(MW_PKT_DUNGEON_LEAVE));
		MPID = _MW_PKT_DUNGEON_LEAVE;
		Len = sizeof(MW_PKT_DUNGEON_LEAVE);
	};
};

struct MW_PKT_DUNGEON_LEAVE_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	MW_PKT_DUNGEON_LEAVE_RE() {
		memset(this, 0, sizeof(MW_PKT_DUNGEON_LEAVE_RE));
		MPID = _MW_PKT_DUNGEON_LEAVE_RE;
		Len = sizeof(MW_PKT_DUNGEON_LEAVE_RE);
	};
};

struct MW_PKT_CHAR_SAVE : PACKET_BASE
{
	unsigned short	wSid;
	MW_PKT_CHAR_SAVE() {
		memset(this, 0, sizeof(MW_PKT_CHAR_SAVE));
		MPID = _MW_PKT_CHAR_SAVE;
		Len = sizeof(MW_PKT_CHAR_SAVE);
	};
};

struct MW_PKT_CHAR_SAVE_RE : PACKET_BASE
{
	unsigned short	wSid;
	unsigned short	wResult;
	MW_PKT_CHAR_SAVE_RE() {
		memset(this, 0, sizeof(MW_PKT_CHAR_SAVE_RE));
		MPID = _MW_PKT_CHAR_SAVE_RE;
		Len = sizeof(MW_PKT_CHAR_SAVE_RE);
	};
};

struct MW_PKT_GET_EVT_TIME : PACKET_BASE
{
	MW_PKT_GET_EVT_TIME() {
		memset(this, 0, sizeof(MW_PKT_GET_EVT_TIME));
		MPID = _MW_PKT_GET_EVT_TIME;
		Len = sizeof(MW_PKT_GET_EVT_TIME);
	};

	BYTE EvtID;
};

struct MW_PKT_GET_EVT_TIME_RE : PACKET_BASE
{
	char FireTime[20];
	int  TypeID;

	MW_PKT_GET_EVT_TIME_RE() {
		memset(this, 0, sizeof(MW_PKT_GET_EVT_TIME_RE));
		MPID = _MW_PKT_GET_EVT_TIME_RE;
		Len = sizeof(MW_PKT_GET_EVT_TIME_RE);
	};
};

struct MW_PKT_GET_EVT_UPDATE_TIME : PACKET_BASE
{
	WORD Type;
	WORD AddDay;
	MW_PKT_GET_EVT_UPDATE_TIME() {
		memset(this, 0, sizeof(MW_PKT_GET_EVT_UPDATE_TIME));
		MPID = _MW_PKT_GET_EVT_UPDATE_TIME;
		Len = sizeof(MW_PKT_GET_EVT_UPDATE_TIME);
	};
};

struct MW_PKT_GET_EVT_UPDATE_TIME_RE : PACKET_BASE
{
	MW_PKT_GET_EVT_UPDATE_TIME_RE() {
		memset(this, 0, sizeof(MW_PKT_GET_EVT_UPDATE_TIME_RE));
		MPID = _MW_PKT_GET_EVT_UPDATE_TIME_RE;
		Len = sizeof(MW_PKT_GET_EVT_UPDATE_TIME_RE);
	};
};


struct MW_PKT_UPDATE_TOKEN_ALL_USERS : PACKET_BASE
{
	MW_PKT_UPDATE_TOKEN_ALL_USERS() {
		memset(this, 0, sizeof(MW_PKT_UPDATE_TOKEN_ALL_USERS));
		MPID = _MW_PKT_UPDATE_TOKEN_ALL_USERS;
		Len = sizeof(MW_PKT_UPDATE_TOKEN_ALL_USERS);
	};

	int Cnt;
};

struct MW_PKT_UPDATE_LOG_MSG : PACKET_BASE
{
	MW_PKT_UPDATE_LOG_MSG() {
		memset(this, 0, sizeof(MW_PKT_UPDATE_LOG_MSG));
		MPID = _MW_PKT_UPDATE_LOG_MSG;
		Len = sizeof(MW_PKT_UPDATE_LOG_MSG);
	};

	WORD	Type;
	WCHAR   szMsg[300];
	WCHAR	szUserID[_MAX_USER_ID_SIZE];	/// 아이디
	WCHAR	szCharName[_MAX_CHAR_ID_SIZE];			/// 패스워드

};
#endif
/////////////////////////////////////////////////////////////////////// MIDDLEWARE PROTOCOL

#pragma pack()
