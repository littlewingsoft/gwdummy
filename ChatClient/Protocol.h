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

// �� ������� �÷��� ��
enum eROOM_MODIFY_FLAG
{
	_ROOM_MOD_NAME			= 0x00000001,	// �� �̸�����
	_ROOM_MOD_PASSWD		= 0x00000002,	// �� �������
	_ROOM_MOD_LEVEL			= 0x00000004,   // �� �������Ѻ���
	_ROOM_MOD_RULE			= 0x00000008,	// �� ��Ģ����(����, ü����)
	_ROOM_MOD_MAXCNT		= 0x00000010,	// �� �ִ��ο�
	_ROOM_MOD_CURRENTCNT	= 0x00000020,	// �� �����ο�
	_ROOM_MOD_MAP			= 0x00000040,	// �� ����
	_ROOM_MOD_TOTAL			= 0x000000ff,	// ��� �׸� ����
};

// packet result error codes.
enum ePACKET_RESULT
{
	_ERR_NONE = 0,		// Error is not occured.
	_ERR_NOTREGISTERED,	// Not registered User.
	_ERR_PWD,			// Wrong Password.
	_ERR_NETWORK,		// User socket error occured.
	_ERR_PROTOCOL,		// denied for invalid protocol version
	_ERR_OCCUR,			// �����߻�
	_ERR_DISABLE,		// �Ұ���
	_ERR_LOGINED,		// �α��ν� �̹� �α��� �Ǿ�����
};

enum eRoomPassword
{
	_ROOM_PASSWORD_NO = 0,	/// ������
	_ROOM_PASSWORD_OK,		/// �����
};

enum eTRADE_CARD_MOVE
{
	_TRADE_CARD_MOVE_NONE = 0,	
	_TRADE_CARD_MOVE_INVEN,		/// ȹ���� ī�� ��������
	_TRADE_CARD_MOVE_MAILBOX,	/// ȹ���� ī�� ����������
};

enum eCHATTYPE				/// Ŀ�´�Ƽ ������
{
	_CHAT_PERSON = 0,		/// ���� �޽���(�ӼӸ�)
	_CHAT_ROOM,				/// �� �޽���
	_CHAT_CHANNEL,			/// ä�� �޽���
	_CHAT_DUNGEON,			/// ���� �޽���
	_CHAT_GUILD,			/// ��� �޽���
	_CHAT_SYSTEM,			/// �ý��� �޽���
	_CHAT_GAME_MANAGER,		/// ��� �޽���
	_CHAT_GAME_NOTIFY,		/// ��ü���� �޽���
	_CHAT_MAX
};

enum eTRADING				/// �ŷ� ���°�
{
	_TRADING_NONE = 0,		/// �ŷ��� : ����
	_TRADING_PERSON,		/// �ŷ��� : ����
	_TRADING_PERSON_READY,	/// �ŷ��� : ����(�غ�)
	_TRADING_PERSON_START,	/// �ŷ��� : ����(����)
	_TRADING_PERSON_WAIT,   /// �ŷ��� : ���ΰŷ� ��û����
	_TRADING_BOOSTER,		/// �ŷ��� : �ν���
	_TRADING_SHOP,			/// �ŷ��� : ����
	_TRADING_MIX,			/// �ŷ��� : ����
	_TRADING_PRODUCT,		/// �ŷ��� : ����
	_TRADING_DISSOLVE,		/// �ŷ��� : ����
	_TRADING_AUCTION,		/// �ŷ��� : ���
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
	_GS_PKT_LOGIN = 1,					/// ���Ӽ��� �α���
	_GS_PKT_LOGIN_RE,					/// ���Ӽ��� �α��� ����
	_GS_PKT_LOGOUT,						/// ���Ӽ��� �α׾ƿ�
	_GS_PKT_SERVER_LIST,				/// ��������Ʈ ��û
	_GS_PKT_SERVER_LIST_RE,
	_GS_PKT_CHANNEL_LIST,				/// �ش� ������ ä�� ����Ʈ ��û
	_GS_PKT_CHANNEL_LIST_RE,

	_GS_PKT_CHAR_COUNT,					/// ĳ���Ͱ���: ������ ĳ���� �ߺ�Ȯ��
	_GS_PKT_CHAR_COUNT_RE,
	_GS_PKT_MYCHAR_GET,					/// ĳ���Ͱ���: ������ ĳ���� ��û
	_GS_PKT_MYCHAR_GET_RE,
	_GS_PKT_MYCHAR_ADD,					/// ĳ���Ͱ���: ������ ĳ���� ����
	_GS_PKT_MYCHAR_ADD_RE,
	_GS_PKT_MYCHAR_DEL,					/// ĳ���Ͱ���: ������ ĳ���� ����
	_GS_PKT_MYCHAR_DEL_RE,
	_GS_PKT_MYCHAR_ENTREE,				/// �����κ�: ����
	_GS_PKT_MYCHAR_ENTREE_RE,			/// �����κ�: ��������
	_GS_PKT_MYCHAR_ENTREE_LOAD_END,		/// �����κ�: ����Ÿ �ε��Ϸ�
	_GS_PKT_USERINFO,					/// (�Ⱦ���)
	_GS_PKT_NEWUSER,					/// �����κ�: ĳ���� �߰�
	_GS_PKT_GETUSER,					/// �����κ�: ĳ���� ����Ʈ ��û
	_GS_PKT_ADDUSER,					/// �����κ�: ĳ���� ����Ʈ ����
	_GS_PKT_DELUSER,					/// �����κ�: ĳ���� ����
	_GS_PKT_MOVE,						/// �����κ�: �̵�
	_GS_PKT_STOP,						/// �����κ�: ����
	_GS_PKT_CHAT,						/// (�Ⱦ���)
	_GS_PKT_MYCHAR_PARTS_GET,			/// (�Ⱦ���)
	_GS_PKT_MYCHAR_PARTS_GET_RE,		/// ĳ���� ��������
	_GS_PKT_MYCHAR_DECKS_GET,			/// (�Ⱦ���)
	_GS_PKT_MYCHAR_DECKS_GET_RE,		/// ĳ���� ��ũ����
	_GS_PKT_MYCHAR_INVENTORY_GET,		/// (�Ⱦ���)
	_GS_PKT_MYCHAR_INVENTORY_GET_RE,	/// ĳ���� ��������
	_GS_PKT_CHAR_GET,					/// ĳ���� ����
	_GS_PKT_CHAR_GET_RE,
	_GS_PKT_CHAR_INVEN_GET,				/// ĳ���� ��������
	_GS_PKT_CHAR_INVEN_GET_RE,
	_GS_PKT_MYCHAR_CARD_MOVE,			/// �κ��丮, ����, ��ũ ���� ī�� �̵� ��Ŷ
	_GS_PKT_TEST_GAME_MESSAGE,			/// Ŭ���̾�Ʈ �׽�Ʈ�� ��Ŷ(�Ⱦ���)

	_GS_PKT_1V1_INVITE,					/// �ϴ��� ��û: 
	_GS_PKT_1V1_INVITE_RE,				/// �ϴ��� ��û: 
	_GS_PKT_1V1_RESULT,					/// �ϴ��� ��û: 
	_GS_PKT_1V1_RESULT_RE,				/// �ϴ��� ��û: 
	_GS_PKT_1V1_CANCEL,					/// �ϴ��� ��û: 
	_GS_PKT_1V1_CANCEL_RE,				/// �ϴ��� ��û: 

