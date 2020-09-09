#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_
#include "StateMachine.h"

enum Element
{
	FIRE,
	WATER,
	GRASS,

	NEUTRAL
};

class Monster
{
	char life;
	const char healQuantity = 5;

	Element element;
	Element weakness;
	
public:
	const StateMachine::StateMachineBase* machine = new const StateMachine::StateMachineBase();
	
	Monster();
	Monster(const Element& elem);
	Monster(const Monster& m);
	Monster& operator=(Monster other);

	~Monster();
	
	void takeDamage(char val, Element attackElement);
	bool isAlive();

private:
	void swap(Monster& m);
	
};
#endif
