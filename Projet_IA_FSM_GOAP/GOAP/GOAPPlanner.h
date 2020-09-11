#pragma once
#include <stack>
#include <string>
#include <vector>
#include "Action.h";

class GOAPPlanner
{
public:
	std::stack<const Action*> plan(const std::vector<Action>& possibleActions, const GameState& actualState,
		const Action* const goal) const;

	bool buildGraph(const std::vector<Action>& possibleActions,
		GameState& actualState,
		const Action* goal,
		std::stack<const Action*>& actionsQueue,
		int& cost) const;
};