	_GS_PKT_CREATEROOM,					/// ��: ����
	_GS_PKT_ENTERROOM,					/// ��: ����
	_GS_PKT_CREATEROOM_RE,				/// ��:
	_GS_PKT_ENTERROOM_RE,				/// ��:
	_GS_PKT_LEAVEROOM,					/// ��: ����
	_GS_PKT_LEAVEROOM_RE,				/// ��: 
	_GS_PKT_NEW_LEADER,					/// ��: ���ο� ���� �˸�
	_GS_PKT_NEWUSER_INROOM,				/// ��: ������ ������� ������
	_GS_PKT_ADDROOM,					/// ��: ���Ͽ��� �� �߰��ϱ�
	_GS_PKT_DELROOM,					/// ��: ���Ͽ��� �� �����ϱ�
	_GS_PKT_ROOM_INVITE,				/// ����: ���ӹ� �����ʴ�
	_GS_PKT_ROOM_INVITE_REJECT,			/// ����: ���ӹ� �����ʴ� ����
	_GS_PKT_MODIFYROOM,					/// ����: �� ����
	_GS_PKT_ROOM_DEPORTATION,			/// ����: ��� �߹�
	_GS_PKT_CHG_PLAYER_SLOT,			/// ����: �÷��̾� ���� ����
	_GS_PKT_CHG_PLAYER_DECK,			/// �÷��̾� �� ����
	_GS_PKT_CHG_PLAYER_READY,			/// ����: �� �ȿ����� ���� �غ�Ϸ�
	_GS_PKT_GETROOMINFO,				/// ��: ��������
	_GS_PKT_GETROOMINFO_RE,				/// ��: 
	_GS_PKT_OBSERVER_ENTERROOM,			/// ��: ������ ����
	_GS_PKT_OBSERVER_ENTERROOM_RE,		/// ��:
	_GS_PKT_OBSERVER_LEAVEROOM,			/// ��: ������ ����
	_GS_PKT_OBSERVER_LEAVEROOM_RE,		/// ��: 
	_GS_PKT_LEVELUP,					/// ĳ���� ���� ���
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
	_GS_PKT_OBSERVER_LIST,				/// ����: ������ ����Ʈ ��û
	_GS_PKT_OBSERVER_LIST_RE,			/// ����: ������ ����Ʈ ����
	_GS_PKT_DMG,
	_GS_PKT_GAMEOVER,
	_GS_PKT_ALIVE,
	_GS_PKT_UPDATE_USER_STATS,
	_GS_PKT_UPDATE_CREATURE_STATS,
	_GS_PKT_SHUFFLE,
	_GS_PKT_SHUFFLE_RE,
	_GS_PKT_KILL_CREATURE,

	_GS_PKT_COMM_CHAT,					/// Ŀ�´�Ƽ : XML ä����Ŷ
	_GS_PKT_ZONE_ENTREE,				/// ���� ���� ��û
	_GS_PKT_ZONE_ENTREE_RE,				/// ���� ���� ����
	_GS_PKT_ZONE_ENTREE_LOAD_END,		/// ���� ���� ����Ÿ �ε��Ϸ�

	_GS_PKT_TRADE_BOOSTER_USE,			/// ī��ŷ�(�ν���) : ���
	_GS_PKT_TRADE_BOOSTER_VIEW,			/// ī��ŷ�(�ν���) : ī�庸��
	_GS_PKT_TRADE_BOOSTER_VIEW_RE,		/// ī��ŷ�(�ν���) : ī�庸��
	_GS_PKT_TRADE_BOOSTER_RESULT,		/// ī��ŷ�(�ν���) : ���	
	_GS_PKT_TRADE_PERSON_INVITE,		/// ī��ŷ�(����) : ��û
	_GS_PKT_TRADE_PERSON_ACCEPT,		/// ī��ŷ�(����) : �¶�
	_GS_PKT_TRADE_PERSON_CANCEL,		/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_PERSON_CONDITION,		/// ī��ŷ�(����) : ����(card,GP)
	_GS_PKT_TRADE_PERSON_READY,			/// ī��ŷ�(����) : �غ�
	_GS_PKT_TRADE_PERSON_START,			/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_PERSON_RESULT,		/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_SHOP_BUY,				/// ī��ŷ�(����) : ī�屸��
	_GS_PKT_TRADE_SHOP_BUY_RE,			/// ī��ŷ�(����) : ī�屸�� ���
	_GS_PKT_TRADE_SHOP_SELL,			/// ī��ŷ�(����) : ī���Ǹ�
	_GS_PKT_TRADE_SHOP_SELL_RE,			/// ī��ŷ�(����) : ī���Ǹ� ���
	_GS_PKT_TRADE_MIX_EXE,				/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_MIX_CONDITION,		/// ī��ŷ�(����) : ����(ī��, gp...)

	_GS_PKT_DEL_CARD,					/// �ڵ� ī�� ����
	_GS_PKT_ATTACK,
	_GS_PKT_ATTACK_RE,
	_GS_PKT_ATTACK_MOVE,
	_GS_PKT_ATTACK_MOVE_RE,
	_GS_PKT_DEL_CARD_RE,				/// ī�带 �������� ������.
	_GS_PKT_MISS,
	_GS_PKT_CHARSEL_ENTREE,				/// ���� ĳ���� ���� �����û
	_GS_PKT_CHARSEL_ENTREE_RE,			/// ���� ĳ���� ���� ��������
	_GS_PKT_CHARSEL_ENTREE_LOAD_END,	/// ���� ĳ���� ���� ����Ÿ �ε��Ϸ�

	_GS_PKT_ROOM_LIST,					/// ��: �渮��Ʈ ��û
	_GS_PKT_ROOM_LIST_RE,				/// ��: �渮��Ʈ ����
	
	_GS_PKT_NPC_CREATE,					//// NPC ����
	_GS_PKT_NPC_MOVE,					//// NPC �̵�
	_GS_PKT_NPC_WAIT,					//// NPC ���
	_GS_PKT_NPC_ATTACK,					//// NPC ����
	_GS_PKT_NPC_DEATH,					//// NPC ���
	_GS_PKT_USER_ATTACK_NPC,			//// ������ NPC�� ����

