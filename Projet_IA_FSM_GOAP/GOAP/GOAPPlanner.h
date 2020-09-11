#pragma once
#include <vector>
#include "Action.h"

class GOAPPlanner
{
public:
	//Retourne la succession d'action necessaire a atteindre le but
	std::vector<Action*> plan(std::vector<Action*>& possibleActions, GameState& actualState,
		const Action* const goal) const;

	//Renvois vrai si on a reussis a construire un graph
	//sinon c'est qu'il y a un probleme dans la config des Action
	bool buildGraph(const std::vector<Action*>& possibleActions,
		GameState& actualState,
		const Action* goal,
		std::vector<Action*>& actionsQueue,
		int& cost) const;
};
