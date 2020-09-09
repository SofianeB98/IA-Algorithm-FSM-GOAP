#include "WorldMaster.h"

#include "Monster.h"
#include <iostream>

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