	_GS_PKT_TRADE_MIX_RESULT,			/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_PRODUCT_EXE,			/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_PRODUCT_CONDITION,	/// ī��ŷ�(����) : ����(ī��, gp...)
	_GS_PKT_TRADE_PRODUCT_RESULT,		/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_DISSOLVE_EXE,			/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_DISSOLVE_CONDITION,	/// ī��ŷ�(����) : ����(ī��, gp...)
	_GS_PKT_TRADE_DISSOLVE_RESULT,		/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_AUTION,				/// ī��ŷ�(���) :
	_GS_PKT_DUNGEON_ENTREE,				/// ���� ���� ��û
	_GS_PKT_DUNGEON_ENTREE_RE,			/// ���� ���� ����
	_GS_PKT_DUNGEON_ENTREE_LOAD_END,	/// ���� ���� ����Ÿ �ε��Ϸ�
	_GS_PKT_DUNGEON_LEAVE,				/// ���� ����
	_GS_PKT_DUNGEON_LEAVE_RE,			/// ���� ����
	_GS_PKT_PICKUP_CARD,				/// ī�� �ݱ�
	_GS_PKT_PICKUP_CARD_RE,				/// ī�� �ݱ�
	_GS_PKT_AWARD,						/// ���� ����
	_GS_PKT_BATTLE_SESSION,				/// pve ���� ����
	_GS_PKT_NPC_TRACE,					/// NPC����
	_GS_PKT_TRADE_SELLEDCARD_BUY,		/// ī��ŷ�(����) : �Ǹ��� ī�� �籸��
	_GS_PKT_TRADE_SELLEDCARD_BUY_RE,	/// ī��ŷ�(����) : �Ǹ��� ī�� �籸�� ���
	_GS_PKT_TEST,
	_GS_PKT_TRADE_SHOP_CANCEL,			/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_MIX_CANCEL,			/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_PRODUCT_CANCEL,		/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_DISSOLVE_CANCEL,		/// ī��ŷ�(����) : ���
	_GS_PKT_TRADE_BOOSTER_CANCEL,		/// ī��ŷ�(�ν���) : ���
	_GS_PKT_TRADE_SHOP_OPEN,			/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_MIX_OPEN,				/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_PRODUCT_OPEN,			/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_DISSOLVE_OPEN,		/// ī��ŷ�(����) : ����
	_GS_PKT_TRADE_BOOSTER_OPEN,			/// ī��ŷ�(�ν���) : ����
	_GS_PKT_MP_BEGIN,
	_GS_PKT_EP_BEGIN,
	_GS_PKT_USER_MONEY_UPDATE,
	_GS_PKT_USER_EXP_UPDATE,
	_GS_PKT_COMPENSATION,
	_GS_PKT_ACQUIRE_CARD_IN_COMBAT,
	_GS_PKT_SELECT_COMPENSATION_CARD,
	_GS_PKT_SELECT_COMPENSATION_CARD_RE,
	//��Ƽ ã�� ui
	_GS_PKT_CREATE_PARTY,				///��Ƽ ����
	_GS_PKT_CREATE_PARTY_RE,			///��Ƽ ���� ���
	_GS_PKT_INVITE_PARTY,				///��Ƽ �ʴ�
	_GS_PKT_INVITE_PARTY_RE,			///��Ƽ �ʴ� ���
	_GS_PKT_NEW_PARTY_MEMBER,			///���ε��� ��Ƽ�� //������ �մ� ��Ƽ������ ����
	_GS_PKT_ENTER_PARTY,				///��Ƽ ����
	_GS_PKT_ENTER_PARTY_RE,				///��Ƽ ���� ���
	_GS_PKT_LEAVE_PARTY,				///��Ƽ ����
	_GS_PKT_LEAVE_PARTY_RE,				///��Ƽ ���� ���
	_GS_PKT_NEW_PARTY_LEADER,			///���ο� ��Ƽ�� ����
	_GS_PKT_SEARCH_PARTY,				///��Ƽ ã��
	//
	_GS_PKT_CHG_PARTY_OPT,				//��Ƽ �ɼ� ����
	_GS_PKT_CHG_PARTY_OPT_RE,			//��Ƽ �ɼ� ����

	_GS_PKT_READY_PARTY,
	_GS_PKT_READY_PARTY_RE,

	_GS_PKT_START_PARTY,
	_GS_PKT_START_PARTY_RE,

	_GS_PKT_HOLY_PLACE,					//������ ���ҿ����� ����� ī�� ����
	_GS_PKT_HOLY_PLACE_RE,			

	_GS_PKT_RESURRECTION,				//��Ȱ ��û
	_GS_PKT_RESURRECTION_RE,			//��Ȱ ��û ó�� ���

	_GS_PKT_USER_DEATH,

	_GS_PKT_UPDATE_LIFE_PT,				//������ ������ �մ� ������ ����Ʈ ����

	_GS_PKT_UPDATE_TOKEN,				///��ū ����
	_GS_PKT_BATTLE_SESSION_END,			/// pve ���� ����
//#ifdef SUB_CHANNEL
	_GS_PKT_CHANGE_SUBCHANNEL,			//sub channel ���� ��û
//#endif
	_GS_PKT_CHG_PLAYER_DECK_RE,			/// �÷��̾� �� ���� ��� 

	_GS_PKT_CLICK_NPC,
};

//////////////////////////////////////////////////////////////////////
// Login server packet defines.
// Created by Timothy 2009.05.16.
//////////////////////////////////////////////////////////////////////
//Client->Server
struct LS_PKT_LOGIN : PACKET_BASE
{
	char	szUserID[_MAX_USER_ID_SIZE];	/// ���̵�
	char	szPwd[_MAX_PWD_SIZE];			/// �н�����
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
	char			szUserID[_MAX_USER_ID_SIZE];			/// ���̵�
	char			szSessionKey[_MAX_SESSION_KEY_SIZE];	/// ����Ű
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
	WORD		wSid;									/// ������ȣ
	WORD		wResult;								/// �����
	WORD		wChannelID;								/// ���� ä��
	WORD		wMaxUserCount;							/// ���� ä���� ���� �ִ��
	WORD		wCharCount;								/// ĳ���� ����
	char		szCharNames[_MAX_CHAR_ID_SIZE*_MAX_USER_CHAR_SIZE*2]; /// ĳ�����̸� ����Ʈ, ����: char(20)
	int			nCP;									/// ��������Ʈ
	GS_PKT_LOGIN_RE() {
		memset(this, 0x00, sizeof(GS_PKT_LOGIN_RE));
		MPID = _GS_PKT_LOGIN_RE;
		Len = sizeof(GS_PKT_LOGIN_RE);
	};
};

//Server<->Client
struct GS_PKT_LOGOUT : PACKET_BASE
{
	WORD		wSid;									/// ������ȣ
	GS_PKT_LOGOUT() {
		memset(this, 0x00, sizeof(GS_PKT_LOGOUT));
		MPID = _GS_PKT_LOGOUT;
		Len = sizeof(GS_PKT_LOGOUT);
	};
};

//Server->Client
struct	GS_PKT_USERINFO : PACKET_BASE
{
	DWORD		dwCount;								/// ������ ����
	char		pData[_MAX_DEFINED_DATA];				/// ����: ������ȣ(WORD)+ĳ����(CHAR_DATA)+������ġ(float[3])+��ǥ��ġ(float[3])
	GS_PKT_USERINFO() {
		memset(this, 0x00, sizeof(GS_PKT_USERINFO));
		MPID = _GS_PKT_USERINFO;
		Len = sizeof(GS_PKT_USERINFO);
	};
};

//Server->Client
struct GS_PKT_NEWUSER : PACKET_BASE
{
	WORD		wSid;									/// ������ȣ
	CHAR_DATA	Character;								/// ĳ����
	GS_PKT_NEWUSER() {
		memset(this, 0x00, sizeof(GS_PKT_NEWUSER));
		MPID = _GS_PKT_NEWUSER;
		Len = sizeof(GS_PKT_NEWUSER);
	};
};

//Client->Server
struct GS_PKT_GETUSER : PACKET_BASE
{
	WORD		wReqSid;								/// ��û ��ȣ
	GS_PKT_GETUSER() {
		memset(this, 0x00, sizeof(GS_PKT_GETUSER));
		MPID = _GS_PKT_GETUSER;
		Len = sizeof(GS_PKT_GETUSER);
	};
};

//Server->Client
struct GS_PKT_ADDUSER : PACKET_BASE
{
	WORD		wReqSid;								/// ������û��ȣ:��� ,  �ޱ�Ϸ�:0
	WORD		wCount;									/// ���� ������ ����
	char		pData[_MAX_DEFINED_DATA];				/// ����: ������ȣ(WORD)+ĳ����(CHAR_DATA)+������ġ(float[3])+��ǥ��ġ(float[3])
	GS_PKT_ADDUSER() {
		memset(this, 0x00, sizeof(GS_PKT_ADDUSER));
		MPID = _GS_PKT_ADDUSER;
		Len = sizeof(GS_PKT_ADDUSER);
	};
};

//Server->Client
struct GS_PKT_DELUSER : PACKET_BASE
{
	WORD		wSid;									/// �κ񿡼� ���ŵǴ� ����
	GS_PKT_DELUSER() {
		memset(this, 0x00, sizeof(GS_PKT_DELUSER));
		MPID = _GS_PKT_DELUSER;
		Len = sizeof(GS_PKT_DELUSER);
	};
};

