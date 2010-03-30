#include "stdafx.h"
#include "CHatClientDlg.h"
#include "luaglue.h"

map< WORD, CHAR_DATA> g_UserMap;


void CChatClientDlg::Process(PACKET_BASE* pkPacket)
{
	switch(pkPacket->MPID) 
	{
	case _LS_PKT_LOGIN_RE:
		{
			LS_PKT_LOGIN_RE* pLoginRe = (LS_PKT_LOGIN_RE*)pkPacket;
			if(pLoginRe->wResult != 0 ) 
			{
				if(AfxMessageBox("unregistered id or wrong password.")==IDOK) 
				{
					::PostMessage(this->m_hWnd, WM_USERCLOSE, NULL, NULL);
					break;
				}
			}
			m_szSession = pLoginRe->szSessionKey;

			LS_PKT_SERVER_LIST reqPkt;
			reqPkt.Len = sizeof( reqPkt );
			reqPkt.FROM = _FROM_CLIENT;
			m_ASocket.SendData(&reqPkt, reqPkt.Len);

			stringstream ss;
			ss<<"ID: " <<lua_tinker::get<char*>( luaGlue::g_hLua,"ID") << 
				"PASS: "<<lua_tinker::get<char*>( luaGlue::g_hLua,"PASS");
			this->m_ChatList.AddString(ss.str().c_str() );
			this->m_ChatList.AddString("login ok" );
			
			SetTimer( 1024,1000,0);
		}
		break;

	case _LS_PKT_SERVER_LIST_RE:
		{
			LS_PKT_SERVER_LIST_RE* pkt = (LS_PKT_SERVER_LIST_RE*) pkPacket;

			for( size_t n=0; n< pkt->wCount; n++)
			{
				int offset = n*_MAX_SERVER_NAME*2;
				wstring  szServerName = (const wchar_t*) (&pkt->pData[ offset] );
					
					int ret = lua_tinker::get<int>( luaGlue::g_hLua, "GAMESERVER_INDEX");
					if( ret == n )
					{
						LS_PKT_CHANNEL_LIST pkt;
						pkt.FROM = _FROM_CLIENT;
						wcscpy_s( pkt.szServerName , _MAX_SERVER_NAME, szServerName.c_str() );
						this->m_ASocket.SendData( &pkt, pkt.Len );
						std::wstringstream ws;
						ws <<  L"server: " << szServerName;

						char dst[64]={0,};
						int retLength = WideCharToMultiByte(CP_ACP, 0, 
						ws.str().c_str(), ws.str().length(), dst, 64, 0,0);

						this->m_ChatList.AddString( dst );
						break;
					}
			}
			
			
		}
		break;

	case _LS_PKT_CHANNEL_LIST_RE:
		{
			LS_PKT_CHANNEL_LIST_RE* pkt = (LS_PKT_CHANNEL_LIST_RE*) pkPacket;
			for( size_t n=0; n< pkt->wCount; n++)
			{
				int offset = n* sizeof( CHANNEL_INFO ) ;
				CHANNEL_INFO* pkChannel = (CHANNEL_INFO*) (&pkt->pData[ offset]);				


				if( lua_tinker::get<int>( luaGlue::g_hLua, "GAMECHANNEL_INDEX")== n )
				{
					std::wstringstream ws;
					ws <<  L"channel: " << pkChannel->szName ;

					char dst[64]={0,};
					int retLength = WideCharToMultiByte(CP_ACP, 0, 
						ws.str().c_str(), ws.str().length(), dst, 64, 0,0);
					this->m_ChatList.AddString( dst );


					char* ip = pkChannel->szIP;//szChannelIP;
					int port =pkChannel->wPort;

					m_ASocket.CloseSocket();
					Sleep(500);
					m_ASocket.ConnectSocket( ip, port );

					int count = 0;
					while( !m_ASocket.IsConnected() ) 
					{
						Sleep(100);
						count++;
						if( count > 10) 
						{
							m_ChatList.AddString( "Dont connect game server" );
							return ;
						}
					}

					GS_PKT_LOGIN pkt;
					pkt.Len = sizeof(GS_PKT_LOGIN);
					pkt.FROM = _FROM_CLIENT;
					pkt.wProtocolVersion = _PROTOCOL_VERSION;
					strcpy_s( pkt.szSessionKey, _MAX_SESSION_KEY_SIZE, (const char*)this->m_szSession.c_str() );
					strcpy_s( pkt.szUserID, _MAX_USER_ID_SIZE, lua_tinker::get<char*>( luaGlue::g_hLua,"ID") );
					if(m_ASocket.SendData(&pkt, pkt.Len)==false) 
					{
						m_ChatList.AddString( "connot Send Login Packet " );
					}

					break;
				}
			}
		}
		break;

	case _GS_PKT_LOGIN_RE:
		{
			GS_PKT_LOGIN_RE* pkt = (GS_PKT_LOGIN_RE*) pkPacket;
			this->m_wSid = pkt->wSid;
			m_ChatList.AddString( "connected and login game server" );

			const char* szNick = lua_tinker::get<const char*>( luaGlue::g_hLua, "NICK" );
			if( pkt->wCharCount > 0 )
			{
				for( int offsetName = 0; offsetName< pkt->wCharCount ; offsetName++)
				{
					int offest= (offsetName*_MAX_CHAR_ID_SIZE*2);

					wstring szWNick = ( (wchar_t*)&pkt->szCharNames[ offest ] );
					char dst[64]={0,};
					int retLength = WideCharToMultiByte(CP_ACP, 0, 
						szWNick.c_str(), szWNick.length(), dst, 64, 0,0);

					if( strcmp( szNick, dst) == 0 )
					{
						//요청을 보내자.
						GS_PKT_MYCHAR_GET get;
						get.FROM = _FROM_CLIENT;
						get.Len = sizeof( get );
						wcscpy_s( get.szName, _MAX_CHAR_ID_SIZE,  szWNick.c_str() );
						m_ASocket.SendData( &get, sizeof( get ) );
						//m_ChatList.AddString( szNick );
						break;
					}
				}
			}
			else
				m_ChatList.AddString( "there is no Avatar" );
		}
		break;

	case _GS_PKT_LOGOUT:
	{
		GS_PKT_LOGOUT* pkt = (GS_PKT_LOGOUT* )pkPacket;
		map<WORD,CHAR_DATA>::iterator it=g_UserMap.find(pkt->wSid);
		if( it != g_UserMap.end() )
		{
			g_UserMap.erase( it );
			RefreshUserList();
		}
	}
	break;


	case _GS_PKT_ADDUSER:
		{
			GS_PKT_ADDUSER* pkt = (GS_PKT_ADDUSER*)pkPacket;
			WORD wSid;
			CHAR_DATA kData;
			int pos=0;
			int offset = sizeof(CHAR_DATA);
			for( int n=0; n<pkt->wCount; n++)
			{
				memcpy(&wSid, pkt->pData+pos, 2); pos += 2;
				memcpy(&kData, pkt->pData+pos, offset); pos += offset;
				//memcpy( fpos, pkt->pData+pos, 12); 
				//memcpy( goal, pkt->pData+pos, 12); pos += 12;
				pos += 24;

				g_UserMap[ wSid ] =  kData;
			}

			RefreshUserList();
			
			

			if( pkt->wReqSid != 0 )
			{
				//요청다시해야함.
				GS_PKT_GETUSER	send;
				send.Len = sizeof(GS_PKT_GETUSER);
				send.FROM = _FROM_CLIENT;
				send.wReqSid = pkt->wReqSid;
				m_ASocket.SendData( &send, send.Len );
			}else
			{
				//모든 요청이 다끝났으므로 OnEntryLobby 호출하면됨.
				lua_tinker::call<void>( luaGlue::g_hLua, "OnEntryLobby" );
			}

		}
		break;

	case _GS_PKT_NEWUSER:
		{
			GS_PKT_NEWUSER* pkt = (GS_PKT_NEWUSER*)pkPacket;
			if( m_wSid == pkt->wSid )
			{
				GS_PKT_GETUSER	send;
				send.Len = sizeof(GS_PKT_GETUSER);
				send.FROM = _FROM_CLIENT;
				send.wReqSid = 1;
				m_ASocket.SendData( &send, send.Len );
			}

			g_UserMap[ pkt->wSid ] = pkt->Character;

			char dst[64]={0,};
			int retLength = WideCharToMultiByte(CP_ACP, 0, 
			pkt->Character.szCharName, _MAX_CHAR_ID_SIZE, dst, 64, 0,0);

			stringstream ss;
			ss<< "NewUser: " << dst;
			m_ChatList.AddString( ss.str().c_str() );
			
			lua_tinker::call<void, char* >( luaGlue::g_hLua, "OnAddUser", dst);

			RefreshUserList();
		}
		break;

	case _GS_PKT_NEWUSER_INROOM:
		{
			GS_PKT_NEWUSER_INROOM* pkt = (GS_PKT_NEWUSER_INROOM* )pkPacket;
			g_UserMap[ pkt->PlayerInfo.wSid ] = pkt->PlayerInfo.Character;
			RefreshUserList();

			char dst[64]={0,};
			int retLength = WideCharToMultiByte(CP_ACP, 0, 
			pkt->PlayerInfo.Character.szCharName, _MAX_CHAR_ID_SIZE, dst, 64, 0,0);

			lua_tinker::call<void, char* >( luaGlue::g_hLua, "OnNewUserInRoom", dst);
		}
		break;

	case _GS_PKT_GAMEOVER:
		{
			GS_PKT_LEAVEROOM pkt;
			pkt.FROM = _FROM_CLIENT;
			pkt.Len = sizeof( pkt );
			m_ASocket.SendData( &pkt, sizeof( pkt ) );

		}
		break;

	case _GS_PKT_LEAVEROOM_RE:
		{
			GS_PKT_LEAVEROOM_RE* pkt = (GS_PKT_LEAVEROOM_RE*) pkPacket;
			map<WORD,CHAR_DATA>::iterator it = g_UserMap.find( pkt->wSid );
			if( it != g_UserMap.end() )
				g_UserMap.erase( it );

			RefreshUserList();			
		
			if( m_wSid == pkt->wSid )
			{
				GS_PKT_MYCHAR_ENTREE tmpPkt;
				tmpPkt.FROM= _FROM_CLIENT;
				tmpPkt.Len = sizeof( tmpPkt );
				wcscpy_s( tmpPkt.szName, _MAX_CHAR_ID_SIZE, g_UserMap[m_wSid].szCharName  );
				m_ASocket.SendData( &tmpPkt, sizeof( tmpPkt ) );
			}
		}
		break;


	case _GS_PKT_MYCHAR_GET_RE:
		{
			GS_PKT_MYCHAR_GET_RE* pkt= (GS_PKT_MYCHAR_GET_RE*) pkPacket;
			if( pkt->wResult == 0  )
			{
				GS_PKT_MYCHAR_ENTREE tmpPkt;
				tmpPkt.FROM= _FROM_CLIENT;
				tmpPkt.Len = sizeof( tmpPkt );
				wcscpy_s( tmpPkt.szName, _MAX_CHAR_ID_SIZE, pkt->Character.szCharName  );
				m_ASocket.SendData( &tmpPkt, sizeof( tmpPkt ) );				
				break;
			}
		}
		break;

	case _GS_PKT_MYCHAR_ENTREE_RE:
		{
			GS_PKT_MYCHAR_ENTREE_RE* pkt=(GS_PKT_MYCHAR_ENTREE_RE*)pkPacket;
			if( pkt->wResult == 0 )
			{
				GS_PKT_MYCHAR_ENTREE_LOAD_END tmp;
				tmp.FROM= _FROM_CLIENT;
				tmp.Len = sizeof( tmp );
				m_ASocket.SendData( &tmp, sizeof( tmp ) );	
			}
		}
		break;

	case _GS_PKT_CHG_PLAYER_READY:
		{
			GS_PKT_CHG_PLAYER_READY* pkt = (GS_PKT_CHG_PLAYER_READY*)pkPacket;

			char dst[64]={0,};
			int retLength = WideCharToMultiByte(CP_ACP, 0, 
			g_UserMap[pkt->wSid].szCharName, _MAX_CHAR_ID_SIZE, dst, 64, 0,0);

			lua_tinker::call<void,char*, int>(luaGlue::g_hLua,"OnReadyChange",
				                              dst, pkt->wState );
		}
		break;

	case _GS_PKT_COMM_CHAT:
		{
			GS_PKT_COMM_CHAT* pkt = (GS_PKT_COMM_CHAT*) pkPacket;
			

			char dst[256]={0,};
			int retLength = WideCharToMultiByte(CP_ACP, 0, 
			pkt->szCmd, _MAX_CHAT_SIZE*2, dst, 256, 0,0);

			lua_tinker::call<void,char*>(luaGlue::g_hLua,"OnChat", dst );		
		}
		break;
	case _GS_PKT_CREATEROOM_RE:
		{
		
		}
		break;

	case _GS_PKT_ROOM_LIST_RE:
		{
			GS_PKT_ROOM_LIST_RE* pkt = (GS_PKT_ROOM_LIST_RE*)pkPacket;
		//int Total;	// 전체 갯수
		//int Page;   // 0이면 다 받았음
		//int Count;	// 전송된 갯수
		//CREATE_ROOM_INFO RoomList[MAX_ROOM_LIST];			

			/*
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
			*/

			
			for( int n=0 ; n< pkt->Count; n++)
			{
				lua_tinker::table RoomInfo( luaGlue::g_hLua );
				RoomInfo.set("idx", pkt->RoomList[n].idx );
				RoomInfo.set("mapIdx", pkt->RoomList[n].mapIdx);
				RoomInfo.set("MaxCnt", pkt->RoomList[n].MaxCnt);
				RoomInfo.set("CurrCnt", pkt->RoomList[n].CurrCnt);
				RoomInfo.set("RoomLeaderIdx", pkt->RoomList[n].RoomLeaderIdx);
				RoomInfo.set("GameRule", pkt->RoomList[n].GameRule);
				RoomInfo.set("LevelLimit", pkt->RoomList[n].LevelLimit);
				RoomInfo.set("State", pkt->RoomList[n].State);
				RoomInfo.set("Password", pkt->RoomList[n].Password);
				RoomInfo.set("Type", pkt->RoomList[n].Type);
				RoomInfo.set("BattleSessionID", pkt->RoomList[n].BattleSessionID );

			//char dst[64]={0,};
			//int retLength = WideCharToMultiByte(CP_ACP, 0, 
			//pkt->RoomList[n].Name, MAX_ROOM_NAME, dst, 64, 0,0);

			//	RoomInfo.set("Name", dst );
			
//				retLength = WideCharToMultiByte(CP_ACP, 0, 
//			g_UserMap[ pkt->RoomList[n].RoomLeaderIdx ].szCharName, _MAX_CHAR_ID_SIZE, dst, 64, 0,0);
			lua_tinker::call<void>(luaGlue::g_hLua,"OnRoomList", RoomInfo );	
				lua_tinker::enum_stack(luaGlue::g_hLua);
			}
			
		}
		break;

	case _GS_PKT_REQ_SELECT_DECKCARD_RE:
	case _GS_PKT_RESOURCE_ALL_COMPLETE:
	case _GS_PKT_SCENE_COMPLETE_RE:
	case _GS_PKT_SCENE_ALL_COMPLETE:
	case _GS_PKT_MP_BEGIN:
	case _GS_PKT_EP_BEGIN:
	case _GS_PKT_USR_MP_UPDATE:
	case _GS_PKT_USR_HP_UPDATE:
	case _GS_PKT_CREATURE_EP_UPDATE:
	case _GS_PKT_CREATURE_HP_UPDATE:
	case _GS_PKT_CREATURE_DEAD:
	case _GS_PKT_UPDATE_GRAVE_CNT:
	case _GS_PKT_UPDATE_DECK_CNT:
	case _GS_PKT_HANDCARD_USE:
	case _GS_PKT_CREATURE_SUMMON:
	case _GS_PKT_MAGICCARD_USE:
	case _GS_PKT_ENHANCECARD_USE:
	case _GS_PKT_EQUIPCARD_USE:
	case _GS_PKT_UPDATE_USERSTATS:
	case _GS_PKT_ATTACK_RE:
	case _GS_PKT_ATTACK_MOVE_RE:
	case _GS_PKT_DEL_CARD_RE:				/// 카드를 무덤으로 보낸다.
	case _GS_PKT_MISS:
	case _GS_PKT_SKILL_ATTACK_RE:
	case _GS_PKT_UPDATE_USER_STATS:
	case _GS_PKT_UPDATE_CREATURE_STATS:
	case _GS_PKT_SHUFFLE_RE:
	case _GS_PKT_KILL_CREATURE:
	case _GS_PKT_NEW_HANDCARD:
	case _GS_PKT_DMG:
	case _GS_PKT_START_GAME_RE:
	case _GS_PKT_NATURE_ATTRIBUTE:
	case _GS_PKT_OTHERPLAYER_INFO:
	case _GS_PKT_HANDCARD_LIST:
	case _GS_PKT_RESOURCE_COMPLETE_RE:
		break;

	case _GS_PKT_MODIFYROOM:
	case _GS_PKT_MOVE:
	case _GS_PKT_MYCHAR_PARTS_GET_RE:
	case _GS_PKT_MYCHAR_DECKS_GET_RE:
	case _GS_PKT_MYCHAR_INVENTORY_GET_RE:
	case _GS_PKT_CHG_PLAYER_SLOT:
	case _GS_PKT_CHG_PLAYER_DECK:
	case _GS_PKT_LEVELUP:
		break;

	default:
		{
			MessageBox("nonhandle","error",MB_OK );
		}
		break;
	}

}
