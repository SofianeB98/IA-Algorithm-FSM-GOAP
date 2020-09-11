#include "GameMaster.h"

void GameMaster::StartGame()
{
	goap = new GOAPPlanner();

	currentGameState = new GameState();
	currentGameState->availableActions.reserve(20);
	
}

void GameMaster::UdapteGame()
{
	while(currentGameState->woodStock < 200)
	{
		
	}
}


void GameMaster::DeleteGame()
{
	if(currentGameState != nullptr)
	{
		delete currentGameState;
		currentGameState = nullptr;
	}

	if(goap != nullptr)
	{
		delete goap;
		goap = nullptr;
	}
}
