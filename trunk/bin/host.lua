require('lua/LuaXml')
require('scheduler')


IP = "66.232.147.107"
PORT = 8292


GAMESERVER_INDEX= 1 --0 base�� �����.
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


local chatLoop = function( taskObj )

	while( true ) do
		send_chatmsg( 2 , "�ȳ��ϼ��� ��Ʈ��ġ ���� �ϽǷ���?" )
		
		local info = {}
		ret = getTable(info) 
		if ret == true
			then 
				ods( "useable table" )
				ods( info.name )
				ods( info.age )
				
			else
				ods( "nil table" )
		end
		
		scheduler:wait(taskObj,2)
--[[
		send_move( {orgx=7.336,orgy=-7.057,orgz=9.336, destx=6.790,desty=3.177,destz=9.336} ) --������ ��ġ�� ����ϴ�.
		scheduler:wait(taskObj,2)

		send_move( {orgx=6.790,orgy=3.177,orgz=9.336,destx= 7.336,desty=-7.057,destz=9.336} ) --������ ��ġ�� ����ϴ�.
		scheduler:wait(taskObj,2)
--]]
	end
end


local myPos={ x=0.21, y=15.57,z=10.00 }
local destPos = myPos

function OnEntryLobby()
	SetTimer(1818,100) --1�ʿ� �ѹ��� 1818 �̶�� ���̵�� OnTimer �� ȣ���Ŵ
	send_move( {orgx=0,orgy=15.7,orgz=9.336,destx=0,desty=16.7,destz=9.336} ) --������ ��ġ�� ����ϴ�.
	send_chatmsg( 2, "���� ����Ŭ���̾�Ʈ �Դϴ�. �������� �۵��� ���� ������ �ֽ��ϴ�." )

	scheduler:Start()
	
	scheduler:addTask( "chatLoop", chatLoop )	
	
	RoomUser = {} --��� ��������.
end


function moveTask (taskObj)

--��ǥ�� �����ߴ��� üũ. ��� �̵���Ŵ.

		while( IsAlive() == true ) do
		
			send_move( {orgx=myPos.x,orgy=myPos.y, orgz=myPos.z ,
						destx=destPos.x,desty=destPos.y,destz= destPos.z } )

			scheduler:wait(taskObj,2)
			
		end
end

function OnAvatarMove(obj)
	print( "wSid: "..obj.wSid )

	print( string.format("flag: %d", obj.flag ) )
	print( string.format("Goal: %.3f,%f,%f",obj.fPosGoal_0, obj.fPosGoal_1,obj.fPosGoal_2) )
	print( string.format( "Orig: %.3f,%f,%f",obj.fPosOrig_0, obj.fPosOrig_1,obj.fPosOrig_2) )

	if obj.wSid ~= MySID() then
		destPos = {x=obj.fPosGoal_0, y=obj.fPosGoal_1, z=obj.fPosGoal_2 }
		scheduler:addTask( string.format( "moveTask_%d",os.clock() ), moveTask )

	else
		myPos={ obj.fPosGoal_0, obj.fPosGoal_1,obj.fPosGoal_2}
	end
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

function OnTimer()
	scheduler:loop()
end

--������ ���� ������.
function OnStartGame()
	send_loadinComplete()
end

