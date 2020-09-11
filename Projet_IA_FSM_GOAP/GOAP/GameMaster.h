#pragma once
#include "GameState.h"
#include "GOAPPlanner.h"

/// <summary>
/// Le game master gere les main loop du programme
/// ainsi que les variables qui le font fonctionner
///
/// Ainsi c'est lui qui aura le game state, le planner, les actions possible ainsi que l'objectif a atteindre
/// </summary>
struct GameMaster
{
	GameState* currentGameState;
	GOAPPlanner* goap;
	Action* goal;

	std::vector<Action*> availableActions;
	
	static void waitForMilliseconds(int milli);

	void StartGame();
	
	void UdapteGame();
	
	void DeleteGame();
};
