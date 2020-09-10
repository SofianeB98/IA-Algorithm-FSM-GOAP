#include "WorldMaster.h"

#include "Monster.h"
#include <iostream>
#include <ctime>

void WorldMaster::waitForMilliseconds(int milli)
{
	// Cross-platform sleep function
	clock_t end_time;
	end_time = clock() + milli * CLOCKS_PER_SEC / 1000;
	while (clock() < end_time) 
	{
		//blank loop for waiting
	}
}

void WorldMaster::StartWorld()
{
	monsterPlayer->CreateStateMachine();
}

void WorldMaster::UpdateWorld()
{	
	while(monsterPlayer->isAlive())
	{
		//heal
		monsterPlayer->heal();
		
		//generate new monster Random (life + element)
		srand(time(NULL));
		const int rdmElem = rand() % 3 + 1;
		const char rdmLife = rand() % 100 + 1;
		Element elem;

		switch (rdmElem)
		{
		default:
		case 1:
			elem = Element::FIRE;
			break;

		case 2:
			elem = Element::WATER;
			break;

		case 3:
			elem = Element::GRASS;
			break;
		}

		monsterRandom = new Monster(elem, rdmLife);
		monsterRandom->CreateStateMachine();
		std::cout << (int)rdmLife << " Monster life "<< std::endl;
		
		//battle
		ProcessBattle();

		delete monsterRandom;
	}

	std::cout << "Your monster die ! " << std::endl;

	
}

void WorldMaster::ProcessBattle()
{
	std::cout << "new battler ! " << std::endl;
	
	while (monsterPlayer->isAlive() && monsterRandom->isAlive())
	{
		if (!monsterPlayer->isAlive())
			break;
		
		//Init turn state ?
		//While is monster turn
		//-Process State
		//while(monsterPlayer->getLife() > 6)
		monsterPlayer->machine->ProcessState(*monsterPlayer, *monsterRandom);
		
		std::cout << "wait";
		
		//wait X milliseconds before execute the next
		waitForMilliseconds(1000);

		std::cout << "   after wait " << std::endl;

		if (!monsterRandom->isAlive())
			break;
		
		//Init turn state ?
		//While is monster turn
		//-Process State
		//while (monsterRandom->isAlive())
		monsterRandom->machine->ProcessState(*monsterRandom, *monsterPlayer);
		
		monsterRandom->takeDamage(100, Element::NEUTRAL);
		
	}
}

void WorldMaster::DeleteWorld()
{
	delete monsterPlayer;
	delete monsterRandom;
}
