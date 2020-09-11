#pragma once
#include <queue>
#include <string>
#include <vector>
#include "Action.h";

class GOAPPlanner
{
public:
	std::queue<const Action*> plan(const std::vector<Action>& possibleActions, const GameState& actualState,
		const Action* const goal) const;

	bool buildGraph();
};
