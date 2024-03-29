require('lua/LuaXml')
require('scheduler')


IP = "66.232.147.107"
PORT = 8292


GAMESERVER_INDEX= 1 --0 base로 계산함.
GAMECHANNEL_INDEX=0 -- 현재 channel 은 거의 1개임

-- Launch( id,pass,nick, "scenario.lua" )

-- login / logOut
-- 옵션값에 따라서 랜덤하게 할지 정해진 시나리오 대로 할지 셋팅됨.
-- 옵션값이 있다면
-- 마을을 3바퀴 뺑글뺑글 돈다.
-- 방만들어서 대기
-- 방리스트 조회후 렌덤하게 들어가서 방장에게 인사후 기다리기
-- join 후에 기다리다 30초~1분 지나면 10~1까지 카운트 다운 세고 방나가기.
-- 대기방목록 보기에서 Host/Guest/To Lobby 할지 결정


-- battle 하기.
-- n초에 한번씩 서버에다가 현재 핸드에 있는 카드를 한장씩 모두 쿼리 날려봄.
-- 하나씩 사용해보고 응답오기전까진 멈춰있다가 응답오면
-- 핸드를 받으면 현재 카드 리스트를 한줄에 모두 1.이름(인덱스)/타입 로 표기.


ID = "jmt3"
PASS ="333"
NICK = "jmt3"


--마을에 들어갔을때.
--[[
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
--]]

local RoomUser = {}


local chatLoop = function( taskObj )

	while( true ) do
		send_chatmsg( 2 , "안녕하세요 고스트워치 한판 하실래예?" )
		
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
		send_move( {orgx=7.336,orgy=-7.057,orgz=9.336, destx=6.790,desty=3.177,destz=9.336} ) --강제로 위치를 맞춥니다.
		scheduler:wait(taskObj,2)

		send_move( {orgx=6.790,orgy=3.177,orgz=9.336,destx= 7.336,desty=-7.057,destz=9.336} ) --강제로 위치를 맞춥니다.
		scheduler:wait(taskObj,2)
--]]
	end
end


local myPos={ x=0.21, y=15.57,z=10.00 }
local destPos = myPos

function OnEntryLobby()
	SetTimer(1818,100) --1초에 한번씩 1818 이라는 아이디로 OnTimer 를 호출시킴
	send_move( {orgx=0,orgy=15.7,orgz=9.336,destx=0,desty=16.7,destz=9.336} ) --강제로 위치를 맞춥니다.
	send_chatmsg( 2, "저는 더미클라이언트 입니다. 정상적인 작동을 하지 않을수 있습니다." )

	scheduler:Start()
	
	scheduler:addTask( "chatLoop", chatLoop )	
	
	RoomUser = {} --모두 날려버려.
end


function moveTask (taskObj)

--목표에 도달했는지 체크. 계속 이동시킴.

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
	send_chatmsg( 1 , name.."님 안녕하세요 고스트워치 한판 하실래예?" )
end

function OnJoinUser( name )
	send_chatmsg( 1, name.."님 안녕하세요 고스트워치 한판 하실래예?" )
end


function OnNewUserInRoom( name )
	send_chatmsg( 1, name.."님 어서 Ready를 누르세요!!!!" )
	table.insert( RoomUser, name )
end


function OnLeavUser(userData)
	send_chatmsg( 1, userData.name.."님 good bye" )
	RoomUser[userData.name]=nil
end


-- 방안에 사람이 레디 했을때. 호출됨
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
 방안에 들어온 사람들이 모두 레디하면
 게임 시작 메세지 보내기.
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

--방장이 게임 시작함.
function OnStartGame()
	send_loadinComplete()
end

