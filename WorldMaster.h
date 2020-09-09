#pragma once

class Monster;

class WorldMaster
{
public:
	Monster* monsterPlayer;
	Monster* monsterRandom;

	void StartWorld();
	
	void UpdateWorld();

	
};
