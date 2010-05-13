#pragma once

#ifdef _WIN32
	#pragma pack( push ,1 )
#else
	#pragma pack(1)
#endif

#ifdef _SERVER
	#include <string>

	inline std::string trim_right ( const std::string & source , const std::string & t = " " ) 
	{
		std::string str = source; 
		return str.erase ( str.find_last_not_of ( t ) + 1 ) ;
	}
#endif


// Socket Define Values.
const BYTE TYPE_LISTEN			= 0x01;
const BYTE TYPE_CLIENT			= 0x02;
const BYTE TYPE_SERVER			= 0x03;

#define _PACKET_MTU					4096	// Max Packet Size...

const DWORD _MAX_ACCEPTABLE_COUNT = 500;
const DWORD _MIN_ACCEPTABLE_COUNT = 200;

// packet direction
#define _FROM_CLIENT			0x01
#define _FROM_SERVER			0x02
#define _FROM_MIDDLEWARE		0x03

// packet wrap parity bytes
const BYTE _PACKET_START1		= 0x55;
const BYTE _PACKET_START2		= 0xBB;
const BYTE _PACKET_END1			= 0x55;
const BYTE _PACKET_END2			= 0xBB;

// string length define for packet design.
#define _MAX_SESSION_KEY_SIZE		64		// user authorized login key value
#define _MAX_USER_ID_SIZE			20		// 계정 이름 길이
#define _MAX_CHAR_ID_SIZE			12		// 캐릭터 이름 길이
#define _MAX_USER_CHAR_SIZE			6		// 계정당 캐릭터 최대수
#define _MAX_NICK_NAME_SIZE			10		// user nickname max length
#define _MAX_CHAT_SIZE				256		// chat message max length
#define _MAX_SERVER_NAME			20		// server id max length
#define _MAX_DECK_NAME				10		// 데크의 이름 길이
#define _MAX_PARTS_CARD_SIZE		30		// 파츠의 카드 최대수
#define _MAX_PARTS_CARD_USE_SIZE	10		// 파츠의 카드 현재 사용수
#define _MAX_DECK_CARD_SIZE			50		// 데크의 카드 최대수
#define _MAX_INVENTORY_CARD_SIZE	100		// 가방의 카드 최대수
#define _MAX_STORAGE_CARD_SIZE		300		// 창고의 카드 최대수
#define _MAX_CHAR_DECK_SIZE			6		// 캐릭터의 데크 최대수
#define _MAX_SYSTEM_MSG				128		// system message max length
#define _MAX_IP_SIZE				20		// IPv4 address size
#define _MAX_PWD_SIZE				16		// password string max length
#define _MAX_DEFINED_DATA			4000	// user defined data max size in packet
#define _MAX_TRADE_CARD_PERSON		5		// 카드거래(개인)
#define _MAX_TRADE_CARD_MIX			3		// 카드거래(조합)
#define _MAX_TRADE_CARD_PRODUCT		8		// 카드거래(제작)
#define _MAX_TRADE_CARD_DISSOLVE	8		// 카드거래(분해)
#define _MAX_AWARD_CARD_SIZE		10		// 보상으로 주는 카드 최대수
#define _MAX_BOOSTER_CARD_SIZE		50		// 부스터의 카드 리스트 최대 개수
#define _MAX_BOOSTER_GAIN_SIZE		20		// 부스터에서 얻을 수 있는 카드 최대개수
#define _MAX_TRADE_CARD_AMOUNT		20000	// 한번에 카드거래할 수 있는 최대량
// database define values
#define _MAX_SHARED_NAME			20		// shared memory share name.
#define _MAX_DB_DSN					20		// ODBC Name
#define _MAX_DB_UID					20		// ODBC Login ID
#define _MAX_DB_PWD					20		// ODBC Login Pwd

#define _NOT_CONNECTED				65535

#define MAX_PLAYER_INROOM			10
#define MAX_TARGET_LIST				10

