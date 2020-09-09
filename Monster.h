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
	const char healQuantity = 5;
	char life;

	Element element;
	Element weakness;
	
public:
	const StateMachine::StateMachineBase* machine = new const StateMachine::StateMachineBase();
	
	Monster();
	Monster(const Element& elem);
	Monster(const Element& elem, const char l);
	Monster(const Monster& m);
	Monster& operator=(Monster other);

	~Monster();
	
	void takeDamage(char val, Element attackElement);
	void heal();
	bool isAlive();

private:
	void swap(Monster& m);
	
};
#endif
