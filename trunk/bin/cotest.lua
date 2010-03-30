require ("scheduler")

--[[
	test routine.
--]]


local  testTask =
function (taskObj)

	print("hi")
		scheduler:wait(taskObj, 3 ) -- 3초 후에 아래 문맥실행.
	print( "what are you doing? " )
		scheduler:wait(taskObj, 5 ) -- 5초 후에 아래 문맥 실행.
	print( "if you don't tell me, then im going to byebye" )
		scheduler:wait(taskObj, 3 ) -- 3초 후에 아래의 문맥 실행.
	print( "ok byebye~~" )

	--모두 끝남. coroutine 은 dead 상태가됨.
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
scheduler:loop() --game 에서 매루프 넣어주면 됨.
end