enum eUSER_EXIST_AREA						// 유저위치
{
	_USER_AREA_NONE = 0,
	_USER_AREA_CHAR,						/// 캐릭터 선택 지역
	_USER_AREA_LOBBY,						/// 마을 로비 지역
	_USER_AREA_WAITROOM,					/// 대기방(게임전) 지역
	_USER_AREA_GAMEROOM,					/// 게임방(게임중) 지역
	_USER_AREA_DUNGEON,						/// 던전 지역
	_USER_AREA_MAX
};

enum eUSER_EXIST_ZONE						// 유저위치
{
	_USER_ZONE_NONE = 0,
	_USER_ZONE_RAZKA_CLOISTER = 30000001,	/// 라즈카 마을
	_USER_ZONE_CLIVE_MOUNTAIN,				/// 클라이브 바위산
	_USER_ZONE_LAVA_CAVE,					/// 용암동굴
	_USER_ZONE_KHAUKET_ALTAR,				/// 카우케트 제단
	_USER_ZONE_LIEN_UNDERGROUND,			/// 하이넨 지하수로
	_USER_ZONE_RAZTEKA_RUINS,				/// 라즈테카 유적
	_USER_ZONE_RAZKA_FORREST,				/// 라즈타 숲
	_USER_ZONE_PIT_OF_ETERNITY,				/// 영원의 나락
	_USER_ZONE_WIND_VALLEY,					/// 바람의 계곡
	_USER_ZONE_CHARACTER_LOBBY,				/// 캐릭터 로비
	_USER_ZONE_CAIZA_DESERT,				/// 카이자 사막
	_USER_ZONE_WATER_ALTER,					/// 물의 신전
	_USER_ZONE_LAZKA_MASON_VILLAGE			/// 라즈카 석공마을
};

//장착되는 장소.
enum eCHAR_PARTS_SLOT
{
	_CHAR_PARTS_HEAD=0,		/// [0. 머리]
	_CHAR_PARTS_ARMOR,		/// [1. 상의]
	_CHAR_PARTS_PANTS,		/// [2. 하의]
	_CHAR_PARTS_GLOVES,		/// [3. 손]
	_CHAR_PARTS_BOOTS,		/// [4. 발]
	_CHAR_PARTS_AMULATE,	/// [5. 목걸이]
	_CHAR_PARTS_RING,		/// [6. 반지]
	_CHAR_PARTS_BELT,		/// [7. 벨트]
	_CHAR_PARTS_WEAPON_R,	/// [8. 오른손 무기(공격구)]
	_CHAR_PARTS_WEAPON_L,	/// [9. 왼손 무기(방어구)]
	_CHAR_PARTS_MAX,
	_CHAR_PARTS_NONE = 255,
};

//장착되는 파츠의 타입.
enum eATTACH_PARTSTYPE
{
	_HEAD=0,				/// [0. 투구]
	_ARMOR,					/// [1. 상의] 
	_PANTS,					/// [2. 하의] 
	_GLOVES,				/// [3. 장갑] 
	_BOOTS,					/// [4. 신발] 
	_AMULATE,				/// [5. 목걸이] 
	_RING,					/// [6. 반지] 
	_BELT,					/// [7. 벨트] 
	_RIGHT_OR_LEFT = 8,		/// [8. 오른손or왼손]	(1000)	//비트 계산 가능.
	_RIGHT_HAND = 9,		/// [9. 오른손]			(1001)
	_LEFT_HAND = 10,		/// [10. 왼손]			(1010)
	_RIGHT_AND_LEFT = 11,	/// [11. 양손]			(1011)
	//이하 나중에 추가될 예정임
	//	_BOW,				/// 활 
	//	_LANCE,				/// 창
	_UNDEFINEDTYPE = 255
};

enum eROOM_STATE
{
	_ROOM_STATE_WAIT,
	_ROOM_STATE_GAMMING,
	_ROOM_STATE_END
};


