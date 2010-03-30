
scheduler={ tasks={} }

--[[
scheduler.__index = scheduler --Dispatcher 생성

function scheduler:Create()
	local obj=
	{
		tasks={}
	}
	setmetatable( obj,scheduler )
	return obj
end
--]]

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

--os.time() 1초간격으로 늘어남.
-- 처리가능한 애들만 실행시키고 실행이 다된 애들은 리스트에서 삭제.
function scheduler:Dispatch()

	repeat
		for name,task in pairs(self.tasks) do
			local currtime = os.clock()
			--print( os.clock() ) --, task.wakeUptime
			if  os.clock() >= task.wakeUptime + task.timeStamp then
				coroutine.resume( task.co, task )
			end

			if coroutine.status(task.co) == "dead" then
				self.tasks[name] = nil
			end

		end
	until not next(self.tasks)
	print( "nothing more than" )
end
