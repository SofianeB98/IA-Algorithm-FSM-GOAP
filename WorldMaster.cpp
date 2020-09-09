#include "WorldMaster.h"

#include "Monster.h"
#include <iostream>
#include <time.h>

void waitForMilliseconds(int milli)
{
	// Cross-platform sleep function
	clock_t end_time;
	end_time = clock() + milli * CLOCKS_PER_SEC / 1000;
	while (clock() < end_time) {
		//blank loop for waiting
	}
}

void WorldMaster::StartWorld()
{
	
}

void WorldMaster::UpdateWorld()
{	
	while(monsterPlayer->isAlive())
	{
		//heal

		//generate new monster Random (life + element)
		
		//battle
		ProcessBattle();
	}

	std::cout << "Your monster die ! " << std::endl;
}

void WorldMaster::ProcessBattle()
{
	while (monsterPlayer->isAlive() || monsterRandom->isAlive())
	{
		//Init turn state ?
		//While is monster turn
		//-Process State

		std::cout << "wait";
		
		//wait X milliseconds before execute the next
		waitForMilliseconds(1500);

		std::cout << "   after wait " << std::endl;
		
		//Init turn state ?
		//While is monster turn
		//-Process State
	}
}

void WorldMaster::DeleteWorld()
{
	delete monsterPlayer;
	delete monsterRandom;
}