//Server<-Client
struct GS_PKT_CHAR_COUNT : PACKET_BASE
{
	WCHAR			szName[_MAX_CHAR_ID_SIZE];			/// ĳ���� �̸� �ߺ�Ȯ��
	GS_PKT_CHAR_COUNT() {
		memset(this, 0, sizeof(GS_PKT_CHAR_COUNT));
		MPID = _GS_PKT_CHAR_COUNT;
		Len = sizeof(GS_PKT_CHAR_COUNT);
	};
};

struct GS_PKT_CHAR_COUNT_RE : PACKET_BASE
{
	WORD	wCount;										/// ��û�� ĳ������ �̸� ����
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
	WCHAR			szName[_MAX_CHAR_ID_SIZE];			/// �̸�
	GS_PKT_MYCHAR_GET() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_GET));
		MPID = _GS_PKT_MYCHAR_GET;
		Len = sizeof(GS_PKT_MYCHAR_GET);
	};
};

//Server->Client
struct GS_PKT_MYCHAR_GET_RE : PACKET_BASE
{
	CHAR_DATA		Character;							/// ĳ����
	WORD			wResult;							/// �����
	GS_PKT_MYCHAR_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_GET_RE));
		MPID = _GS_PKT_MYCHAR_GET_RE;
		Len = sizeof(GS_PKT_MYCHAR_GET_RE);
	};
};

//Server<-Client
struct  GS_PKT_MYCHAR_ADD : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];				/// �̸�
	BYTE		byAttr;									/// �Ӽ� ��,��...
	BYTE		byRace;									/// ����
	BYTE		bySex;									/// ����
	BYTE		byHead;									/// �Ӹ�(��)
	BYTE		byHair;									/// �Ӹ���
	BYTE		byDummy;
	int			nSkinColor;								/// �Ǻ� ��
	int			nHairColor;								/// �Ӹ��� ��
	GS_PKT_MYCHAR_ADD() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ADD));
		MPID = _GS_PKT_MYCHAR_ADD;
		Len = sizeof(GS_PKT_MYCHAR_ADD);
	};
};

//Server->Client
struct  GS_PKT_MYCHAR_ADD_RE : PACKET_BASE
{
	CHAR_DATA	Character;								/// ĳ����
	WORD		wResult;								/// �����
	GS_PKT_MYCHAR_ADD_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_ADD_RE));
		MPID = _GS_PKT_MYCHAR_ADD_RE;
		Len = sizeof(GS_PKT_MYCHAR_ADD_RE);
	};
};

//Server<-Client
struct  GS_PKT_MYCHAR_DEL : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];				/// ĳ���� �̸�
	GS_PKT_MYCHAR_DEL() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_DEL));
		MPID = _GS_PKT_MYCHAR_DEL;
		Len = sizeof(GS_PKT_MYCHAR_DEL);
	};
};

//Server->Client
struct  GS_PKT_MYCHAR_DEL_RE : PACKET_BASE
{
	WCHAR		szName[_MAX_CHAR_ID_SIZE];				/// ĳ���� �̸�
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
	float		fPosOrig[3];	/// ������ġ
	float		fPosGoal[3];	/// ��ǥ��ġ
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
	float		fPosStop[3];	/// ������ġ
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
	CHAR_PARTS		Parts;							/// ����
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
	CHAR_DECK		Decks[_MAX_CHAR_DECK_SIZE/3];	/// ��ũ
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
	CHAR_INVENTORY	Inventory;						/// ����
	GS_PKT_MYCHAR_INVENTORY_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_MYCHAR_INVENTORY_GET_RE));
		MPID = _GS_PKT_MYCHAR_INVENTORY_GET_RE;
		Len = sizeof(GS_PKT_MYCHAR_INVENTORY_GET_RE);
	};
};

//Server<-Client
struct  GS_PKT_CHAR_GET : PACKET_BASE
{
	WORD		wSid;			// ���� ������ȣ
	GS_PKT_CHAR_GET() {
		memset(this, 0, sizeof(GS_PKT_CHAR_GET));
		MPID = _GS_PKT_CHAR_GET;
		Len = sizeof(GS_PKT_CHAR_GET);
	};
};

//Client<-Server
struct  GS_PKT_CHAR_GET_RE : PACKET_BASE
{
	CHAR_DATA	Character;			// ���� ĳ����
	GS_PKT_CHAR_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_CHAR_GET_RE));
		MPID = _GS_PKT_CHAR_GET_RE;
		Len = sizeof(GS_PKT_CHAR_GET_RE);
	};
};

//Server<-Client
struct  GS_PKT_CHAR_INVEN_GET : PACKET_BASE
{
	WORD		wSid;				// ���� ������ȣ
	GS_PKT_CHAR_INVEN_GET() {
		memset(this, 0, sizeof(GS_PKT_CHAR_INVEN_GET));
		MPID = _GS_PKT_CHAR_INVEN_GET;
		Len = sizeof(GS_PKT_CHAR_INVEN_GET);
	};
};

//Client<-Server
struct  GS_PKT_CHAR_INVEN_GET_RE : PACKET_BASE
{
	CHAR_INVENTORY	Inventory;		// ���� ĳ���� ����
	GS_PKT_CHAR_INVEN_GET_RE() {
		memset(this, 0, sizeof(GS_PKT_CHAR_INVEN_GET_RE));
		MPID = _GS_PKT_CHAR_INVEN_GET_RE;
		Len = sizeof(GS_PKT_CHAR_INVEN_GET_RE);
	};
};

