--[[

�ش缭��,ä�ο�  jmt4�� ���� �濡�� ��.

taskmanager �� ����
�Ź� üũ�� task�� ���ư��� �ؾ���
task �� ������ ������ ����.

1. request Joint packet
2. �濡 ���� ready �ϰ� � �������ڴ� ä�� �޼��� ����.
3. chating �޼����� �Ľ��Ŀ� ������ ��, �׷�, �ƴ�, ���Ǻ���

--]]

IP = "66.232.147.107"
PORT = 8292

GAMESERVER_INDEX= 6 --0 base�� �����.
GAMECHANNEL_INDEX=0 -- ���� channel �� ���� 1����


ID = "jmt3"
PASS ="333"
NICK = "jmt3"


--������ ������.
function OnEntryLobby()
send_move( 2.21,-0.57,9.336 ) --������ ��ġ�� ����ϴ�.
_print( "send_requestRoomList()" )
send_requestRoomList()
SetTimer(1818,1000) --1�ʿ� �ѹ��� 1818 �̶�� ���̵�� OnTimer �� ȣ���Ŵ
end

function OnAddUser(name)

--send_chatmsg( name.."�� �ȳ��ϼ���" )
end

cnt = 0

function OnJoinUser( Nick )
if Nick == "jmt1" then
   _print( Nick.."�߿Դ�" )
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
		_print( roomInfo.RoomLeaderIdx.."�� jmt1�� ��" )
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

--������ ���� ������.
function OnStartGame()
	send_loadinComplete()
end

function OnChat( chat )
--   local xfile = xml.eval(chat)
 --  print( xfile )
	_print( chat )
end





