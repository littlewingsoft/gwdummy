require ("scheduler")

--[[
	test routine.
--]]


local  testTask =
function (taskObj)

	print("hi")
		scheduler:wait(taskObj, 3 ) -- 3�� �Ŀ� �Ʒ� ���ƽ���.
	print( "what are you doing? " )
		scheduler:wait(taskObj, 5 ) -- 5�� �Ŀ� �Ʒ� ���� ����.
	print( "if you don't tell me, then im going to byebye" )
		scheduler:wait(taskObj, 3 ) -- 3�� �Ŀ� �Ʒ��� ���� ����.
	print( "ok byebye~~" )

	--��� ����. coroutine �� dead ���°���.
end

function testTerror(taskObj)
	for n=1,100 do
		print( "hi", n )
		scheduler:wait(taskObj, 0.01 )

	end
	print "terror compeleted!!!!"
end

--local sc = scheduler:Create()
scheduler:addTask( "testTask", testTask )
--scheduler:addTask( "testTerror", testTerror )
scheduler:Start()

while ( true ) do
scheduler:loop() --game ���� �ŷ��� �־��ָ� ��.
end



