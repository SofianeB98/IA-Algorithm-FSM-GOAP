#include "Monster.h"
#include "StateMachine.h"
using namespace StateMachine;

#include "mathutils.h"

Monster::Monster()
{
	this->life = 100;
	this->element = Element::FIRE;
	this->weakness = Element::WATER;
}

Monster::Monster(const Element& elem)
{
	this->life = 100;
	this->element = elem;

	switch (this->element)
	{
	default:
	case Element::FIRE:
		this->weakness = Element::WATER;
		break;

	case Element::WATER:
		this->weakness = Element::GRASS;
		break;

	case Element::GRASS:
		this->weakness = Element::FIRE;
		break;
	}
}

Monster::Monster(const Monster& m)
{
	this->element = m.element;
	this->weakness = m.weakness;
	this->life = m.life;
}

Monster::Monster(const Element& elem, const char l)
{
	this->life = l;
	this->element = elem;

	switch (this->element)
	{
	default:
	case Element::FIRE:
		this->weakness = Element::WATER;
		break;

	case Element::WATER:
		this->weakness = Element::GRASS;
		break;

	case Element::GRASS:
		this->weakness = Element::FIRE;
		break;
	}
}


Monster& Monster::operator=(Monster other)
{
	swap(other);
	return *this;
}

void Monster::swap(Monster& m)
{
	std::swap(this->element, m.element);
	std::swap(this->life, m.life);
	std::swap(this->weakness, m.weakness);
}

Monster::~Monster()
{
	if(this->machine != nullptr)
		delete this->machine;
}

char Monster::getLife() const
{
	return this->life;
}

Element Monster::getElement() const
{
	return this->element;
}

Element Monster::getWeakness() const
{
	return this->weakness;
}


void Monster::heal()
{
	if (this->life >= 100)
		return;
	
	this->life += healQuantity;
}

void Monster::CreateStateMachine()
{
	this->machine = new StateMachine::StateMachineBase();

	State* beginState = new StateMachine::BeginTurnState();
	State* escapeState = new StateMachine::EscapeState();
	State* attackState = new AttackState();
	State* elementalAttackState = new ElementAttackState();
	State* normalAttackState = new NormalAttackState();
	
	BaseTransition* beginToEscapeLife = new LifeConditionTransition(escapeState, false, true, 10);
	BaseTransition* beginToEscapeWeakness = new IsOpponentMyWeaknessTransition(escapeState);
	
	BaseTransition* beginToAttack = new LifeConditionTransition(attackState, true, true, 10);

	beginState->AddTransition(beginToEscapeLife);
	beginState->AddTransition(beginToEscapeWeakness);
	beginState->AddTransition(beginToAttack);

	BaseTransition* elementalAttackTransition = new UseElementalTransition(elementalAttackState);
	BaseTransition* normalAttackTransition = new UseNeutralTransition(normalAttackState);

	attackState->AddTransition(elementalAttackTransition);
	attackState->AddTransition(normalAttackTransition);

	BaseTransition* attackToBegin = new EmptyTransition(beginState);
	
	machine->ChangeState(beginState);


}

bool Monster::isMonsterTurn() const
{
	return this->isTurn;
}

void Monster::setMonsterTurn(bool val)
{
	this->isTurn = val;
}


void Monster::takeDamage(char val, Element attackElement)
{
	char damage = 0;
	
	if (attackElement == this->weakness)
		damage = clamp(val * 2, 0, 100);
	else if (attackElement == Element::NEUTRAL || attackElement == this->element)
		damage = clamp(val * 1, 0, 100);
	else
		damage = clamp(val * 0.5f, 0.0f, 100.0f);;

	this->life -= static_cast<char>(damage);
}

bool Monster::isAlive()
{
	return this->life > 0;
}
