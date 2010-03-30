--[[

해당서버,채널에  jmt4가 만든 방에만 들어감.

taskmanager 를 만들어서
매번 체크후 task가 돌아가게 해야함
task 의 종류는 다음과 같다.

1. request Joint packet
2. 방에 들어가서 ready 하고 어서 시작하자는 채팅 메세지 보냄.
3. chating 메세지를 파싱후에 응답함 응, 그래, 아니, 한판붙자

--]]

IP = "66.232.147.107"
PORT = 8292

GAMESERVER_INDEX= 6 --0 base로 계산함.
GAMECHANNEL_INDEX=0 -- 현재 channel 은 거의 1개임


ID = "jmt3"
PASS ="333"
NICK = "jmt3"


--마을에 들어갔을때.
function OnEntryLobby()
send_move( 2.21,-0.57,9.336 ) --강제로 위치를 맞춥니다.
_print( "send_requestRoomList()" )
send_requestRoomList()
SetTimer(1818,1000) --1초에 한번씩 1818 이라는 아이디로 OnTimer 를 호출시킴
end

function OnAddUser(name)

--send_chatmsg( name.."님 안녕하세요" )
end

cnt = 0

function OnJoinUser( Nick )
if Nick == "jmt1" then
   _print( Nick.."잘왔다" )
   end

end

function OnLeavUser(nick)
end


function OnReadyChange( Nick,readyState )
if  Nick== "jmt1" and readyState == 1 then
	_print( "startGame" )
    send_startGame()
	send_loadinComplete()
   end
end

function OnRoomList( roomInfo ) --,hostNick
--	if hostNick == "jmt1" then
		_print( roomInfo.RoomLeaderIdx.."은 jmt1의 방" )
--	end
end

--[[
taskList = { task1,task2,task3 }

function TaskMgr_update()

foreach task in taskList
     _print( taskList[n] )
	 coroutine.yield(1000)
end

end
--]]

function OnTimer()

	send_requestRoomList()
end

--방장이 게임 시작함.
function OnStartGame()
	send_loadinComplete()
end

function OnChat( chat )
--   local xfile = xml.eval(chat)
 --  print( xfile )
	_print( chat )
end





