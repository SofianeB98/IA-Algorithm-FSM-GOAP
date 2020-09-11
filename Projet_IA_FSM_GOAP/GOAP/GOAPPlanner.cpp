#include "GOAPPlanner.h"
#include "GameState.h"

std::stack<const Action*> GOAPPlanner::plan(
	const std::vector<Action>& possibleActions,
	const GameState& actualState,
	const Action* goal) const
{
	//copy toutes les preconditions du goal
	//dès qu'une precondition est remplis
	//je chercher a combler le reste

	std::stack<const Action*> actions;
	int actionsCost = 0;

	GameState stateCopy = actualState;

	bool a = buildGraph(possibleActions, stateCopy, goal, actions, actionsCost);

	return actions;
}

bool GOAPPlanner::buildGraph(const std::vector<Action>& possibleActions,
	GameState& actualState,
	const Action* goal,
	std::stack<const Action*>& actionsQueue,
	int& cost) const
{
	bool foundGraph = false;

	for (auto& action : possibleActions)
	{
		// Check juste la compatibilité des enums
		if (goal->getPreconditions()->checkPrecondition(action.getEffects()->getEffectType()) 
			|| goal->getPreconditions() == nullptr)
		{
			// On incrémente le cost
			cost += action.getCost();
			// On execute l'action
			goal->performAction(actualState);
			// Si les préconditions de l'action sont déjé validés, on s'arrete
			//if (goal->getPreconditions()->checkPreconditionOnGs(actualState))

			actionsQueue.push(&action);
			foundGraph = true;
			// Si compatible, on ajoute au tableau de actions possibles
			break;
		}

		// Sinon, On execute l'action
		goal->performAction(actualState);

		const bool found = buildGraph(possibleActions, actualState, &action, actionsQueue, cost);

		if (found)
		{
			foundGraph = true;
			break;
		}
	}


	return foundGraph;
}
