﻿#include "GameMaster.h"



#include <cassert>
#include <ctime>
#include <iostream>

void GameMaster::waitForMilliseconds(int milli)
{
	// Cross-platform sleep function
	clock_t end_time;
	end_time = clock() + milli * CLOCKS_PER_SEC / 1000;
	while (clock() < end_time)
	{
		//blank loop for waiting
	}
}

void GameMaster::StartGame()
{
	goap = new GOAPPlanner();

	Precondition* woodPrec = new Precondition(ActionType::STOCK_WOOD);
	woodPrec->setPrecondition([](const GameState& gs)
		{
			if (gs.woodStock >= 150)
				return true;
		
			return false;
		});

	Precondition* haveAxePrec = new Precondition(ActionType::HAVE_AXE);
	haveAxePrec->setPrecondition([](const GameState& gs)
		{
			return gs.availableAxe > 0;
		});

	Precondition* buildAxePrec = new Precondition(ActionType::BUILD_AXE);
	haveAxePrec->setPrecondition([](const GameState& gs)
		{
			return true;
		});
	
	// ---------------------------------------------------------------------------------
	
	Effect* houseEffect = new Effect(ActionType::BUILD_HOUSE);
	houseEffect->setEffect([](GameState& gs)
		{
			gs.woodStock -= 150;
			gs.craftedHouse += 1;

			std::cout << "J'ai construit une Maison !! " << gs.craftedHouse << std::endl;
		});
	
	Effect* stockWoodEffect = new Effect(ActionType::STOCK_WOOD);
	stockWoodEffect->setEffect([](GameState& gs)
		{
			gs.woodStock += 100;
			gs.axeEnergy -= 2;
		
			std::cout << "Je recolte du bois !! + 10 :::: " << gs.woodStock << std::endl;
			std::cout << "Ma hache perd en energie !! " << gs.axeEnergy << std::endl;
		
			if (gs.axeEnergy <= 0)
				gs.hasAxe = false;
		});

	Effect* haveAxeEffect = new Effect(ActionType::HAVE_AXE);
	haveAxeEffect->setEffect([](GameState& gs)
		{
			std::cout << "J'ai pris une hache !!" << std::endl;
		
			gs.hasAxe = true;
			gs.availableAxe -= 1;
			gs.axeEnergy = 10;
		});
	
	Effect* buildAxeEffect = new Effect(ActionType::BUILD_AXE);
	buildAxeEffect->setEffect([](GameState& gs)
		{
			std::cout << "Je construit une hache !!" << std::endl;
			gs.availableAxe += 1;
		});
	
	// ---------------------------------------------------------------------------------
	
	goal = new Action(5);
	goal->setEffect(houseEffect);
	goal->setPrecondition(woodPrec);

	Action* stockWood = new Action(2);
	stockWood->setEffect(stockWoodEffect);
	stockWood->setPrecondition(haveAxePrec);
	
	Action* pickupAxe = new Action(1);
	pickupAxe->setEffect(haveAxeEffect);
	pickupAxe->setPrecondition(buildAxePrec);
	
	Action* buildAxe = new Action(1);
	buildAxe->setEffect(buildAxeEffect);
	buildAxe->setPrecondition(nullptr);

	
	currentGameState = new GameState();
	currentGameState->availableActions.reserve(20);

	currentGameState->availableActions.push_back(goal);
	currentGameState->availableActions.push_back(stockWood);
	currentGameState->availableActions.push_back(pickupAxe);
	currentGameState->availableActions.push_back(buildAxe);
}

void GameMaster::UdapteGame()
{
	while(currentGameState->craftedHouse < 2)
	{
		{
			std::vector<Action*> plan = goap->plan(currentGameState->availableActions, *currentGameState, goal);

			assert(!plan.empty(), " PLAN EMPTY !!!");

			for(int i = plan.size() - 1; i >= 0; --i)
			{
				plan[i]->performAction(*currentGameState);
				waitForMilliseconds(1000);
			}

			std::cout << "\n" << std::endl;
			
			waitForMilliseconds(1000);
			plan.clear();
		}

		if (goal->getPreconditions()->checkPreconditionOnGs(*currentGameState))
		{
			goal->getEffects()->applyEffect(*currentGameState);

		}
	}
}


void GameMaster::DeleteGame()
{
	if(currentGameState != nullptr)
	{
		delete currentGameState;
		currentGameState = nullptr;
	}

	if(goap != nullptr)
	{
		delete goap;
		goap = nullptr;
	}

}
