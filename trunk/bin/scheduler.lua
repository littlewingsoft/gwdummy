
scheduler={
tasks={},
coLoop = nil
}

function proc_ret(successflag, errmsg)
	if successflag == false then
		print( successflag, errmsg )
	end
end

--os.time() 1초간격으로 늘어남.
-- 처리가능한 애들만 실행시키고 실행이 다된 애들은 리스트에서 삭제.
function scheduler:Dispatch()

	while( true ) do
		for name,task in pairs(self.tasks) do
			local currtime = os.clock()
			--print( "worked"..name ) --, task.wakeUptime
			if  os.clock() >= task.wakeUptime + task.timeStamp then
				bFlag, msg = coroutine.resume( task.co, task )
				proc_ret(bFlag, msg )
			end

			if coroutine.status(task.co) == "dead" then
				self.tasks[name] = nil
			end
		end
		coroutine.yield()
	end

end

function scheduler:Start()
	self.coLoop = coroutine.create( self.Dispatch )
end

function scheduler:loop()
	bFlag, msg = coroutine.resume( self.coLoop, scheduler )
	proc_ret(bFlag, msg )
end

function scheduler:addTask( name, task )
	 v ={
			co = coroutine.create( task ),
			wakeUptime = 0 , --sec단위
			timeStamp = os.clock()	 --마지막 시간 저장.
		}

	 self.tasks[name] = v
end

function scheduler:wait( taskObj, secTime )

	taskObj.wakeUptime = secTime
	taskObj.timeStamp = os.clock()
	return coroutine.yield( secTime )
end


