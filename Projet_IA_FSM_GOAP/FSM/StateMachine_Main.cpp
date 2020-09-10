#include <iostream>

#include "WorldMaster.h"
#include "Monster.h"
#include "StateMachine.h"

using namespace StateMachine;

int main()
{
	WorldMaster world;
	
	
	world.StartWorld();

	world.UpdateWorld();
	
	world.DeleteWorld();
	
	return EXIT_SUCCESS;
}