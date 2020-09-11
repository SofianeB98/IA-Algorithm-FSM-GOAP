#include "GOAPPlanner.h"
#include "GameState.h"

std::vector<Action*> GOAPPlanner::plan(
	std::vector<Action*>& possibleActions,
	GameState& actualState,
	const Action* goal) const
{
	//copy toutes les preconditions du goal
	//dès qu'une precondition est remplis
	//je chercher a combler le reste

	std::vector<Action*> actions;
	int actionsCost = 0;

	//GameState stateCopy = actualState;

	bool a = buildGraph(possibleActions, actualState, goal, actions, actionsCost);

	return actions;
}

bool GOAPPlanner::buildGraph(const std::vector<Action*>& possibleActions,
	GameState& actualState,
	const Action* goal,
	std::vector<Action*>& actionsQueue,
	int& cost) const
{
	bool foundGraph = false;

	for (auto& action : possibleActions)
	{
		if (action == goal)
			continue;

		if (goal->getPreconditions() == nullptr || goal->getPreconditions()->getPrecondition() == ActionType::NO_ACTION)
		{
			foundGraph = true;
			break;
		}
		//for(auto& prec : goal->getPreconditions())
		{
			// Check juste la compatibilité des enums
			if (goal->getPreconditions()->checkPrecondition(action->getEffects()->getEffectType()))
			{
				// On incrémente le cost
				cost += action->getCost();
				// On execute l'action
				//goal->performAction(actualState);
				// Si les préconditions de l'action sont déjé validés, on s'arrete
				//if (goal->getPreconditions()->checkPreconditionOnGs(actualState))

				actionsQueue.push_back(action);
				foundGraph = true;
				// Si compatible, on ajoute au tableau de actions possibles
				const bool found = buildGraph(possibleActions, actualState, action, actionsQueue, cost);
			}
		}


	}


	return foundGraph;
}
