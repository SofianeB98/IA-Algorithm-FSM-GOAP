#include "WorldMaster.h"

#include "Monster.h"
#include <iostream>
#include <ctime>

bool WorldMaster::escape = false;

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
// Initialise le combat
void WorldMaster::StartWorld()
{
	WorldMaster::escape = false;
	int choosenMonsterElement = 1;
	// Selection de l'élément du monstre du joueur
	std::cout << "Choose your monster's element \n";
	std::cout << "1 - FIRE \n";
	std::cout << "2 - WATER \n";
	std::cout << "3 - GRASS" << std::endl;

	std::cin >> choosenMonsterElement;

	//Création du monstre du joueur
	switch (choosenMonsterElement)
	{
	default:
	case 1:
		monsterPlayer = new Monster(Element::FIRE);
		std::cout << "You've choosen FIRE !! This is so Hot !" << std::endl;
		break;

	case 2:
		monsterPlayer = new Monster(Element::WATER);
		std::cout << "You've choosen WATER !! You're Aquaman !!" << std::endl;
		break;

	case 3:
		monsterPlayer = new Monster(Element::GRASS);
		std::cout << "You've choosen GRASS !! It's so Ecologic, Vegan !" << std::endl;
		break;
	}
	// Initialisation de la state machine
	monsterPlayer->CreateStateMachine();
}

// Boucle de jeu
void WorldMaster::UpdateWorld()
{	
	// On combat tant que le monstre du joueur est vivant
	while(monsterPlayer->isAlive())
	{
		waitForMilliseconds(2500);
		
		//Au début de chaque combat, le monstre est soigné
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
			std::cout << "RDM Monster is FIRE !!" << std::endl;
			break;

		case 2:
			elem = Element::WATER;
			std::cout << "RDM Monster is WATER !!" << std::endl;

			break;

		case 3:
			elem = Element::GRASS;
			std::cout << "RDM Monster is GRASS !!" << std::endl;
			break;
		}

		monsterRandom = new Monster(elem, rdmLife);
		monsterRandom->CreateStateMachine();
		
		//Simulation du combat
		ProcessBattle();
		// Delete du monstre ennemie si il est mort
		if (monsterRandom != nullptr)
		{
			delete monsterRandom;
			monsterRandom = nullptr;
		}
		

		waitForMilliseconds(1000);
	}

	std::cout << "Your monster die ! " << std::endl;
}

void WorldMaster::ProcessBattle()
{
	std::cout << "Begin New Battle !!!!! " << std::endl;
	// Tant que les deux monstres sont en vie et qu'aucun des deux n'as fuit le combat
	while ((monsterPlayer->isAlive() && monsterRandom->isAlive()) || !WorldMaster::escape)
	{
		if (WorldMaster::escape)
			break;
	
		if (!monsterPlayer->isAlive())
		{
			std::cout << "Player Monster Die\n" << std::endl;
			break;
		}

		std::cin.get();
		
		std::cout << "Begin Player Monster Turn \n";
		
		// On actualise la state machine du monstre du joueur et on joue l'action associé à chaque état
		monsterPlayer->machine->ProcessState(*monsterPlayer, *monsterRandom);
		
		std::cout << "End Player Monster Turn" << std::endl;
		
		//wait X milliseconds before execute the next
		waitForMilliseconds(1000);

		if (WorldMaster::escape)
			break;
		
		if (!monsterRandom->isAlive())
		{
			std::cout << "Monster Random Die\n" << std::endl;
			break;
		}
		
		std::cout << "Begin Monster Random Turn \n";
		//On actualise la state machine du monstre adverse et on joue l'action associé à chaque état
		monsterRandom->machine->ProcessState(*monsterRandom, *monsterPlayer);

		std::cout << "End Monster Random Turn \n \n" << std::endl;

		std::cout << "- Player Monster have : " << static_cast<int>(this->monsterPlayer->getLife()) << " life" << std::endl;
		std::cout << "- Monster Random have : " << static_cast<int>(this->monsterRandom->getLife()) << " life" << std::endl;

		std::cout << "\n \n" << std::endl;
	}

	WorldMaster::escape = false;
}
// Delete en cascade de tous les pointeurs
void WorldMaster::DeleteWorld()
{
	if (monsterPlayer != nullptr)
	{
		delete monsterPlayer;
		monsterPlayer = nullptr;
	}
	if (monsterRandom != nullptr)
	{
		delete monsterRandom;
		monsterRandom = nullptr;
	}
}

void WorldMaster::EscapeBattle()
{
	WorldMaster::escape = true;
}
