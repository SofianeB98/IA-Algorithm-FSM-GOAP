#pragma once
#include "Action.h"

class GameState
{
public:
	std::vector<Action*> availableActions;
	int woodStock = 0;
	bool hasAxe = false;

	~GameState()
	{
		for(auto& a : availableActions)
		{
			if(a != nullptr)
			{
				delete a;
				a = nullptr;
			}
		}

		availableActions.clear();
	}
};
