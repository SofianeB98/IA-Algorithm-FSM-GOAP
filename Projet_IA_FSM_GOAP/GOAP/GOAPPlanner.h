#pragma once
#include <vector>
#include "Action.h"

class GOAPPlanner
{
public:
	std::vector<Action*> plan(std::vector<Action*>& possibleActions, GameState& actualState,
		const Action* const goal) const;

	bool buildGraph(const std::vector<Action*>& possibleActions,
		GameState& actualState,
		const Action* goal,
		std::vector<Action*>& actionsQueue,
		int& cost) const;
};
