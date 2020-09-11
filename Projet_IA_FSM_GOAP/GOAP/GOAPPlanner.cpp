#include "GOAPPlanner.h"

#include "Action.h"

std::stack<const Action*> GOAPPlanner::plan(
	const std::vector<Action>& possibleActions, 
	const GameState& actualState, 
	const Action* goal) const
{
	//copy toutes les preconditions du goal
	//dès qu'une precondition est remplis
	//je chercher a combler le reste

	std::stack<const Action*> actions;
	int actionsCost = 1;
	
	
	bool a = buildGraph(possibleActions, actualState, goal, actions, actionsCost);
	
	
	return actions;
}

bool GOAPPlanner::buildGraph(const std::vector<Action>& possibleActions,
	GameState& actualState,
	const Action* goal,
	std::stack<const Action*>& actionsQueue,
	int& cost)
{

	bool foundGraph = false;
	//pour chaque action disponnible

	//si conditions ok

	//j'applique l'effet au GS
	//j'ajoute
	//j'inscrise le cost

	//tmp vec et cost
	std::stack<const Action*> tmpActions;
	int tmpCost = 1;
	
	for(auto& a : possibleActions)
	{
		if (goal->checkPreconditions(a))
		{
			tmpActions.push(&a);
			tmpCost += a.getCost();
			goal->performAction(actualState);
			break;
		}
		else
		{
			tmpActions.push(&a);
			tmpCost += a.getCost();
			goal->performAction(actualState);
			bool found = 0;
		}
	}

	return foundGraph;
}