//Server<->Client
struct  GS_PKT_MYCHAR_CARD_MOVE : PACKET_BASE
{
	WORD			wSid;			// ���� ������ȣ, �޴� ��
	int				nMoveKind;		// enum eCHAR_CAED_MOVE_KIND{}; ���߿� �ϳ�, �ְ� �޴� ��
	DWORD			nIdxCard;		// ��� ī��, �޴� ��
	WORD			wOrigSlot;		// ���� ����, �ְ� �޴� ��
	WORD			wGoalSlot;		// ��ǥ ����, �ְ� �޴� ��
	WORD			wResult;		// 0�̸� ����, 0�� �ƴϸ� ����, �޴°�
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
	int		nMapIdx;	/// ������ �� �ε���
	GS_PKT_ZONE_ENTREE() {
		memset(this, 0, sizeof(GS_PKT_ZONE_ENTREE));
		MPID = _GS_PKT_ZONE_ENTREE;
		Len = sizeof(GS_PKT_ZONE_ENTREE);
	};
};
//Server->Client
struct GS_PKT_ZONE_ENTREE_RE : PACKET_BASE
{
	WORD	wResult;	/// _ERR_NONE�̸� ����
	int		nMapIdx;	/// ������ �� �ε���
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
	int		nMapIdx;	/// ������ �� �ε���
	GS_PKT_DUNGEON_ENTREE() {
		memset(this, 0, sizeof(GS_PKT_DUNGEON_ENTREE));
		MPID = _GS_PKT_DUNGEON_ENTREE;
		Len = sizeof(GS_PKT_DUNGEON_ENTREE);
	};
};
//Server->Client
struct GS_PKT_DUNGEON_ENTREE_RE : PACKET_BASE
{
	int		nMapIdx;	/// ������ �� �ε���
	WORD	wResult;	/// _ERR_NONE�̸� ����
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
	WORD	wResult;	/// _ERR_NONE�̸� ����
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
	CHAR_GAIN_CARD	GetCard;	/// �߰�ī������
	WORD			wSlot;		/// �߰�ī���� �κ��丮�� ����
	WORD			wResult;	/// ���: 0�� �ƴϸ� ����
	GS_PKT_PICKUP_CARD_RE() {
		memset(this, 0, sizeof(GS_PKT_PICKUP_CARD_RE));
		MPID = _GS_PKT_PICKUP_CARD_RE;
		Len = sizeof(GS_PKT_PICKUP_CARD_RE);
	};
};
//Server->Client
struct GS_PKT_AWARD : PACKET_BASE
{
	CHAR_DATA		Character;						/// ĳ����
	CHAR_GAIN_CARD	Card[_MAX_AWARD_CARD_SIZE];		/// �߰�ī������
	WORD			wSlot[_MAX_AWARD_CARD_SIZE];	/// �߰�ī���� �κ��丮�� ����
	WORD			wDest[_MAX_AWARD_CARD_SIZE];	/// �̵���ġ[0: ����, 1:����, 2:������], eTRADE_CARD_MOVE�� ��
	GS_PKT_AWARD() {
		memset(this, 0, sizeof(GS_PKT_AWARD));
		MPID = _GS_PKT_AWARD;
		Len = sizeof(GS_PKT_AWARD);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_INVITE : PACKET_BASE
{
	WORD	wFrom;		/// ��û��
	WORD	wDest;		/// �����
	WORD	wResult;	/// ���: 0�� �ƴϸ� ����
	GS_PKT_TRADE_PERSON_INVITE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_INVITE));
		MPID = _GS_PKT_TRADE_PERSON_INVITE;
		Len = sizeof(GS_PKT_TRADE_PERSON_INVITE);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_ACCEPT : PACKET_BASE
{
	WORD	wFrom;		/// ��û��
	WORD	wDest;		/// �����
	WORD	wIsok;		/// �¶�����: 1, �¶�����: 0
	WORD	wResult;	/// ���: 0�� �ƴϸ� ����
	GS_PKT_TRADE_PERSON_ACCEPT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_ACCEPT));
		MPID = _GS_PKT_TRADE_PERSON_ACCEPT;
		Len = sizeof(GS_PKT_TRADE_PERSON_ACCEPT);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_CANCEL : PACKET_BASE
{
	WORD			wSid;		/// �޴°�
	int				nGP;		/// �޴°�
	WORD			wDest[_MAX_TRADE_CARD_PERSON];	/// �̵���ġ[0: ����, 1:����, 2:������], eTRADE_CARD_MOVE�� ��
	WORD			wSlot[_MAX_TRADE_CARD_PERSON];	/// �޴°� (����ī�� �κ���ȣ), -1�̸� ī�����
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PERSON];	/// �޴°� (����ī��)
	WORD			wResult;	/// �޴°� (���: 0�� �ƴϸ� ����)
	GS_PKT_TRADE_PERSON_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_CANCEL));
		MPID = _GS_PKT_TRADE_PERSON_CANCEL;
		Len = sizeof(GS_PKT_TRADE_PERSON_CANCEL);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_CONDITION : PACKET_BASE
{
	WORD			wSid;		/// ������ȣ
	int				nMoveKind;	/// enum eCHAR_CAED_MOVE_KIND{}; ���߿� �ϳ�, �ְ� �޴� ��, ī���̵� ���� ��������Ʈ�� �����(nMoveKind = _CHAR_CAED_MOVE_NONE) 
	WORD			wOrigSlot;	/// ���� ����, �ְ� �޴� ��
	WORD			wGoalSlot;	/// ��ǥ ����, �ְ� �޴� ��
	int				nTradeGP;	/// �ŷ� ��������Ʈ, �ְ� �޴� ��
	int				nGP;		/// ĳ���� ��������Ʈ
	CHAR_GAIN_CARD	Card;		/// ��� ī��, �޴� ��
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����, �޴°�
	GS_PKT_TRADE_PERSON_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_CONDITION));
		MPID = _GS_PKT_TRADE_PERSON_CONDITION;
		Len = sizeof(GS_PKT_TRADE_PERSON_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_READY : PACKET_BASE
{
	WORD			wSid;		/// ������ȣ, �޴°�
	WORD			wReady;		/// �Ⱦ���(0:�غ� ��Ȱ��, 1:�غ� Ȱ��)
	GS_PKT_TRADE_PERSON_READY() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_READY));
		MPID = _GS_PKT_TRADE_PERSON_READY;
		Len = sizeof(GS_PKT_TRADE_PERSON_READY);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_START : PACKET_BASE
{
	WORD			wSid;		/// ������ȣ, �޴°�
	WORD			wStart;		/// �Ⱦ���(0:���� ��Ȱ��, 1:���� Ȱ��)
	GS_PKT_TRADE_PERSON_START() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_START));
		MPID = _GS_PKT_TRADE_PERSON_START;
		Len = sizeof(GS_PKT_TRADE_PERSON_START);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PERSON_RESULT : PACKET_BASE
{
	WORD			wDest[_MAX_TRADE_CARD_PERSON];	/// �̵���ġ[0: ����, 1:����, 2:������], eTRADE_CARD_MOVE�� ��
	WORD			wSlot[_MAX_TRADE_CARD_PERSON];	/// ���� ī���� �κ��丮 ���Թ�ȣ -1�̸� ī�����
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PERSON];	/// ���� ī��
	int				nGetGP;		/// ��������Ʈ
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_PERSON_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PERSON_RESULT));
		MPID = _GS_PKT_TRADE_PERSON_RESULT;
		Len = sizeof(GS_PKT_TRADE_PERSON_RESULT);
	};
};
//Server->Client
struct GS_PKT_TRADE_SHOP_OPEN : PACKET_BASE
{
	WORD			wResult;							/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_SHOP_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_OPEN));
		MPID = _GS_PKT_TRADE_SHOP_OPEN;
		Len = sizeof(GS_PKT_TRADE_SHOP_OPEN);
	};
};
//Server<->Client
struct GS_PKT_TRADE_SHOP_CANCEL : PACKET_BASE
{
	WORD			wResult;							/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_SHOP_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_CANCEL));
		MPID = _GS_PKT_TRADE_SHOP_CANCEL;
		Len = sizeof(GS_PKT_TRADE_SHOP_CANCEL);
	};
};
//Server<-Client
struct GS_PKT_TRADE_SHOP_BUY : PACKET_BASE
{
	DWORD			dwCardIndex;	/// ������ ī���ε���
	DWORD			dwCount;		/// ������ ī�����
	GS_PKT_TRADE_SHOP_BUY() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_BUY));
		MPID = _GS_PKT_TRADE_SHOP_BUY;
		Len = sizeof(GS_PKT_TRADE_SHOP_BUY);
	};
};
//Server->Client
struct GS_PKT_TRADE_SHOP_BUY_RE : PACKET_BASE
{
	CHAR_GAIN_CARD	Card[_MAX_INVENTORY_CARD_SIZE];		/// ������ ī���� ����
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// ������ ī���� ���潽��
	DWORD			dwSlotTotal;						/// ���Ե� ������ ����
	int				nGP;								/// ������ ���� ����Ʈ
	WORD			wResult;							/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_SHOP_BUY_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_BUY_RE));
		MPID = _GS_PKT_TRADE_SHOP_BUY_RE;
		Len = sizeof(GS_PKT_TRADE_SHOP_BUY_RE);
	};
};
//Server<-Client
struct GS_PKT_TRADE_SELLEDCARD_BUY : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// ������ �籸�Ը���� ���Թ�ȣ
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];	/// �� ���Կ��� ������ ����
	DWORD			dwSlotTotal;						/// �籸���� ������ ����
	GS_PKT_TRADE_SELLEDCARD_BUY() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SELLEDCARD_BUY));
		MPID = _GS_PKT_TRADE_SELLEDCARD_BUY;
		Len = sizeof(GS_PKT_TRADE_SELLEDCARD_BUY);
	};
};
//Server->Client
struct GS_PKT_TRADE_SELLEDCARD_BUY_RE : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// ���Ե� ���� ���Թ�ȣ
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];	/// �� ���Կ��� ������ ����
	DWORD			dwSlotTotal;						/// �籸���� ������ ����
	CHAR_GAIN_CARD	Card[_MAX_INVENTORY_CARD_SIZE];		/// �籸���� ī������
	int				nGP;								/// ������ ���� ����Ʈ
	WORD			wResult;							/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_SELLEDCARD_BUY_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SELLEDCARD_BUY_RE));
		MPID = _GS_PKT_TRADE_SELLEDCARD_BUY_RE;
		Len = sizeof(GS_PKT_TRADE_SELLEDCARD_BUY_RE);
	};
};
//Server<-Client
struct GS_PKT_TRADE_SHOP_SELL : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];	/// �Ǹ��� �κ��丮 ���Թ�ȣ
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];	/// �� ���Կ��� �Ǹ��� ����
	DWORD			dwSlotTotal;						/// �Ǹ��� ������ ����
	GS_PKT_TRADE_SHOP_SELL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_SHOP_SELL));
		MPID = _GS_PKT_TRADE_SHOP_SELL;
		Len = sizeof(GS_PKT_TRADE_SHOP_SELL);
	};
};
//Server->Client
struct GS_PKT_TRADE_SHOP_SELL_RE : PACKET_BASE
{
	WORD			wSlot[_MAX_INVENTORY_CARD_SIZE];		/// �Ǹŵ� �κ��丮 ���Թ�ȣ
	WORD			wCount[_MAX_INVENTORY_CARD_SIZE];		/// �� ���Կ��� �Ǹ��� ����
	WORD			wSelledSlot[_MAX_INVENTORY_CARD_SIZE];	/// �Ǹ��� ī�尡 �� �籸�Ը���Ʈ ���Թ�ȣ
	DWORD			dwSlotTotal;							/// �Ǹ��� ������ ����
	int				nGP;									/// �Ǹ��� ���� ����Ʈ
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����
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
	WORD			wResult;							/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_MIX_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_OPEN));
		MPID = _GS_PKT_TRADE_MIX_OPEN;
		Len = sizeof(GS_PKT_TRADE_MIX_OPEN);
	};
};
//Client->Server
struct GS_PKT_TRADE_MIX_CONDITION : PACKET_BASE
{
	int				nMoveKind;	/// enum eTRADE_CARD_MOVE{}; ���߿� �ϳ�, �ְ� �޴� ��
	WORD			wOrigSlot;	/// ���� ����, �ְ� �޴� ��
	WORD			wGoalSlot;	/// ��ǥ ����, �ְ� �޴� ��
	CHAR_GAIN_CARD	Card;		/// ��� ī��, �޴� ��
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����, �޴°�
	GS_PKT_TRADE_MIX_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_CONDITION));
		MPID = _GS_PKT_TRADE_MIX_CONDITION;
		Len = sizeof(GS_PKT_TRADE_MIX_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_MIX_CANCEL : PACKET_BASE
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_MIX];	/// �޴°�, �ŷ�ī��
	WORD			wSlot[_MAX_TRADE_CARD_MIX];	/// �޴°�, ��󽽷Թ�ȣ
	WORD			wDest[_MAX_TRADE_CARD_MIX];	/// �޴°�, eTRADE_CARD_MOVE�� ��
	WORD			wResult;					/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_MIX_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_CANCEL));
		MPID = _GS_PKT_TRADE_MIX_CANCEL;
		Len = sizeof(GS_PKT_TRADE_MIX_CANCEL);
	};
};
//Server->Client
struct GS_PKT_TRADE_MIX_RESULT : PACKET_BASE
{
	WORD			wDest;		/// �̵���ġ[0: ����, 1:����, 2:������], eTRADE_CARD_MOVE�� ��
	WORD			wSlot;		/// ��󽽷Թ�ȣ
	CHAR_GAIN_CARD	Card;		/// ������ ī��
	WORD			wResult;	/// 0�̸� ����, �޴°�
	GS_PKT_TRADE_MIX_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_MIX_RESULT));
		MPID = _GS_PKT_TRADE_MIX_RESULT;
		Len = sizeof(GS_PKT_TRADE_MIX_RESULT);
	};
};
//Client->Server
struct GS_PKT_TRADE_PRODUCT_OPEN : PACKET_BASE
{
	WORD			wResult;					/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_PRODUCT_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_OPEN));
		MPID = _GS_PKT_TRADE_PRODUCT_OPEN;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_OPEN);
	};
};
//Client->Server
struct GS_PKT_TRADE_PRODUCT_EXE : PACKET_BASE
{
	DWORD			dwCard;		/// ������ ī��
	GS_PKT_TRADE_PRODUCT_EXE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_EXE));
		MPID = _GS_PKT_TRADE_PRODUCT_EXE;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_EXE);
	};
};
//Client->Server
struct GS_PKT_TRADE_PRODUCT_CONDITION : PACKET_BASE
{
	int				nMoveKind;	/// enum eTRADE_CARD_MOVE{}; ���߿� �ϳ�, �ְ� �޴� ��
	WORD			wOrigSlot;	/// ���� ����, �ְ� �޴� ��
	WORD			wGoalSlot;	/// ��ǥ ����, �ְ� �޴� ��
	CHAR_GAIN_CARD	Card;		/// ��� ī��, �޴� ��
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����, �޴°�
	GS_PKT_TRADE_PRODUCT_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_CONDITION));
		MPID = _GS_PKT_TRADE_PRODUCT_CONDITION;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_PRODUCT_CANCEL : PACKET_BASE
{
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_PRODUCT];	/// �޴°�, ���ī��
	WORD			wSlot[_MAX_TRADE_CARD_PRODUCT]; /// �޴°�, ��󽽷Թ�ȣ
	WORD			wDest[_MAX_TRADE_CARD_PRODUCT];	/// �޴°�, eTRADE_CARD_MOVE�� ��
	WORD			wResult;					/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_PRODUCT_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_CANCEL));
		MPID = _GS_PKT_TRADE_PRODUCT_CANCEL;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_CANCEL);
	};
};
//Server->Client
struct GS_PKT_TRADE_PRODUCT_RESULT : PACKET_BASE
{
	WORD			wDest;		/// �̵���ġ[0: ����, 1:����, 2:������], eTRADE_CARD_MOVE�� ��
	WORD			wSlot;		/// ��󽽷Թ�ȣ
	CHAR_GAIN_CARD	Card;		/// ������ ī��
	int				nGP;		/// �Һ�ǰ� ���� ����Ʈ
	WORD			wResult;	/// 0�̸� ����, �޴°�
	GS_PKT_TRADE_PRODUCT_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_PRODUCT_RESULT));
		MPID = _GS_PKT_TRADE_PRODUCT_RESULT;
		Len = sizeof(GS_PKT_TRADE_PRODUCT_RESULT);
	};
};
//Client->Server
struct GS_PKT_TRADE_DISSOLVE_OPEN : PACKET_BASE
{
	WORD			wResult;					/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_DISSOLVE_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_OPEN));
		MPID = _GS_PKT_TRADE_DISSOLVE_OPEN;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_OPEN);
	};
};
//Client->Server
struct GS_PKT_TRADE_DISSOLVE_EXE : PACKET_BASE
{
	DWORD			dwCard;		/// ������ ī��
	GS_PKT_TRADE_DISSOLVE_EXE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_EXE));
		MPID = _GS_PKT_TRADE_DISSOLVE_EXE;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_EXE);
	};
};
//Client->Server
struct GS_PKT_TRADE_DISSOLVE_CONDITION : PACKET_BASE
{
	int				nMoveKind;	/// enum eTRADE_CARD_MOVE{}; ���߿� �ϳ�, �ְ� �޴� ��
	WORD			wOrigSlot;	/// ���� ����, �ְ� �޴� ��
	WORD			wGoalSlot;	/// ��ǥ ����, �ְ� �޴� ��
	CHAR_GAIN_CARD	Card;		/// ��� ī��, �޴� ��
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����, �޴°�
	GS_PKT_TRADE_DISSOLVE_CONDITION() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_CONDITION));
		MPID = _GS_PKT_TRADE_DISSOLVE_CONDITION;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_CONDITION);
	};
};
//Server<->Client
struct GS_PKT_TRADE_DISSOLVE_CANCEL : PACKET_BASE
{
	CHAR_GAIN_CARD	Dissolve;	/// �޴°�, ����ī��
	WORD			wSlot;		/// �޴°�, ��󽽷Թ�ȣ
	WORD			wDest;		/// �޴°�, eTRADE_CARD_MOVE�� ��
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_DISSOLVE_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_CANCEL));
		MPID = _GS_PKT_TRADE_DISSOLVE_CANCEL;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_CANCEL);
	};
};
//Server->Client
struct GS_PKT_TRADE_DISSOLVE_RESULT : PACKET_BASE
{
	WORD			wDest[_MAX_TRADE_CARD_DISSOLVE];/// �̵���ġ[0: ����, 1:����, 2:������], eTRADE_CARD_MOVE�� ��
	WORD			wSlot[_MAX_TRADE_CARD_DISSOLVE];/// ��󽽷Թ�ȣ
	CHAR_GAIN_CARD	Card[_MAX_TRADE_CARD_DISSOLVE];	/// ������ ī��
	int				nGP;							/// �Һ�ǰ� ���� ����Ʈ
	WORD			wResult;						/// 0�̸� ����, �޴°�
	GS_PKT_TRADE_DISSOLVE_RESULT() {
		memset(this, 0, sizeof(GS_PKT_TRADE_DISSOLVE_RESULT));
		MPID = _GS_PKT_TRADE_DISSOLVE_RESULT;
		Len = sizeof(GS_PKT_TRADE_DISSOLVE_RESULT);
	};
};
//Server<-Client
struct GS_PKT_TRADE_BOOSTER_OPEN : PACKET_BASE
{
	WORD			wResult;					/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_BOOSTER_OPEN() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_OPEN));
		MPID = _GS_PKT_TRADE_BOOSTER_OPEN;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_OPEN);
	};
};
//Server<-Client
struct GS_PKT_TRADE_BOOSTER_CANCEL : PACKET_BASE
{
	WORD			wResult;					/// 0�̸� ����, 0�� �ƴϸ� ����
	GS_PKT_TRADE_BOOSTER_CANCEL() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_CANCEL));
		MPID = _GS_PKT_TRADE_BOOSTER_CANCEL;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_CANCEL);
	};
};
//Server<->Client
struct GS_PKT_TRADE_BOOSTER_USE : PACKET_BASE
{
	WORD			wSlot;		/// ���ī���� �κ��丮 ���Թ�ȣ
	GS_PKT_TRADE_BOOSTER_USE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_USE));
		MPID = _GS_PKT_TRADE_BOOSTER_USE;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_USE);
	};
};
//Server<-Client
struct GS_PKT_TRADE_BOOSTER_VIEW : PACKET_BASE
{
	WORD			wSlot;		/// ���ī���� �κ��丮 ���Թ�ȣ
	GS_PKT_TRADE_BOOSTER_VIEW() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_VIEW));
		MPID = _GS_PKT_TRADE_BOOSTER_VIEW;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_VIEW);
	};
};
//Server->Client
struct GS_PKT_TRADE_BOOSTER_VIEW_RE : PACKET_BASE
{
	DWORD			nIdxCard[_MAX_BOOSTER_CARD_SIZE]; /// 8�ڸ� �����̸� �ڵ����̺�, Ŭ���̾�Ʈ������ ?ǥ��
	WORD			wResult;	/// 0�̸� ����, �ƴϸ� ����
	GS_PKT_TRADE_BOOSTER_VIEW_RE() {
		memset(this, 0, sizeof(GS_PKT_TRADE_BOOSTER_VIEW_RE));
		MPID = _GS_PKT_TRADE_BOOSTER_VIEW_RE;
		Len = sizeof(GS_PKT_TRADE_BOOSTER_VIEW_RE);
	};
};

