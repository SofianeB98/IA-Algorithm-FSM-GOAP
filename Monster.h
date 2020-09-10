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
	bool isTurn = false;
	
	const char healQuantity = 5;
	char life;

	Element element;
	Element weakness;
	
public:
	StateMachine::StateMachineBase* machine;
	
	Monster();
	Monster(const Element& elem);
	Monster(const Element& elem, const char l);
	Monster(const Monster& m);
	Monster& operator=(Monster other);

	~Monster();

	void CreateStateMachine();
	
	void takeDamage(char val, Element attackElement);
	void heal();
	
	bool isAlive();
	char getLife() const;
	Element getElement() const;
	Element getWeakness() const;

	bool isMonsterTurn() const;
	void setMonsterTurn(bool val);
	
private:
	void swap(Monster& m);
	
};
#endif
