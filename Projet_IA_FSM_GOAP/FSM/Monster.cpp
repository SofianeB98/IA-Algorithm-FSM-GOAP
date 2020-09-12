#include "Monster.h"

#include <ctime>

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
	if (this->machine != nullptr)
	{
		delete this->machine;
		machine = nullptr;
	}
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
	// Initialisation de la state machine
	this->machine = new StateMachine::StateMachineBase();
	// Création de tous les states
	State* beginState = new StateMachine::BeginTurnState();
	State* escapeState = new StateMachine::EscapeState();
	State* attackState = new AttackState();
	State* elementalAttackState = new ElementAttackState();
	State* normalAttackState = new NormalAttackState();

	// Création des conditions
	BaseTransition* beginToEscapeLife = new LifeConditionTransition(false, true, 10); // Si l'adversaire a plus de 10 point de vie
	PairTransitionToState* beginToEscapeLifePair = new PairTransitionToState(escapeState, beginToEscapeLife);
	beginState->AddTransition(beginToEscapeLifePair);

	BaseTransition* beginToEscapeLifeAndWeakness = new LifeConditionAndWeaknessTransition(50); // Si le joueur a moins de 50pdv et que l'adversaire de notre élément faiblesse
	PairTransitionToState* beginToEscapeLifeAndWeaknessPair = new PairTransitionToState(escapeState, beginToEscapeLifeAndWeakness);
	beginState->AddTransition(beginToEscapeLifeAndWeaknessPair);



	// Begin to attack
		// Life > 10
	BaseTransition* beginToAttack = new LifeConditionTransition(true, true, 10); // Si le monstre a plus de 10 point de vie
	PairTransitionToState* beginToAttackPair = new PairTransitionToState(attackState, beginToAttack);
	beginState->AddTransition(beginToAttackPair);

	//attack to elementalAtack
		// UseElementalTransition
	BaseTransition* attackToElemental = new UseElementalTransition(); // Si l'adversaire est faible face à notre élément
	PairTransitionToState* attackToElementalPair = new PairTransitionToState(elementalAttackState, attackToElemental);
	attackState->AddTransition(attackToElementalPair);
	// attack to neutral
		// UseNeutral
	BaseTransition* attackToNeutral = new UseNeutralTransition(); // Si il ne l'est pas
	PairTransitionToState* attackToNeutralPair = new PairTransitionToState(normalAttackState, attackToNeutral);
	attackState->AddTransition(attackToNeutralPair);

	// Back to Begin
	BaseTransition* neutralToBegin = new EmptyTransition();// Retour en état initial systématique 
	PairTransitionToState* neutralToBeginPair = new PairTransitionToState(beginState, neutralToBegin);
	normalAttackState->AddTransition(neutralToBeginPair);

	BaseTransition* elementalToBegin = new EmptyTransition(); // retour en état initial systématique
	PairTransitionToState* elementalToBeginPair = new PairTransitionToState(beginState, elementalToBegin);
	elementalAttackState->AddTransition(elementalToBeginPair);

	// Escape to begin
	BaseTransition* escapeToBegin = new EmptyTransition();
	PairTransitionToState* escapeToBeginPair = new PairTransitionToState(beginState, escapeToBegin);
	escapeState->AddTransition(escapeToBeginPair);

	machine->SetInitialState(beginState);



}

bool Monster::isMonsterTurn() const
{
	return this->isTurn;
}

void Monster::setMonsterTurn(bool val)
{
	this->isTurn = val;
}

bool Monster::tryExit() const
{
	srand(time(NULL));
	const float rdmElem = (rand() % 100 + 1) * 0.01f;


	if (rdmElem >= 0.75f)
		return true;

	return false;

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