enum eCHAR_CAED_MOVE_KIND					/// 카드이동 
{
	_CHAR_CAED_MOVE_NONE = 0,
	_CHAR_CAED_MOVE_INVEN_TO_PARTS,			/// 가방->파츠
	_CHAR_CAED_MOVE_PARTS_TO_INVEN,			/// 파츠->가방
	_CHAR_CAED_MOVE_INVEN_TO_INVEN,			/// 가방->가방
	_CHAR_CAED_MOVE_DECK1_TO_DECK1,			/// 데크1->데크1
	_CHAR_CAED_MOVE_DECK2_TO_DECK2,			/// 데크2->데크2
	_CHAR_CAED_MOVE_DECK3_TO_DECK3,			/// 데크3->데크3
	_CHAR_CAED_MOVE_DECK4_TO_DECK4,			/// 데크4->데크4
	_CHAR_CAED_MOVE_DECK5_TO_DECK5,			/// 데크5->데크5
	_CHAR_CAED_MOVE_DECK6_TO_DECK6,			/// 데크6->데크6
	_CHAR_CAED_MOVE_INVEN_TO_DECK1,			/// 가방->데크1
	_CHAR_CAED_MOVE_INVEN_TO_DECK2,			/// 가방->데크2
	_CHAR_CAED_MOVE_INVEN_TO_DECK3,			/// 가방->데크3
	_CHAR_CAED_MOVE_INVEN_TO_DECK4,			/// 가방->데크4
	_CHAR_CAED_MOVE_INVEN_TO_DECK5,			/// 가방->데크5
	_CHAR_CAED_MOVE_INVEN_TO_DECK6,			/// 가방->데크6
	_CHAR_CAED_MOVE_DECK1_TO_INVEN,			/// 데크1->가방
	_CHAR_CAED_MOVE_DECK2_TO_INVEN,			/// 데크2->가방
	_CHAR_CAED_MOVE_DECK3_TO_INVEN,			/// 데크3->가방
	_CHAR_CAED_MOVE_DECK4_TO_INVEN,			/// 데크4->가방
	_CHAR_CAED_MOVE_DECK5_TO_INVEN,			/// 데크5->가방
	_CHAR_CAED_MOVE_DECK6_TO_INVEN,			/// 데크6->가방
	_CHAR_CAED_MOVE_PERSON_TO_PERSON,		/// 카드거래: 개인->개인
	_CHAR_CAED_MOVE_PERSON_TO_INVEN,		/// 카드거래: 개인->가방
	_CHAR_CAED_MOVE_INVEN_TO_PERSON,		/// 카드거래: 가방->개인
	_CHAR_CAED_MOVE_MIX_TO_MIX,				/// 카드거래: 조합->조합
	_CHAR_CAED_MOVE_MIX_TO_INVEN,			/// 카드거래: 조합->가방
	_CHAR_CAED_MOVE_INVEN_TO_MIX,			/// 카드거래: 가방->조합
	_CHAR_CAED_MOVE_PRODUCT_TO_PRODUCT,		/// 카드거래: 제작->제작
	_CHAR_CAED_MOVE_PRODUCT_TO_INVEN,		/// 카드거래: 제작->가방
	_CHAR_CAED_MOVE_INVEN_TO_PRODUCT,		/// 카드거래: 가방->제작
	_CHAR_CAED_MOVE_DISSOLVE_TO_INVEN,		/// 카드거래: 분해->가방
	_CHAR_CAED_MOVE_INVEN_TO_DISSOLVE,		/// 카드거래: 가방->분해
};

//////////////////////////////////////////////////////////////////////////////////
// Login Server Defined Structure
// Designed by Timothy 2009.5.14
// These are PHOBEOS -- 
struct CHANNEL_INFO
{
	WORD	wID;							// Phobeo Index	- EXAMPLE: 1-500 = beginner, 501-2000 = normal, 2001 - 3000 = clan
	WCHAR	szName[_MAX_SERVER_NAME];		// Phobeo Name
	WORD	wType;							// the GROUP this phobeo belongs	- ie: beginner, normal, clan
	WORD	wCCU;							// ConCurrent user count
	char	szIP[_MAX_IP_SIZE];				// address ip
	WORD	wPort;							// address port
	WORD	wMaxUsers;						// Max users
	WORD	wStatus;						// Current status
	CHANNEL_INFO() { memset(this, 0, sizeof(CHANNEL_INFO)); };
};

