#include <iostream>

#include "Monster.h"
#include "StateMachine.h"

using namespace StateMachine;

int main()
{
	std::cout << "Choose your monster's element \n";
	std::cout << "1 - FIRE \n";
	std::cout << "2 - WATER \n";
	std::cout << "3 - GRASS" << std::endl;

	int element;
	
	std::cin >> element;
	
	Monster monsterA;
	//Create IA player monster
	switch (element)
	{
	default:
	case Element::FIRE:
		monsterA = Monster(Element::FIRE);
		break;
		
	case Element::WATER:
		monsterA = Monster(Element::WATER);
		break;

	case Element::GRASS:
		monsterA = Monster(Element::GRASS);
		break;
	}

	
	//StateMachineBase monsterA;
	//StateMachineBase monsterB;

	//State* x;
	//x->AddTransition(nullptr);
	
	//while (true)
	{
		//initialise monster B
		//monsterB = StateMachineBase();

		//Combat
		while (true /*si a && b == en vie*/)
		{
			//while(true != false)
			//	monsterA.ProcessState(/*me, other or fightdata ==> ref*/);
			//wait

//			monsterB.ProcessState(/*me, other or fightdata == ref*/);

			//exit when a monster is not alive
			break;
		}

		//if my monster die, exit loop

		//else, heal
		//break;
	}
	//exit when a.alive == false
	
	std::cout << "Your monster die ! " << std::endl;

	return EXIT_SUCCESS;
}