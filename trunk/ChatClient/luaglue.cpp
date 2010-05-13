#include "stdafx.h"
#include "afxwin.h"
#include "resource.h"

//#include "ChatClientDlg.h"
extern map<WORD,CHAR_DATA> g_UserMap;

void _print(const char* szMsg )
{
	CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();
	if( pkMain == 0 )
		return;

	if( szMsg == 0 )
		return;

	pkMain->m_ChatList.AddString( szMsg );
	//pkMain->m_ChatList.AddString( "\n" );
	pkMain->m_ChatList.SetTopIndex( pkMain->m_ChatList.GetCount()-1);

}

// CChatClientDlg 메시지 처리기
void show_error(const char* szError )
{
	OutputDebugString( szError );
	OutputDebugString( "\n" );
}


void EncodeString(wstring& wstr , const string& str )
{
	wchar_t  wszBuffer[255];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str.c_str(), str.length()+1, wszBuffer, 255);
	
	wstr = wszBuffer;
}

namespace luaGlue
{
	lua_State* g_hLua =0;
	DWORD timerID=0;
	void send_move(lua_tinker::table obj )
	{
		GS_PKT_MOVE pkt;
		pkt.Len = sizeof( pkt );
		pkt.FROM = _FROM_CLIENT;
		pkt.fPosOrig[0] = obj.get<float>("orgx");
		pkt.fPosOrig[1] = obj.get<float>("orgy");
		pkt.fPosOrig[2] = obj.get<float>("orgz");

		pkt.fPosGoal[0]= obj.get<float>("destx");;
		pkt.fPosGoal[1]= obj.get<float>("desty");;
		pkt.fPosGoal[2]= obj.get<float>("destz");;

		pkt.wFlag = 21;

		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();
		pkt.wSid = pkMain->m_wSid;
		pkMain->m_ASocket.SendData( &pkt, pkt.Len );
	}

	void send_makeRoom(const char* szRoomName)
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();
		GS_PKT_CREATEROOM pkt;
		pkt.FROM = _FROM_CLIENT;
/*
	WORD	MaxCnt;					/// 인원제한
	WORD	LevelLimit;				/// 레벨제한
	WORD	GameRule;				/// 게임방식:체력전,덱전
	DWORD	MapIdx;					/// 전투맵
	WCHAR	Passwd[MAX_ROOM_PASSWD];/// 비번
	WCHAR	Name[MAX_ROOM_NAME];	/// 방명
*/
		pkt.MaxCnt = 4;
		pkt.LevelLimit = 5;
		pkt.GameRule = 0;
		pkt.MapIdx = 30000004;

		int ret=sizeof( pkt.MaxCnt );
		ret += sizeof( pkt.LevelLimit );
		ret += sizeof( pkt.GameRule );
		ret += sizeof( pkt.MapIdx );
		ret += sizeof( pkt.Name );
		ret += sizeof( pkt.Passwd );
		ret += sizeof( pkt.FROM );
		ret += sizeof( pkt.Len );
		ret += sizeof( pkt.MPID );
		ret += sizeof( pkt.SPID );
		