//Server<->Client
struct GS_PKT_TRADE_BOOSTER_RESULT : PACKET_BASE
{
	WORD			wDest[_MAX_BOOSTER_GAIN_SIZE];	/// �̵���ġ[0: ����, 1:����, 2:������], eBOOSTER_DEST�� ��
	WORD			wSlot[_MAX_BOOSTER_GAIN_SIZE];	/// ���Թ�ȣ
	WORD			wUsedSlot;						/// ���Թ�ȣ
	CHAR_GAIN_CARD	Card[_MAX_BOOSTER_GAIN_SIZE];	/// ȹ���� ī��
	WORD			wCount;		/// ȹ���� ī���� ����
	WORD			wResult;	/// 0�̸� ����, 0�� �ƴϸ� ����, �޴°�
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
	WORD	wSid;		//��û ����� ��ȣ
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
	DWORD	idx;				/// ������ȣ
	DWORD	mapIdx;				/// �����ȣ
	WORD	MaxCnt;				/// �ִ��ο�
	WORD	CurrCnt;			/// �����ο�
	WORD	RoomLeaderIdx;		/// ���� ĳ���� ��ȣ
	WORD	GameRule;			/// ���ӷ�: ����, ü����
	WORD	LevelLimit;			/// ��������
	WORD	State;				/// �����, ������
	DWORD	Password;			/// 0:������, 1: �����
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
//	WORD	ChannelSN;				/// ����ä�ι�ȣ(�Ⱦ���)
//	WORD	SubChannelSN;			/// ����ä�ι�ȣ(�Ⱦ���)
	WORD	MaxCnt;					/// �ο�����
	WORD	LevelLimit;				/// ��������
	WORD	GameRule;				/// ���ӹ��:ü����,����
	DWORD	MapIdx;					/// ������
	WCHAR	Passwd[MAX_ROOM_PASSWD];/// ���
	WCHAR	Name[MAX_ROOM_NAME];	/// ���
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
	int Total;	// ��ü ����
	int Page;   // 0�̸� �� �޾���
	int Count;	// ���۵� ����
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
	WORD		wCount;						/// ���� �������� ����
	WORD		wOffset;					/// �д� ����
	char		pData[_MAX_DEFINED_DATA];	/// ĳ���͸��
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
	BYTE		SeatNumber;	/// �¼���ȣ
	BYTE		Type;		/// ���� Ÿ�� 0.�÷��̾� 1.������
	BYTE		DeckType;			
	BYTE		IsReady;	/// TRUE �غ�Ϸ� FALSE �����
	BYTE		PartyIdx;	/// ����ȣ
	BYTE		Dummy;
	CHAR_DATA	Character;	/// ĳ���� ����Ÿ
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
	DWORD	dwRoomIdx;	///  ���ȣ
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
	WORD wSid;					/// ���� ������ȣ
	WORD wTeam;					/// ��  ��ȣ( 0:��, 1:��, 2:������ )
	WORD wSeat;					/// �¼���ȣ(0,1,2...)
	WORD wResult;				/// 0�̸� ����
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
	WORD	wDeckIdx;			/// �� �ε���:0~5
	WCHAR	szDeckName[10];		/// �� �̸�
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
	WORD	wDeckIdx;			/// �� �ε���:0~5
	DWORD	wSid;				/// ���� ������ȣ
	WCHAR	szDeckName[10];		/// �� �̸�

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
	WORD wSid;					/// ���� ������ȣ
	WORD wState;				/// 0:�غ�ƴ� ����, 1:�غ�� ����
};

