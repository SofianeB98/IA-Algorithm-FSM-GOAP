#include <functional>
#include <iostream>

#include "Action.h"

void test(const std::function<bool(void)>& fn)
{
	fn();
}

int main()
{
	std::cout << "Hello World!\n";

	int val = 0;

	const std::function<void(int, float, std::string)> t{
		[&val](int i, float f, std::string s)
		{
			std::cout << i << " " << f << " " << s << std::endl;
		}
	};

	test([&val]()
	{
			if (val > 0)
				return false;
		
			return true;
	});


	Action* makeHouse = new Action(1);
	Precondition* p = new Precondition(ConditionType::STOCK_STONE);
	Precondition* p2 = new Precondition(ConditionType::STOCK_WOOD);
	makeHouse->addPreconditions(*p);
	
}


// -----------------------------------------------------------------------
/*
 *  GOAP SOLVER ==> on lui donne state now, state objectif, et il cherche la meilleur chemin
 *
 *  ACTION ==>
 *
 *  PRECONDITION ==>
 *
 *  une action, qui a un cost, pointe vers plusieurs precondition
 *      chaque precondition prevois plusieurs autre action
 *          chaque action a un effet final (exemple : +1 bois)
 *
 *  action = chop wood
 *      -> condition = avoir villageois de disponnible
 *          -non ?
 *              -> Create villageois
 *                  -> condition = avoir 10 de bouffe
 *                      -oui ?
 *          -oui ?
 *              -> reassign villageois
 *
 * actual state
 *  - wood = 50
 *  - stone = 50
 *  - food = 100
 *  - people = 6
 *
 *  target state
 *  - wood = 100
 *  - stone = 100
 *  - food = 200
 *  - people = 12
 *
 * target state == actual state ==> newTargetState = actual *2
 *  - wood = 150
 *  - stone = 100
 *  - food = 100
 *  - people = 60
 */