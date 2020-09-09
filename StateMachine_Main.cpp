#include <iostream>

#include "WorldMaster.h"
#include "Monster.h"
#include "StateMachine.h"

using namespace StateMachine;

int main()
{
	int choosenMonsterElement = 1;
	
	std::cout << "Choose your monster's element \n";
	std::cout << "1 - FIRE \n";
	std::cout << "2 - WATER \n";
	std::cout << "3 - GRASS" << std::endl;
	
	std::cin >> choosenMonsterElement;
	
	WorldMaster world;
	//Create IA player monster
	switch (choosenMonsterElement)
	{
	default:
	case 1:
		world.monsterPlayer = new Monster(Element::FIRE);
		std::cout << "You've choosen FIRE !! This is so Hot !" << std::endl;
		break;
		
	case 2:
		world.monsterPlayer = new Monster(Element::WATER);
		std::cout << "You've choosen WATER !! You're Aquaman !!" << std::endl;
		break;

	case 3:
		world.monsterPlayer = new Monster(Element::GRASS);
		std::cout << "You've choosen GRASS !! It's so Ecologic, Vegan !" << std::endl;
		break;
	}

	world.StartWorld();

	world.UpdateWorld();
	
	world.DeleteWorld();
	
	return EXIT_SUCCESS;
}