#ifndef _WORLDMASTER_HPP_
#define _WORLDMASTER_HPP_

class Monster;

extern bool escape;

class WorldMaster
{
public:
	static bool escape;

	Monster* monsterPlayer;
	Monster* monsterRandom;

	
	void StartWorld();
	
	void UpdateWorld();
	void DeleteWorld();
	
	void waitForMilliseconds(int milli);

	static void EscapeBattle();
	
private:
	void ProcessBattle();
};

#endif