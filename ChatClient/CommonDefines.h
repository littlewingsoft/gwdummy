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
#define _MAX_USER_ID_SIZE			20		// ���� �̸� ����
#define _MAX_CHAR_ID_SIZE			12		// ĳ���� �̸� ����
#define _MAX_USER_CHAR_SIZE			6		// ������ ĳ���� �ִ��
#define _MAX_NICK_NAME_SIZE			10		// user nickname max length
#define _MAX_CHAT_SIZE				256		// chat message max length
#define _MAX_SERVER_NAME			20		// server id max length
#define _MAX_DECK_NAME				10		// ��ũ�� �̸� ����
#define _MAX_PARTS_CARD_SIZE		30		// ������ ī�� �ִ��
#define _MAX_PARTS_CARD_USE_SIZE	10		// ������ ī�� ���� ����
#define _MAX_DECK_CARD_SIZE			50		// ��ũ�� ī�� �ִ��
#define _MAX_INVENTORY_CARD_SIZE	100		// ������ ī�� �ִ��
#define _MAX_STORAGE_CARD_SIZE		300		// â���� ī�� �ִ��
#define _MAX_CHAR_DECK_SIZE			6		// ĳ������ ��ũ �ִ��
#define _MAX_SYSTEM_MSG				128		// system message max length
#define _MAX_IP_SIZE				20		// IPv4 address size
#define _MAX_PWD_SIZE				16		// password string max length
#define _MAX_DEFINED_DATA			4000	// user defined data max size in packet
#define _MAX_TRADE_CARD_PERSON		5		// ī��ŷ�(����)
#define _MAX_TRADE_CARD_MIX			3		// ī��ŷ�(����)
#define _MAX_TRADE_CARD_PRODUCT		8		// ī��ŷ�(����)
#define _MAX_TRADE_CARD_DISSOLVE	8		// ī��ŷ�(����)
#define _MAX_AWARD_CARD_SIZE		10		// �������� �ִ� ī�� �ִ��
#define _MAX_BOOSTER_CARD_SIZE		50		// �ν����� ī�� ����Ʈ �ִ� ����
#define _MAX_BOOSTER_GAIN_SIZE		20		// �ν��Ϳ��� ���� �� �ִ� ī�� �ִ밳��
#define _MAX_TRADE_CARD_AMOUNT		20000	// �ѹ��� ī��ŷ��� �� �ִ� �ִ뷮
// database define values
#define _MAX_SHARED_NAME			20		// shared memory share name.
#define _MAX_DB_DSN					20		// ODBC Name
#define _MAX_DB_UID					20		// ODBC Login ID
#define _MAX_DB_PWD					20		// ODBC Login Pwd

#define _NOT_CONNECTED				65535

#define MAX_PLAYER_INROOM			10
#define MAX_TARGET_LIST				10

enum eUSER_EXIST_AREA						// ������ġ
{
	_USER_AREA_NONE = 0,
	_USER_AREA_CHAR,						/// ĳ���� ���� ����
	_USER_AREA_LOBBY,						/// ���� �κ� ����
	_USER_AREA_WAITROOM,					/// ����(������) ����
	_USER_AREA_GAMEROOM,					/// ���ӹ�(������) ����
	_USER_AREA_DUNGEON,						/// ���� ����
	_USER_AREA_MAX
};

enum eUSER_EXIST_ZONE						// ������ġ
{
	_USER_ZONE_NONE = 0,
	_USER_ZONE_RAZKA_CLOISTER = 30000001,	/// ����ī ����
	_USER_ZONE_CLIVE_MOUNTAIN,				/// Ŭ���̺� ������
	_USER_ZONE_LAVA_CAVE,					/// ��ϵ���
	_USER_ZONE_KHAUKET_ALTAR,				/// ī����Ʈ ����
	_USER_ZONE_LIEN_UNDERGROUND,			/// ���̳� ���ϼ���
	_USER_ZONE_RAZTEKA_RUINS,				/// ������ī ����
	_USER_ZONE_RAZKA_FORREST,				/// ����Ÿ ��
	_USER_ZONE_PIT_OF_ETERNITY,				/// ������ ����
	_USER_ZONE_WIND_VALLEY,					/// �ٶ��� ���
	_USER_ZONE_CHARACTER_LOBBY,				/// ĳ���� �κ�
	_USER_ZONE_CAIZA_DESERT,				/// ī���� �縷
	_USER_ZONE_WATER_ALTER,					/// ���� ����
	_USER_ZONE_LAZKA_MASON_VILLAGE			/// ����ī ��������
};

