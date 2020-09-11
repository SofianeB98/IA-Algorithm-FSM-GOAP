#include "GameMaster.h"

#include <cassert>
#include <ctime>
#include <iostream>

//Fonction qui permet d'attendre un peu
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
	//creation du planner
	goap = new GOAPPlanner();

	// creation des divers preconditions necessaire
	Precondition* woodPrec = new Precondition(ActionType::STOCK_WOOD);
	woodPrec->setPrecondition([](const GameState& gs)
		{
			//L'effet lié à cette precondition peut etre realiser lorsque
			//le gamestate a 150 de bois ou plus
			if (gs.woodStock >= 150)
				return true;

			//sinon on continue
			return false;
		});

	Precondition* haveAxePrec = new Precondition(ActionType::HAVE_AXE);
	haveAxePrec->setPrecondition([](const GameState& gs)
		{
			//L'effet lié à cette precondition peut etre realiser lorsque
			//le gamestate est equiper d'une hache
			return gs.hasAxe;
		});

	Precondition* buildAxePrec = new Precondition(ActionType::BUILD_AXE);
	buildAxePrec->setPrecondition([](const GameState& gs)
		{
			//L'effet lié à cette precondition peut etre realiser lorsque
			//le gamestate a des Haches, et qu'il n'est plus equiper d'une hache
			return gs.availableAxe > 0 && !gs.hasAxe;
		});

	Precondition* beforeBuildAxePrec = new Precondition(ActionType::NO_ACTION);
	beforeBuildAxePrec->setPrecondition([](const GameState& gs)
		{
			//L'effet lié à cette precondition peut etre realiser lorsque
			//le gamestate n'a plus de Hache, et qu'il n'est plus equiper d'une hache
			return gs.availableAxe < 1 && !gs.hasAxe;
		});

	// ---------------------------------------------------------------------------------

	//creation des divers effets
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
			gs.woodStock += 10;
			gs.axeEnergy -= 2;

			std::cout << "Je recolte du bois !! + 10 :::: " << gs.woodStock << std::endl;
			std::cout << "Ma hache perd en energie !! " << gs.axeEnergy << std::endl;

			if (gs.axeEnergy <= 0)
			{
				gs.hasAxe = false;
				std::cout << "Je n'ai plus de hache ..." << std::endl;
			}
		});

	Effect* pickupAxeEffect = new Effect(ActionType::HAVE_AXE);
	pickupAxeEffect->setEffect([](GameState& gs)
		{
			std::cout << "J'ai pris une hache !!" << std::endl;

			gs.hasAxe = true;
			gs.availableAxe -= 1;
			gs.axeEnergy = 6;
		});

	Effect* buildAxeEffect = new Effect(ActionType::BUILD_AXE);
	buildAxeEffect->setEffect([](GameState& gs)
		{
			std::cout << "Je construit une hache !!" << std::endl;
			gs.availableAxe += 1;
		});

	// ---------------------------------------------------------------------------------

	//creation des divers actions
	goal = new Action(5);
	goal->setEffect(houseEffect);
	goal->setPrecondition(woodPrec);

	Action* stockWood = new Action(2);
	stockWood->setEffect(stockWoodEffect);
	stockWood->setPrecondition(haveAxePrec);

	Action* pickupAxe = new Action(1);
	pickupAxe->setEffect(pickupAxeEffect);
	pickupAxe->setPrecondition(buildAxePrec);

	Action* buildAxe = new Action(1);
	buildAxe->setEffect(buildAxeEffect);
	buildAxe->setPrecondition(beforeBuildAxePrec);

	// ---------------------------------------------------------------------------------

	//creation du gamestate
	currentGameState = new GameState();
	
	//on alloc de la place au actions possible
	availableActions.reserve(10);
	//on ajoute les action
	availableActions.push_back(goal);
	availableActions.push_back(stockWood);
	availableActions.push_back(pickupAxe);
	availableActions.push_back(buildAxe);
}

void GameMaster::UdapteGame()
{
	//Tant qu'on a pas construit X maisons
	while (currentGameState->craftedHouse < 2)
	{
		//On recherche le plan d'action optimal
		std::vector<Action*> plan = goap->plan(availableActions, *currentGameState, goal);

		//on verrifie qu'il y a au moins 1 action
		assert(!plan.empty(), " PLAN EMPTY !!!");

		//on applique les action depuis la fin
		for (int i = plan.size() - 1; i >= 0; --i)
		{
			//Si la condition sur le Gamestate est valide
			if (plan[i]->getPrecondition()->checkPreconditionOnGs(*currentGameState))
			{
				//On l'applique
				plan[i]->performAction(*currentGameState);
			}

			//On attend X millisecond avant de continuer
			waitForMilliseconds(500);
		}

		std::cout << "\n" << std::endl;

		//Enfinc on regarde si on peut réaliser notre objectif
		if (goal->getPrecondition()->checkPreconditionOnGs(*currentGameState))
		{
			goal->getEffect()->applyEffect(*currentGameState);
		}

		//on clear le plan
		//il n'est pas necessaire de le clear etant donner qu'on le reassigne
		//de plus il n'est pas necessaire de delete les action qu'il contient vu qu'elle seront detruite dans
		//delete game
		plan.clear();

		//on attend X milliseconde avant la prochaine boucle
		waitForMilliseconds(500);
	}
}


void GameMaster::DeleteGame()
{
	//detruit automatiquement toutes les action, prec et effet
	for (auto a : availableActions)
	{
		if (a != nullptr)
		{
			delete a;
			a = nullptr;
		}
	}
	availableActions.clear();
	
	//destruction du game state
	if (currentGameState != nullptr)
	{
		delete currentGameState;
		currentGameState = nullptr;
	}

	//destruction du planner
	if (goap != nullptr)
	{
		delete goap;
		goap = nullptr;
	}

}
