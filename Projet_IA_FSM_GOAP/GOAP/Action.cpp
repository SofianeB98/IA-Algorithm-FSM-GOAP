#include "Action.h"

#pragma region ACTION CLASS
Action::Action()
{
	this->cost = 1;

	this->precondition = nullptr;
	this->effect = nullptr;
}

Action::Action(int cst) : cost(cst)
{
	this->precondition = nullptr;
	this->effect = nullptr;
}

void Action::setEffect(Effect* e)
{
	this->effect = e;
}

void Action::setPrecondition(Precondition* p)
{
	this->precondition = p;
}

Action::~Action()
{
	if (precondition != nullptr)
	{
		delete precondition;
		precondition = nullptr;
	}

	if (effect != nullptr)
	{
		delete effect;
		effect = nullptr;
	}

}

void Action::performAction(GameState& gs) const
{
	effect->applyEffect(gs);
}

bool Action::checkPreconditions(const Action& a) const
{


	return this->precondition->checkPrecondition(a.getEffect()->getEffectType());
}
#pragma endregion 

#pragma region PRECONDITION CLASS
bool Precondition::checkPrecondition(const ActionType oth) const
{
	//return true si la condition == oth
	return this->condition == oth;
}

Precondition::~Precondition()
{

}
#pragma endregion 

#pragma region EFFECT CLASS
void Effect::applyEffect(GameState& gs) const
{
	//Applique l'effet sur le gs
	this->effectFunction(gs);
}

Effect::~Effect()
{

}
#pragma endregion 