//�����Ǵ� ���.
enum eCHAR_PARTS_SLOT
{
	_CHAR_PARTS_HEAD=0,		/// [0. �Ӹ�]
	_CHAR_PARTS_ARMOR,		/// [1. ����]
	_CHAR_PARTS_PANTS,		/// [2. ����]
	_CHAR_PARTS_GLOVES,		/// [3. ��]
	_CHAR_PARTS_BOOTS,		/// [4. ��]
	_CHAR_PARTS_AMULATE,	/// [5. �����]
	_CHAR_PARTS_RING,		/// [6. ����]
	_CHAR_PARTS_BELT,		/// [7. ��Ʈ]
	_CHAR_PARTS_WEAPON_R,	/// [8. ������ ����(���ݱ�)]
	_CHAR_PARTS_WEAPON_L,	/// [9. �޼� ����(��)]
	_CHAR_PARTS_MAX,
	_CHAR_PARTS_NONE = 255,
};

//�����Ǵ� ������ Ÿ��.
enum eATTACH_PARTSTYPE
{
	_HEAD=0,				/// [0. ����]
	_ARMOR,					/// [1. ����] 
	_PANTS,					/// [2. ����] 
	_GLOVES,				/// [3. �尩] 
	_BOOTS,					/// [4. �Ź�] 
	_AMULATE,				/// [5. �����] 
	_RING,					/// [6. ����] 
	_BELT,					/// [7. ��Ʈ] 
	_RIGHT_OR_LEFT = 8,		/// [8. ������or�޼�]	(1000)	//��Ʈ ��� ����.
	_RIGHT_HAND = 9,		/// [9. ������]			(1001)
	_LEFT_HAND = 10,		/// [10. �޼�]			(1010)
	_RIGHT_AND_LEFT = 11,	/// [11. ���]			(1011)
	//���� ���߿� �߰��� ������
	//	_BOW,				/// Ȱ 
	//	_LANCE,				/// â
	_UNDEFINEDTYPE = 255
};

enum eROOM_STATE
{
	_ROOM_STATE_WAIT,
	_ROOM_STATE_GAMMING,
	_ROOM_STATE_END
};


