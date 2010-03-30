require('lua/LuaXml')
--require('lua/scheduler')


IP = "66.232.147.107"
PORT = 8292


GAMESERVER_INDEX= 0 --0 base�� �����.
GAMECHANNEL_INDEX=0 -- ���� channel �� ���� 1����

-- Launch( id,pass,nick, "scenario.lua" )

-- login / logOut
-- �ɼǰ��� ���� �����ϰ� ���� ������ �ó����� ��� ���� ���õ�.
-- �ɼǰ��� �ִٸ�
-- ������ 3���� ���ۻ��� ����.
-- �游�� ���
-- �渮��Ʈ ��ȸ�� �����ϰ� ���� ���忡�� �λ��� ��ٸ���
-- join �Ŀ� ��ٸ��� 30��~1�� ������ 10~1���� ī��Ʈ �ٿ� ���� �泪����.
-- ������ ���⿡�� Host/Guest/To Lobby ���� ����


-- battle �ϱ�.
-- n�ʿ� �ѹ��� �������ٰ� ���� �ڵ忡 �ִ� ī�带 ���徿 ��� ���� ������.
-- �ϳ��� ����غ��� ������������� �����ִٰ� �������
-- �ڵ带 ������ ���� ī�� ����Ʈ�� ���ٿ� ��� 1.�̸�(�ε���)/Ÿ�� �� ǥ��.


ID = "jmt3"
PASS ="333"
NICK = "jmt3"


--������ ������.
--[[
		enum eCHATTYPE				/// Ŀ�´�Ƽ ������
		{
			_CHAT_PERSON = 0,		/// ���� �޽���(�ӼӸ�)
			_CHAT_ROOM,				/// �� �޽���
			_CHAT_CHANNEL,			/// ä�� �޽���
			_CHAT_PARTY,			/// ��Ƽ �޽���
			_CHAT_GUILD,			/// ��� �޽���
			_CHAT_SYSTEM,			/// �ý��� �޽���
			_CHAT_GAME_MANAGER,		/// ��� �޽���
			_CHAT_GAME_NOTIFY,		/// ��ü���� �޽���
			_CHAT_MAX
		};
--]]

local RoomUser = {}


function OnEntryLobby()
send_move( 2.21,-0.57,9.336 ) --������ ��ġ�� ����ϴ�.
send_chatmsg( 2, "���� ����Ŭ���̾�Ʈ �Դϴ�. �������� �۵��� ���� ������ �ֽ��ϴ�." )
send_makeRoom("�׽�Ʈ��")
RoomUser = {} --��� ��������.
end

function OnAddUser(name)
	send_chatmsg( 1 , name.."�� �ȳ��ϼ��� ��Ʈ��ġ ���� �ϽǷ���?" )
end

function OnJoinUser( name )
	send_chatmsg( 1, name.."�� �ȳ��ϼ��� ��Ʈ��ġ ���� �ϽǷ���?" )
end


function OnNewUserInRoom( name )
	send_chatmsg( 1, name.."�� � Ready�� ��������!!!!" )
	table.insert( RoomUser, name )
end


function OnLeavUser(userData)
	send_chatmsg( 1, userData.name.."�� good bye" )
	RoomUser[userData.name]=nil
end


-- ��ȿ� ����� ���� ������. ȣ���
function OnReadyChange( Nick,readyState )
	RoomUser[Nick]=readyState

	local cnt = 0
table.foreach( RoomUser,
				function( k,v )
					if v==1 then
						cnt = cnt + 1
					end
				end)


--[[
 ��ȿ� ���� ������� ��� �����ϸ�
 ���� ���� �޼��� ������.
--]]
print( "ready cnt, RoomUserCnt", cnt , #RoomUser )

	if  cnt == #RoomUser then
		print( "send_startGame" )
		send_startGame()
		send_loadinComplete()
	end

end



function OnChat( chat )

   local xdoc = xml.eval(chat)
   if xdoc ~= nil then
	local xelem = xdoc:find(  "CHAT" )
		print( xelem["from"] ..": ".. xelem[1] )
	end
end


