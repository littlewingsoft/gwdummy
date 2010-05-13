require('lua/LuaXml')
require('scheduler')

scheduler:Start()

IP = "66.232.147.107"
PORT = 8292

GAMESERVER_INDEX= 1 --0 base로 계산함.
GAMECHANNEL_INDEX=0 -- 현재 channel 은 거의 1개임

ID = "jmt3"
PASS ="333"
NICK = "jmt3"

--[[
local RoomUser = {}

local chatLoop = function( taskObj )

	while( true ) do
		send_chatmsg( 2 , "안녕하세요 고스트워치 한판 하실래예?" )
		scheduler:wait(taskObj,2)

		--send_move( {orgx=7.336,orgy=-7.057,orgz=9.336, destx=6.790,desty=3.177,destz=9.336} ) --강제로 위치를 맞춥니다.
		--scheduler:wait(taskObj,2)

	end
end
--]]


local myPos={ x=0.21, y=15.57,z=9.336 }
local destPos = myPos
function OnEntryLobby()

	SetTimer(1818,100) --1초에 한번씩 1818 이라는 아이디로 OnTimer 를 호출시킴
	send_move( {orgx=0,orgy=17.884598,orgz=9.7769442,
				destx=-1,desty=17.884598,destz=9.7769442} ) --강제로 위치를 맞춥니다.
	send_chatmsg( 2, "저는 더미클라이언트 입니다. 정상적인 작동을 하지 않을수 있습니다." )

	--send_PartyCreate()
	send_PartySearch()

end

function OnEnter_Dungeon()
	send_move( {orgx=19,orgy=-152,orgz=365,
				destx=19,desty=-152,destz=365} ) --강제로 위치를 맞춥니다.
end


-- 새로운 파티 멤버가 들어왔는데 jmt1 이면  ready Party 패킷 보냄.
function OnNewPartyMember( nick )
	if nick == "jmt1" then

		send_PartyReady()

	end

end


function OnAvatarMove(obj)
	print( "wSid: "..obj.wSid )
	print( string.format( "Orig: %.3f,%f,%f",obj.fPosOrig_0, obj.fPosOrig_1,obj.fPosOrig_2) )
	print( string.format("Goal: %.3f,%f,%f",obj.fPosGoal_0, obj.fPosGoal_1,obj.fPosGoal_2) )
	print( string.format("flag: %d", obj.flag ) )
	print("\n")

	if obj.wSid ~= MySID() then
		destPos= {x=obj.fPosGoal_0, y=obj.fPosGoal_1, z=obj.fPosGoal_2 }
--		send_move( {orgx=myPos.x,orgy=myPos.y, orgz=myPos.z ,
	--				destx=destPos.x,desty=destPos.y,destz= destPos.z } )
	else
		myPos={ obj.fPosGoal_0, obj.fPosGoal_1,obj.fPosGoal_2}
	end
end



function OnAddUser(name)
	send_chatmsg( 1 , name.."님 안녕하세요 고스트워치 한판 하실래예?" )
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



