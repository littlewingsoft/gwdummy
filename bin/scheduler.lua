
scheduler={ tasks={} }

--[[
scheduler.__index = scheduler --Dispatcher ����

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
			wakeUptime = 0 , --sec����
			timeStamp = os.clock()	 --������ �ð� ����.
		}

	 self.tasks[name] = v
end

function scheduler:wait( taskObj, secTime )

	taskObj.wakeUptime = secTime
	taskObj.timeStamp = os.clock()
	return coroutine.yield( secTime )
end

--os.time() 1�ʰ������� �þ.
-- ó�������� �ֵ鸸 �����Ű�� ������ �ٵ� �ֵ��� ����Ʈ���� ����.
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
