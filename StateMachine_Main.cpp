#include <iostream>
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
	//Create IA player monster

	StateMachineBase monsterA;
	StateMachineBase monsterB;

	State* x;
	x->AddTransition(nullptr);
	
	while (true)
	{
		//initialise monster B
		monsterB = StateMachineBase();

		//Combat
		while (true /*si a && b == en vie*/)
		{
			monsterA.ChangeState(new State());
			monsterA.ProcessState(/*me, other or fightdata ==> ref*/);
			monsterA.ChangeState(new State());
			//wait

			monsterB.ProcessState(/*me, other or fightdata == ref*/);

			//exit when a monster is not alive
			break;
		}

		//if my monster die, exit loop

		//else, heal
	}
	//exit when a.alive == false

	
	std::cout << "Your monster die ! " << std::endl;

	return EXIT_SUCCESS;
}