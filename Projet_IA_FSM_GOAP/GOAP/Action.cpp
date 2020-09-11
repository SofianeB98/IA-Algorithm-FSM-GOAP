#include "Action.h"

Action::Action()
{
	this->cost = 1;

	this->preconditions = nullptr;
	this->effects = nullptr;
}

Action::Action(int cst) : cost(cst)
{
	this->preconditions = nullptr;
	this->effects = nullptr;
}
void Action::setEffect(Effect* e)
{
	this->effects = e;
}

void Action::setPrecondition(Precondition* p)
{
	this->preconditions = p;
}

Action::~Action()
{
	if (preconditions != nullptr)
	{
		delete preconditions;
		preconditions = nullptr;
	}

	if (effects != nullptr)
	{
		delete effects;
		effects = nullptr;
	}

}

void Action::performAction(GameState& gs) const
{
	effects->applyEffect(gs);

}

bool Action::checkPreconditions(const Action& a) const
{


	return this->preconditions->checkPrecondition(a.getEffects()->getEffectType());
}


bool Precondition::checkPrecondition(const ActionType gs) const
{
	return this->condition == gs;
}


Precondition::~Precondition()
{

}




Effect::~Effect()
{

}

void Effect::applyEffect(GameState& gs) const
{
	this->effectFunction(gs);
}