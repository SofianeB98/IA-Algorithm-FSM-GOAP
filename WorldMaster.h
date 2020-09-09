#ifndef _WORLDMASTER_HPP_
#define _WORLDMASTER_HPP_

class Monster;

class WorldMaster
{
public:
	Monster* monsterPlayer;
	Monster* monsterRandom;

	void StartWorld();
	
	void UpdateWorld();
	void DeleteWorld();
	
	void waitForMilliseconds(int milli);
	
private:
	void ProcessBattle();
};

#endif