struct GS_PKT_ROOM_INVITE : PACKET_BASE
{
	GS_PKT_ROOM_INVITE()
	{
		ZeroMemory(this, sizeof(GS_PKT_ROOM_INVITE));
		MPID = _GS_PKT_ROOM_INVITE;
		Len = sizeof(GS_PKT_ROOM_INVITE);
	}
	WORD	wRoomreader;	/// ���� ������ȣ
	int		nRoomIdx;		/// �� ������ȣ
};

struct GS_PKT_ROOM_INVITE_REJECT : PACKET_BASE
{
	GS_PKT_ROOM_INVITE_REJECT()
	{
		ZeroMemory(this, sizeof(GS_PKT_ROOM_INVITE_REJECT));
		MPID = _GS_PKT_ROOM_INVITE_REJECT;
		Len = sizeof(GS_PKT_ROOM_INVITE_REJECT);
	}
	WORD	wRoomreader;	/// ���� ������ȣ
	int		nRoomIdx;		/// �� ������ȣ
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
	DWORD				Flag;						/// ���� �÷���(eROOM_MODIFY_FLAG�� ��)
	CREATE_ROOM_INFO	Room;						/// ���� ��
	WCHAR				Passwd[MAX_ROOM_PASSWD];	/// �� ���, ��� ����,������ ��츸 �ִ°�
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
	BYTE SlotIdx;				//������ ���� ��ȣ
	BYTE Dummy;
	WORD TargetwSid;			//Ÿ�� ������ȣ
	BYTE TargetSlotIdx[MAX_TARGET_LIST];		//Ÿ�� ����Ʈ  ������� ���� Ÿ���� ������� -1(127)�� �־��ش�.
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

