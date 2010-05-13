require('lua/LuaXml')
require('scheduler')

scheduler:Start()

IP = "66.232.147.107"
PORT = 8292

GAMESERVER_INDEX= 1 --0 base�� �����.
GAMECHANNEL_INDEX=0 -- ���� channel �� ���� 1����

ID = "jmt3"
PASS ="333"
NICK = "jmt3"

--[[
local RoomUser = {}

local chatLoop = function( taskObj )

	while( true ) do
		send_chatmsg( 2 , "�ȳ��ϼ��� ��Ʈ��ġ ���� �ϽǷ���?" )
		scheduler:wait(taskObj,2)

		--send_move( {orgx=7.336,orgy=-7.057,orgz=9.336, destx=6.790,desty=3.177,destz=9.336} ) --������ ��ġ�� ����ϴ�.
		--scheduler:wait(taskObj,2)

	end
end
--]]


local myPos={ x=0.21, y=15.57,z=9.336 }
local destPos = myPos
function OnEntryLobby()

	SetTimer(1818,100) --1�ʿ� �ѹ��� 1818 �̶�� ���̵�� OnTimer �� ȣ���Ŵ
	send_move( {orgx=0,orgy=17.884598,orgz=9.7769442,
				destx=-1,desty=17.884598,destz=9.7769442} ) --������ ��ġ�� ����ϴ�.
	send_chatmsg( 2, "���� ����Ŭ���̾�Ʈ �Դϴ�. �������� �۵��� ���� ������ �ֽ��ϴ�." )

	--send_PartyCreate()
	send_PartySearch()

end

function OnEnter_Dungeon()
	send_move( {orgx=19,orgy=-152,orgz=365,
				destx=19,desty=-152,destz=365} ) --������ ��ġ�� ����ϴ�.
end


-- ���ο� ��Ƽ ����� ���Դµ� jmt1 �̸�  ready Party ��Ŷ ����.
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
	send_chatmsg( 1 , name.."�� �ȳ��ϼ��� ��Ʈ��ġ ���� �ϽǷ���?" )
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



