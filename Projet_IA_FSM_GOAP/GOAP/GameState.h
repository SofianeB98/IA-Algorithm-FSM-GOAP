#pragma once
#include "Action.h"

/// <summary>
/// Contient toutes les donnees du programme
/// On pourrait s'amuser a en ajouter, afin de complexifier
/// et diversifier le goap
/// exemple :
///		- ajouter des ressources
///		- des outils
///		- etc
/// </summary>
class GameState
{
public:
	bool hasAxe = false;
	
	int woodStock = 0;
	int availableAxe = 0;
	int craftedHouse = 0;
	int axeEnergy = 0;
	


	~GameState()
	{
		
	}
};
