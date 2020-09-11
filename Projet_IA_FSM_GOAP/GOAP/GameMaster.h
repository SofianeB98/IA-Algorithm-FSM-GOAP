#pragma once
#include "GameState.h"
#include "GOAPPlanner.h"

struct GameMaster
{
	GameState* currentGameState;
	GOAPPlanner* goap;

	void StartGame();
	
	void UdapteGame();
	
	void DeleteGame();
};