	int m_StatusMore;		//�����̻�

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
	WORD Activate;		// 1 : Ȱ��ȭ 0 : ��Ȱ��ȭ
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
	WORD InitMP;	//�ʱ� ������
	WORD Period;	//�ֱ�(��)
	double Quantity;	//�ö󰡴� ����
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
	WORD InitEP;	//�ʱ� ������
	WORD Period;	//�ֱ�(��)
	WORD Quantity;	//�ö󰡴� ����
};
//���� �� ȹ��
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
//���� ����ġ ȹ��
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
//���� ī�� ����
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
//���� ī�� ���� ���
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
//����â ���� ��Ŷ 
struct GS_PKT_COMPENSATION : PACKET_BASE
{
	GS_PKT_COMPENSATION()
	{
		memset(this, 0x00, sizeof(GS_PKT_COMPENSATION));
		MPID = _GS_PKT_COMPENSATION;
		Len = sizeof(GS_PKT_COMPENSATION);
	}

	WORD wSid;
	WORD SelectCount;		//���� ���� Ƚ��.

	WORD CounterBlewCnt;
	WORD CriticalCnt;
	DWORD RemainDeckCnt;
	DWORD ClearTime;
	DWORD AcquireGold;
	DWORD AcquireExp;

};
//���͸� �׿� ȹ���ϴ� ī��
struct GS_PKT_ACQUIRE_CARD_IN_COMBAT : PACKET_BASE
{
	GS_PKT_ACQUIRE_CARD_IN_COMBAT()
	{
		memset(this, 0x00, sizeof(GS_PKT_ACQUIRE_CARD_IN_COMBAT));
		MPID = _GS_PKT_ACQUIRE_CARD_IN_COMBAT;
		Len = sizeof(GS_PKT_ACQUIRE_CARD_IN_COMBAT);
	}
	WORD SrcSid;		//ī�� �Դ� ���
	WORD TargetSid;		//���͸� ���� ���
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
	WORD wSid;			// ���� ������ȣ
	WORD wLev;			// ������ ��� ��ġ
};

struct GS_PKT_GETROOMINFO : PACKET_BASE
{
	GS_PKT_GETROOMINFO()
	{
		memset(this, 0x00, sizeof(GS_PKT_GETROOMINFO));
		MPID = _GS_PKT_GETROOMINFO;
		Len = sizeof(GS_PKT_GETROOMINFO);
	}
	int nRoomIdx;		// ������ ��� ��ġ
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
	WORD				wSid;		//��Ƽ�� ��ȣ
	WORD				wResult;	//�����
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


	DWORD				PartyIdx;		//��Ƽ��ȣ
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

	DWORD				nToken;		//���� ��ū ����
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
	WORD IsReady;		//0 : �غ�ʵ� 1: �غ��
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
	_MW_PKT_USER_LOGIN = 400,	/// �α���
	_MW_PKT_USER_LOGIN_RE,
	_MW_PKT_USER_LOGOUT,		/// �α׾ƿ�
	_MW_PKT_USER_LOGOUT_RE,
	_MW_PKT_USER_SAVE,			/// ���� ����(�Ⱦ���)
	_MW_PKT_USER_SAVE_RE,		/// ���� ����(�Ⱦ���)
	_MW_PKT_CHAR_CNT,			/// ĳ���� ����
	_MW_PKT_CHAR_CNT_RE,
	_MW_PKT_MYCHAR_GET,			/// �� ĳ���� ���
	_MW_PKT_MYCHAR_GET_RE,
	_MW_PKT_MYCHAR_ADD,			/// �� ĳ���� �߰�
	_MW_PKT_MYCHAR_ADD_RE,
	_MW_PKT_MYCHAR_DEL,			/// �� ĳ���� ����
	_MW_PKT_MYCHAR_DEL_RE,
	_MW_PKT_MYCHAR_ENTREE,		/// �� ĳ���� ��������
	_MW_PKT_MYCHAR_ENTREE_RE,
	_MW_PKT_MYCHAR_DECK_GET,	/// �� ���(�Ⱦ���)
	_MW_PKT_MYCHAR_DECK_GET_RE, /// �� ���(�Ⱦ���)
	_MW_PKT_MYCHAR_INVENTORY,	/// �κ��丮 ���(�Ⱦ���)
	_MW_PKT_MYCHAR_INVENTORY_RE,/// �κ��丮 ���(�Ⱦ���)
	_MW_PKT_CHARSEL_ENTREE,		/// ĳ���� ������ ����
	_MW_PKT_CHARSEL_ENTREE_RE,	
	_MW_PKT_DUNGEON_LEAVE,		/// ���� ����(�Ⱦ���)
	_MW_PKT_DUNGEON_LEAVE_RE,	/// ���� ����(�Ⱦ���)
	_MW_PKT_CHAR_SAVE,			/// ĳ���� ����
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
	WCHAR szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
	MW_PKT_MYCHAR_DEL_RE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_DEL_RE));
		MPID = _MW_PKT_MYCHAR_DEL_RE;
		Len = sizeof(MW_PKT_MYCHAR_DEL_RE);
	};
};

struct MW_PKT_MYCHAR_ENTREE : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
	MW_PKT_MYCHAR_ENTREE_RE() {
		memset(this, 0, sizeof(MW_PKT_MYCHAR_ENTREE_RE));
		MPID = _MW_PKT_MYCHAR_ENTREE_RE;
		Len = sizeof(MW_PKT_MYCHAR_ENTREE_RE);
	};
};

struct MW_PKT_CHARSEL_ENTREE : PACKET_BASE
{
	unsigned short	wSid;
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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
	WCHAR			szName[_MAX_CHAR_ID_SIZE];	/// ĳ���� �̸�
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
	WCHAR	szUserID[_MAX_USER_ID_SIZE];	/// ���̵�
	WCHAR	szCharName[_MAX_CHAR_ID_SIZE];			/// �н�����

};
#endif
/////////////////////////////////////////////////////////////////////// MIDDLEWARE PROTOCOL

#pragma pack()