struct SERVER_INFO
{
	WORD	wIndex;
	WCHAR	szName[_MAX_SERVER_NAME];
	SERVER_INFO() { memset(this, 0, sizeof(SERVER_INFO)); };
};

typedef union{
	WORD		w;
	BYTE		b[2];
} SERIAL_INDEX;

typedef union{
	__int64		i;
	BYTE		b[8];
} CARD_SERIAL;

struct CHAR_GAIN_CARD			/// 메인 캐릭터가 획득한 카드정보
{
	DWORD		nIdxCard;		/// 카드 인덱스
	CARD_SERIAL	UID;			/// 카드 시리얼(획득시 부여되는 값)
	WORD		wRemainUse;		/// 남은 사용 횟수
	WORD		wRemainTrade;	/// 남은 트래이드 횟수
	WORD		wRemainTime;	/// 남은 사용시간
	WORD		wEndurance;		/// 남은 내구도
	short		sTransPara1;	/// 변화 파라미터1
	short		sTransPara2;	/// 변화 파라미터2
	short		sTransPara3;	/// 변화 파라미터3
	short		sFold;			/// 중복 개수
	CHAR_GAIN_CARD() { memset(this, 0, sizeof(CHAR_GAIN_CARD)); };
};

struct CHAR_PARTS				/// 캐릭터 파츠
{
	CHAR_GAIN_CARD	Card[_MAX_PARTS_CARD_SIZE];
	CHAR_PARTS() { memset(this, 0, sizeof(CHAR_PARTS)); };
};

struct CHAR_DECK				/// 캐릭터 데크
{
	WORD			wIndex;		/// 1~6번덱 번호 
	WORD			wCount;		/// 세팅된 카드의 수
	WCHAR			szName[_MAX_DECK_NAME];
	CHAR_GAIN_CARD	Card[_MAX_DECK_CARD_SIZE];
	CHAR_DECK() { memset(this, 0, sizeof(CHAR_DECK)); };
};

struct CHAR_INVENTORY			/// 캐릭터 가방
{
	WORD			wCount;		/// 세팅된 카드의 수
	CHAR_GAIN_CARD	Card[_MAX_INVENTORY_CARD_SIZE];
	CHAR_INVENTORY() { memset(this, 0, sizeof(CHAR_INVENTORY)); };
};

struct TRADE_CARD_PERSON		/// 카드거래정보(개인)
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PERSON];	/// 거래카드
	int				nGP;							/// 게임포인트
	TRADE_CARD_PERSON() { memset(this, 0, sizeof(TRADE_CARD_PERSON)); };
};

struct TRADE_CARD_MIX			/// 카드거래정보(조합)
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_MIX];	/// 거래카드
	CHAR_GAIN_CARD	Mix;						/// 조합카드(결과)
	TRADE_CARD_MIX() { memset(this, 0, sizeof(TRADE_CARD_MIX)); };
};

struct TRADE_CARD_PRODUCT		/// 카드거래정보(제작)
{
	//CHAR_GAIN_CARD	Card[3];	/// 재료카드
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PRODUCT];	/// 재료카드
	CHAR_GAIN_CARD	Product;	/// 제작카드(결과)
	TRADE_CARD_PRODUCT() { memset(this, 0, sizeof(TRADE_CARD_PRODUCT)); };
};

struct TRADE_CARD_DISSOLVE		/// 카드거래정보(분해)
{
	//CHAR_GAIN_CARD	Card[3];	/// 결과카드(결과)
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_DISSOLVE];	/// 재료카드
	CHAR_GAIN_CARD	Dissolve;	/// 분해카드
	TRADE_CARD_DISSOLVE() { memset(this, 0, sizeof(TRADE_CARD_DISSOLVE)); };
};

