#pragma once
#include "GameState.h"
#include "GOAPPlanner.h"

struct GameMaster
{
	GameState* currentGameState;
	GOAPPlanner* goap;
	Action* goal;

	void waitForMilliseconds(int milli);
	void StartGame();
	
	void UdapteGame();
	
	void DeleteGame();
};
