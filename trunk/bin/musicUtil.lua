require "schedule.lua"

function music:fadIn(key,vol)
	totalTime = self:datatable[key]:getPlayTime()
	while( true ) do
		if currCursor + 0.3  >= totalTime then
			
		end
		self:datatable[key]:SetVolume( vol )
	end
	
end