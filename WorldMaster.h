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
	
private:
	void ProcessBattle();
	void waitForMilliseconds(int milli);
};

#endif