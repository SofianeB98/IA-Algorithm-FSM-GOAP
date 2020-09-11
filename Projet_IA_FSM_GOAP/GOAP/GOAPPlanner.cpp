#include "GOAPPlanner.h"

#include "Action.h"
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
	int actionsCost = 1;
	
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
	//pour chaque action disponnible

	//si conditions ok

	//j'applique l'effet au GS
	//j'ajoute
	//j'inscrise le cost

	//tmp vec et cost

	for (auto& a : possibleActions)
	{
		// Check juste la compatibilité des enums
		if (goal->getPreconditions()->checkPrecondition(a.getEffects()->getEffectType()))
		{

			// On incrémente le cost
			cost += a.getCost();
			// On execute l'action
			goal->performAction(actualState);
			// Si les préconditions de l'action sont déjé validés, on s'arrete
			if (goal->getPreconditions()->checkPreconditionOnGs(actualState))
			{
				actionsQueue.push(&a);
				foundGraph = true;
				// Si compatible, on ajoute au tableau de actions possibles
				break;
			}
			else
			{
				bool f = buildGraph(possibleActions, actualState, &a, actionsQueue, cost);
				if(f)
				{
					foundGraph = true;
					break;
				}
			}
		}

	}

	
	return foundGraph;
}
