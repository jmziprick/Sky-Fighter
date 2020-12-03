function move(x, y, timeInSeconds, alive)
	if(alive == 0)
	then return 4 --dead state
	end

	if(timeInSeconds < 5) --fire state
	then return 0
	
	elseif(timeInSeconds >= 5 and timeInSeconds < 8) --stop state
	then return 1
	
	elseif(timeInSeconds >= 8 and timeInSeconds < 10) --resume state
	then return 2
	
	elseif(timeInSeconds >= 10) --restart state
	then return 3

	end
end