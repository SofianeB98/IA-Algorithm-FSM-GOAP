#pragma once
#include "Action.h"

class GameState
{
public:
	std::vector<Action*> availableActions;
	int woodStock = 0;
	int availableAxe = 0;
	int craftedHouse = 0;

	int axeEnergy = 5;
	
	bool hasAxe = false;

	~GameState()
	{
		for(auto a : availableActions)
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
