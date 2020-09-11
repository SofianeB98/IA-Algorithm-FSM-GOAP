#include "GOAPPlanner.h"

#include <cassert>

#include "GameState.h"

std::vector<Action*> GOAPPlanner::plan(
	std::vector<Action*>& possibleActions,
	GameState& actualState,
	const Action* goal) const
{
	//copy toutes les preconditions du goal
	//dès qu'une precondition est remplis
	//je chercher a combler le reste

	std::vector<Action*> actions; //Vector final qui sera retourne
	int actionsCost = -1;

	//Copy du state actuel
	GameState stateCopy = actualState;

	//Construction du graph
	for (auto& action : possibleActions)
	{
		std::vector<Action*> tmpActions; //Vector final qui sera retourne
		int tmpCost = -1;

		if (goal->getPrecondition() == nullptr || goal->getPrecondition()->getPrecType() == ActionType::NO_ACTION)
			break;
		
		if (goal->getPrecondition()->checkPrecondition(action->getEffect()->getEffectType()))
		{
			tmpCost = 0;
			
			// On incrémente le cost
			tmpCost += action->getCost();

			// On execute l'action
			//goal->performAction(actualState);

			// On ajoute l'action a la liste
			tmpActions.push_back(action);
			
			const bool isBuilded = buildGraph(possibleActions, stateCopy, action, tmpActions, tmpCost);

		}

		if(actionsCost == -1 
			&& tmpCost > 0)
		{
			actionsCost = tmpCost;
			actions = tmpActions;
		}

		if(tmpCost < actionsCost 
			&& tmpCost > 0)
		{
			actionsCost = tmpCost;
			actions = tmpActions;
		}
	}

	//Repere si on a bien construit le graph
	assert(!actions.empty(), "PROBLEME DE CONFIGURATION DANS LES ACTIONS !!");

	//retourn la liste d'action
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

		//si le but passer en parametre est nulptr ou sont prectype est no action
		//C'est qu'on est arrivé a la fin du graph possible
		//donc on break
		if (goal->getPrecondition() == nullptr || 
			goal->getPrecondition()->getPrecType() == ActionType::NO_ACTION)
		{
			foundGraph = true;
			break;
		}

		//Si la condition de l'action est deja ok sur le gamestate, on stop
		if (goal->getPrecondition()->checkPreconditionOnGs(actualState))
			break;
		
		// Check juste la compatibilité des enums
		// Si c'est vrai, c'est que l'effet repond a la condition
		if (goal->getPrecondition()->checkPrecondition(action->getEffect()->getEffectType()))
		{	
			// On incrémente le cost
			cost += action->getCost();
			
			// On execute l'action
			//goal->performAction(actualState);

			// On ajoute l'action a la liste
			actionsQueue.push_back(action);

			// Vu qu'il y a au moins une action de trouver, on dit qu'on a trouver un chemin
			foundGraph = true;
			
			// Si compatible, on ajoute au tableau de actions possibles
			const bool found = buildGraph(possibleActions, actualState, action, actionsQueue, cost);
		}

		//si tmpcost inferieur a cost en parametre
		//j'assigne tout
	}

	return foundGraph;
}