enum eCHAR_CAED_MOVE_KIND					/// ī���̵� 
{
	_CHAR_CAED_MOVE_NONE = 0,
	_CHAR_CAED_MOVE_INVEN_TO_PARTS,			/// ����->����
	_CHAR_CAED_MOVE_PARTS_TO_INVEN,			/// ����->����
	_CHAR_CAED_MOVE_INVEN_TO_INVEN,			/// ����->����
	_CHAR_CAED_MOVE_DECK1_TO_DECK1,			/// ��ũ1->��ũ1
	_CHAR_CAED_MOVE_DECK2_TO_DECK2,			/// ��ũ2->��ũ2
	_CHAR_CAED_MOVE_DECK3_TO_DECK3,			/// ��ũ3->��ũ3
	_CHAR_CAED_MOVE_DECK4_TO_DECK4,			/// ��ũ4->��ũ4
	_CHAR_CAED_MOVE_DECK5_TO_DECK5,			/// ��ũ5->��ũ5
	_CHAR_CAED_MOVE_DECK6_TO_DECK6,			/// ��ũ6->��ũ6
	_CHAR_CAED_MOVE_INVEN_TO_DECK1,			/// ����->��ũ1
	_CHAR_CAED_MOVE_INVEN_TO_DECK2,			/// ����->��ũ2
	_CHAR_CAED_MOVE_INVEN_TO_DECK3,			/// ����->��ũ3
	_CHAR_CAED_MOVE_INVEN_TO_DECK4,			/// ����->��ũ4
	_CHAR_CAED_MOVE_INVEN_TO_DECK5,			/// ����->��ũ5
	_CHAR_CAED_MOVE_INVEN_TO_DECK6,			/// ����->��ũ6
	_CHAR_CAED_MOVE_DECK1_TO_INVEN,			/// ��ũ1->����
	_CHAR_CAED_MOVE_DECK2_TO_INVEN,			/// ��ũ2->����
	_CHAR_CAED_MOVE_DECK3_TO_INVEN,			/// ��ũ3->����
	_CHAR_CAED_MOVE_DECK4_TO_INVEN,			/// ��ũ4->����
	_CHAR_CAED_MOVE_DECK5_TO_INVEN,			/// ��ũ5->����
	_CHAR_CAED_MOVE_DECK6_TO_INVEN,			/// ��ũ6->����
	_CHAR_CAED_MOVE_PERSON_TO_PERSON,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_PERSON_TO_INVEN,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_INVEN_TO_PERSON,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_MIX_TO_MIX,				/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_MIX_TO_INVEN,			/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_INVEN_TO_MIX,			/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_PRODUCT_TO_PRODUCT,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_PRODUCT_TO_INVEN,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_INVEN_TO_PRODUCT,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_DISSOLVE_TO_INVEN,		/// ī��ŷ�: ����->����
	_CHAR_CAED_MOVE_INVEN_TO_DISSOLVE,		/// ī��ŷ�: ����->����
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

struct CHAR_GAIN_CARD			/// ���� ĳ���Ͱ� ȹ���� ī������
{
	DWORD		nIdxCard;		/// ī�� �ε���
	CARD_SERIAL	UID;			/// ī�� �ø���(ȹ��� �ο��Ǵ� ��)
	WORD		wRemainUse;		/// ���� ��� Ƚ��
	WORD		wRemainTrade;	/// ���� Ʈ���̵� Ƚ��
	WORD		wRemainTime;	/// ���� ���ð�
	WORD		wEndurance;		/// ���� ������
	short		sTransPara1;	/// ��ȭ �Ķ����1
	short		sTransPara2;	/// ��ȭ �Ķ����2
	short		sTransPara3;	/// ��ȭ �Ķ����3
	short		sFold;			/// �ߺ� ����
	CHAR_GAIN_CARD() { memset(this, 0, sizeof(CHAR_GAIN_CARD)); };
};

struct CHAR_PARTS				/// ĳ���� ����
{
	CHAR_GAIN_CARD	Card[_MAX_PARTS_CARD_SIZE];
	CHAR_PARTS() { memset(this, 0, sizeof(CHAR_PARTS)); };
};

struct CHAR_DECK				/// ĳ���� ��ũ
{
	WORD			wIndex;		/// 1~6���� ��ȣ 
	WORD			wCount;		/// ���õ� ī���� ��
	WCHAR			szName[_MAX_DECK_NAME];
	CHAR_GAIN_CARD	Card[_MAX_DECK_CARD_SIZE];
	CHAR_DECK() { memset(this, 0, sizeof(CHAR_DECK)); };
};

struct CHAR_INVENTORY			/// ĳ���� ����
{
	WORD			wCount;		/// ���õ� ī���� ��
	CHAR_GAIN_CARD	Card[_MAX_INVENTORY_CARD_SIZE];
	CHAR_INVENTORY() { memset(this, 0, sizeof(CHAR_INVENTORY)); };
};

struct TRADE_CARD_PERSON		/// ī��ŷ�����(����)
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PERSON];	/// �ŷ�ī��
	int				nGP;							/// ��������Ʈ
	TRADE_CARD_PERSON() { memset(this, 0, sizeof(TRADE_CARD_PERSON)); };
};

struct TRADE_CARD_MIX			/// ī��ŷ�����(����)
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_MIX];	/// �ŷ�ī��
	CHAR_GAIN_CARD	Mix;						/// ����ī��(���)
	TRADE_CARD_MIX() { memset(this, 0, sizeof(TRADE_CARD_MIX)); };
};