//#ifdef _SERVER
// 캐릭터 파라미터들 152 BYTE
struct CHAR_DATA {
	WCHAR			szCharName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	BYTE			byAttr;							/// 속성
	BYTE			byRace;							/// 종족
	BYTE			bySex;							/// 성별
	BYTE			byHead;							///	머리
	BYTE			byHair;							/// 머리가락
	BYTE			byGrade;						/// 계급
	WORD			wLev;							/// 레벨
	int				nSkinColor;						/// 피부 색상
	int				nHairColor;						/// 머리가락 색상
	short			nHP;							/// 체력
	short			nMP;							/// 마력
	short			nAP;							/// 공격력
	short			nDP;							/// 방어력
	WORD			wLevFire;						/// 속성레벨: 불
	WORD			wLevWater;						/// 속성레벨: 물
	WORD			wLevEarth;						/// 속성레벨: 대지
	WORD			wLevWind;						/// 속성레벨: 바람
	WORD			wLevLight;						/// 속성레벨: 빛
	WORD			wLevDark;						/// 속성레벨: 어둠
	int				nZone;							/// 캐릭터 활동지역
	int				nGuild;							/// 길드번호
	int				nXP;							/// 경험치
	int				nGP;							/// 게임 포인트
	int				nPvpPoint;						/// PVP 포인트
	int				nWin;							/// 승리수
	int				nLose;							/// 패배수
	int				nMainPoint;						/// 공식전 포인트
	int				nMainWin;						/// 공식전 승리수
	int				nMainLose;						/// 공식전 패배수
	WORD			wMainGrade;						/// 공식전 계급
	WORD			wDummy;							/// 
	int				nRank;							/// 순위
	int				nToken;							/// 토큰
	int				nIdxParts[_MAX_PARTS_CARD_USE_SIZE];	/// 장착파츠의 인덱스들 : 파츠의 세부데이타에서 인덱스만 추출하여 대입한다.
	CHAR_DATA() { memset(this, 0, sizeof(CHAR_DATA)); };
};
// 캐릭터 보유 카드들
struct CHAR_CARD_DATA {
	CHAR_PARTS			Parts;						/// 파츠
	CHAR_DECK			Decks[_MAX_CHAR_DECK_SIZE];	/// 데크
	CHAR_INVENTORY		Inventory;					/// 가방
	CHAR_CARD_DATA() { memset(this, 0, sizeof(CHAR_CARD_DATA)); };
};
// 유저 정보들
struct USER_DATA {
	TCHAR				szUserID[_MAX_USER_ID_SIZE];		/// 아이디
	TCHAR				szSessionKey[_MAX_SESSION_KEY_SIZE];/// 인증키
	CHAR_DATA			Character;							/// 캐릭터 
	CHAR_CARD_DATA		CardAsset;							/// 캐릭터(카드자산)
	TRADE_CARD_PERSON   TradeCardPerson;					/// 카드거래(개인)
	TRADE_CARD_MIX		TradeCardMix;						/// 카드거래(조합)
	TRADE_CARD_PRODUCT  TradeCardProduct;					/// 카드거래(제작)
	TRADE_CARD_DISSOLVE TradeCardDissolve;					/// 카드거래(분해)
	USER_DATA() { memset(this, 0, sizeof(USER_DATA)); };
};

struct PARTY_USER_INFO
{

	WCHAR			szCharName[_MAX_CHAR_ID_SIZE];	/// 캐릭터 이름
	WORD			IsReady;
	WORD			wSid;
	PARTY_USER_INFO() { memset(this,0,sizeof(PARTY_USER_INFO)); }
};

#define MAX_ROOM_LIST	10
#define MAX_ROOM_PASSWD	10
#define MAX_ROOM_NAME	50

#define MAX_PARTY_MEMBER 4

enum EVT_TIME_TABLE_ID
{
	EVT_ID_TOKEN=1,
};

//#endif
//////////////////////////////////////////////////////////////////////////////////


#pragma pack()