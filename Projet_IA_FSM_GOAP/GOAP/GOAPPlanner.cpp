#include "GOAPPlanner.h"
#include "Action.h"

std::queue<const Action*> GOAPPlanner::plan(
	const std::vector<Action>& possibleActions, 
	const GameState& actualState, 
	const Action* goal) const
{
	//copy toutes les preconditions du goal
	//dès qu'une precondition est remplis
	//je chercher a combler le reste

	std::queue<const Action*> actions;
	//vector-> action
	//int cost;
	//
	//
	//
	//
	
	for(auto& a : possibleActions)
	{
		//tmp vec et cost
		
		if(goal->checkPreconditions(a))
		{
			//do somthing, add to queue
			//add Make sotne
		}
	}

	
	
	return actions;
	
	//toutes les prec fill
	//return
}