		//memset( pkt.Passwd,0, sizeof(wchar_t )*MAX_ROOM_PASSWD);
		wcscpy_s( pkt.Name, MAX_ROOM_NAME, L"test방"  );

//		wstring wst;
//		EncodeString(wst , szRoomName );
//		copy(	wst.begin(), wst.end(), pkt.Name );
		pkMain->m_ASocket.SendData( &pkt, pkt.Len );
#pragma pack(push)
	}


	void send_startGame()
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();

		GS_PKT_START_GAME pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.Len = sizeof( pkt );
		pkMain->m_ASocket.SendData( &pkt,sizeof( pkt ) );
	}

	void send_loadinComplete()
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	

		{
		GS_PKT_RESOURCE_COMPLETE pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.Len = sizeof( pkt );
		pkMain->m_ASocket.SendData( &pkt,sizeof( pkt ) );
		}

		{
			GS_PKT_SCENE_COMPLETE pkt;
			pkt.FROM = _FROM_CLIENT;
			pkMain->m_ASocket.SendData( &pkt,sizeof( pkt ) );
		}
	}

	void send_PartySearch()
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	

		GS_PKT_SEARCH_PARTY pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.DungeonMapIdx = 30000014;
		pkt.SenarioIdx = 0;
		
		pkMain->m_ASocket.SendData( &pkt, sizeof( pkt ) );		
	}

	void send_PartyCreate()
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	

		GS_PKT_CREATE_PARTY pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.wSid = pkMain->m_wSid;
		
		pkMain->m_ASocket.SendData( &pkt, sizeof( pkt ) );
	}
	void send_PartyEnter(int partyIndex)
	{
		GS_PKT_ENTER_PARTY pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.PartyIdx = partyIndex;

		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	
		pkMain->m_ASocket.SendData( &pkt, sizeof( pkt ) );
		
	}

	void send_ClickNpc(int tbId)
	{
		GS_PKT_CLICK_NPC pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.TableID = tbId;
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	
		pkMain->m_ASocket.SendData( &pkt, sizeof( pkt ) );

	}
	void send_PartyReady()
	{
		GS_PKT_READY_PARTY pkt;
		pkt.FROM = _FROM_CLIENT;
		pkt.Len = sizeof( pkt );

		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	
		pkMain->m_ASocket.SendData( &pkt, sizeof( pkt ) );
	}

	void send_requestRoomList()
	{
		//방목록 요구함.
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	

		GS_PKT_ROOM_LIST pkt;
		pkt.FROM = _FROM_CLIENT;
		pkMain->m_ASocket.SendData(&pkt,sizeof(pkt) );

	}

	void Volume( float fVol )
	{
		
	}

	/*
		enum eCHATTYPE				/// 커뮤니티 종류값
		{
			_CHAT_PERSON = 0,		/// 개인 메시지(귓속말)
			_CHAT_ROOM,				/// 방 메시지
			_CHAT_CHANNEL,			/// 채널 메시지
			_CHAT_PARTY,			/// 파티 메시지
			_CHAT_GUILD,			/// 길드 메시지
			_CHAT_SYSTEM,			/// 시스템 메시지
			_CHAT_GAME_MANAGER,		/// 운영자 메시지
			_CHAT_GAME_NOTIFY,		/// 전체공지 메시지
			_CHAT_MAX
		};
	*/
	void send_chatmsg( int msgType, char* msg )//const char* msg
	{
		CChatClientDlg* pkMain = (CChatClientDlg*) theApp.GetMainWnd();	
		GS_PKT_COMM_CHAT pkt;
		pkt.FROM =_FROM_CLIENT;
		pkt.Len = sizeof( pkt );
		pkt.wType = msgType;

		wchar_t wszChat[256];
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, 
			(const char*)msg,strlen(msg)+1, wszChat, 255);

		swprintf_s( pkt.szCmd, _MAX_CHAT_SIZE, 
			L"<CHAT from=\"%s\" to=\"\" type=\"%d\">%s</CHAT>", 
			g_UserMap[ pkMain->m_wSid ].szCharName, 
			_CHAT_ROOM, wszChat );

		pkMain->m_ASocket.SendData(&pkt, pkt.Len);	
	}

	void SetTimer(int _timerID,int elapsedTime )
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	
		pkMain->SetTimer( _timerID,elapsedTime,0 );
		timerID = _timerID;
	}

	int MySID()
	{
		CChatClientDlg* pkMain= (CChatClientDlg*) theApp.GetMainWnd();	
		return pkMain->m_wSid;
	}

	bool getTable(lua_tinker::table tb)
	{
		if( 0 )
		{
			lua_tinker::enum_stack(luaGlue::g_hLua );
			lua_tinker::pop<lua_tinker::table>(luaGlue::g_hLua );
			lua_tinker::enum_stack(luaGlue::g_hLua );
			return false;
		}
		tb.set("name","jjm");
		tb.set("age", 31);
		
		return true;
		//lua_tinker::call<void,lua_tinker::table>( luaGlue::g_hLua, "push_table",tb);
	}

	struct init_t
	{
		init_t()
		{
			g_hLua = lua_open();
			luaopen_string(g_hLua);
			luaL_openlibs(g_hLua);
		}

		~init_t()
		{
			lua_close( g_hLua );
		}
	};

	static init_t tt;

	void setting()
	{
		// Lua 기본 함수들을 로드한다.

		lua_tinker::def( g_hLua, "ods", show_error);
		
		lua_tinker::def( g_hLua, "_ALERT", show_error);
		lua_tinker::def( g_hLua, "print", _print );
		lua_tinker::def( g_hLua, "send_move", send_move );	
		lua_tinker::def( g_hLua, "send_makeRoom", send_makeRoom );	
		lua_tinker::def( g_hLua, "send_startGame", send_startGame );	
		lua_tinker::def( g_hLua, "send_loadinComplete", send_loadinComplete );	
		lua_tinker::def( g_hLua, "send_requestRoomList", send_requestRoomList );	
		lua_tinker::def( g_hLua, "send_chatmsg", send_chatmsg );	

		
		lua_tinker::def( g_hLua, "send_PartySearch", send_PartySearch );	
		lua_tinker::def( g_hLua, "send_PartyCreate", send_PartyCreate );	
		lua_tinker::def( g_hLua, "send_PartyEnter", send_PartyEnter );	
		lua_tinker::def( g_hLua, "send_PartyReady", send_PartyReady );	
		lua_tinker::def( g_hLua, "send_ClickNpc", send_ClickNpc );	
		

		lua_tinker::def( g_hLua, "SetTimer", SetTimer );
		lua_tinker::def( g_hLua, "MySID",MySID );

		lua_tinker::def( g_hLua, "getTable",getTable );

		lua_tinker::dofile( luaGlue::g_hLua, theApp.m_lpCmdLine  );
		//lua_tinker::enum_stack( luaGlue::g_hLua);
	}


}