struct TRADE_CARD_PRODUCT		/// ī��ŷ�����(����)
{
	//CHAR_GAIN_CARD	Card[3];	/// ���ī��
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PRODUCT];	/// ���ī��
	CHAR_GAIN_CARD	Product;	/// ����ī��(���)
	TRADE_CARD_PRODUCT() { memset(this, 0, sizeof(TRADE_CARD_PRODUCT)); };
};

struct TRADE_CARD_DISSOLVE		/// ī��ŷ�����(����)
{
	//CHAR_GAIN_CARD	Card[3];	/// ���ī��(���)
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_DISSOLVE];	/// ���ī��
	CHAR_GAIN_CARD	Dissolve;	/// ����ī��
	TRADE_CARD_DISSOLVE() { memset(this, 0, sizeof(TRADE_CARD_DISSOLVE)); };
};

//#ifdef _SERVER
// ĳ���� �Ķ���͵� 152 BYTE
struct CHAR_DATA {
	WCHAR			szCharName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
	BYTE			byAttr;							/// �Ӽ�
	BYTE			byRace;							/// ����
	BYTE			bySex;							/// ����
	BYTE			byHead;							///	�Ӹ�
	BYTE			byHair;							/// �Ӹ�����
	BYTE			byGrade;						/// ���
	WORD			wLev;							/// ����
	int				nSkinColor;						/// �Ǻ� ����
	int				nHairColor;						/// �Ӹ����� ����
	short			nHP;							/// ü��
	short			nMP;							/// ����
	short			nAP;							/// ���ݷ�
	short			nDP;							/// ����
	WORD			wLevFire;						/// �Ӽ�����: ��
	WORD			wLevWater;						/// �Ӽ�����: ��
	WORD			wLevEarth;						/// �Ӽ�����: ����
	WORD			wLevWind;						/// �Ӽ�����: �ٶ�
	WORD			wLevLight;						/// �Ӽ�����: ��
	WORD			wLevDark;						/// �Ӽ�����: ���
	int				nZone;							/// ĳ���� Ȱ������
	int				nGuild;							/// ����ȣ
	int				nXP;							/// ����ġ
	int				nGP;							/// ���� ����Ʈ
	int				nPvpPoint;						/// PVP ����Ʈ
	int				nWin;							/// �¸���
	int				nLose;							/// �й��
	int				nMainPoint;						/// ������ ����Ʈ
	int				nMainWin;						/// ������ �¸���
	int				nMainLose;						/// ������ �й��
	WORD			wMainGrade;						/// ������ ���
	WORD			wDummy;							/// 
	int				nRank;							/// ����
	int				nToken;							/// ��ū
	int				nIdxParts[_MAX_PARTS_CARD_USE_SIZE];	/// ���������� �ε����� : ������ ���ε���Ÿ���� �ε����� �����Ͽ� �����Ѵ�.
	CHAR_DATA() { memset(this, 0, sizeof(CHAR_DATA)); };
};
// ĳ���� ���� ī���
struct CHAR_CARD_DATA {
	CHAR_PARTS			Parts;						/// ����
	CHAR_DECK			Decks[_MAX_CHAR_DECK_SIZE];	/// ��ũ
	CHAR_INVENTORY		Inventory;					/// ����
	CHAR_CARD_DATA() { memset(this, 0, sizeof(CHAR_CARD_DATA)); };
};
// ���� ������
struct USER_DATA {
	TCHAR				szUserID[_MAX_USER_ID_SIZE];		/// ���̵�
	TCHAR				szSessionKey[_MAX_SESSION_KEY_SIZE];/// ����Ű
	CHAR_DATA			Character;							/// ĳ���� 
	CHAR_CARD_DATA		CardAsset;							/// ĳ����(ī���ڻ�)
	TRADE_CARD_PERSON   TradeCardPerson;					/// ī��ŷ�(����)
	TRADE_CARD_MIX		TradeCardMix;						/// ī��ŷ�(����)
	TRADE_CARD_PRODUCT  TradeCardProduct;					/// ī��ŷ�(����)
	TRADE_CARD_DISSOLVE TradeCardDissolve;					/// ī��ŷ�(����)
	USER_DATA() { memset(this, 0, sizeof(USER_DATA)); };
};

struct PARTY_USER_INFO
{

	WCHAR			szCharName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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