#include "Action.h"

Action::Action()
{
	this->cost = 1;

	this->preconditions.reserve(5);
	this->effects.reserve(2);
}

Action::Action(int cst) : cost(cst)
{
	this->preconditions = nullptr;
	this->effects = nullptr;
}
void Action::setEffect( Effect* e)
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
	for (auto& e : effects)
	{
		e->applyEffect(gs);
	}
}

bool Action::checkPreconditions(const Action& a) const
{
	bool b = false;

	for (auto& pA : a.getEffects())
	{
		for (auto& p : preconditions)
		{
			b |= p->checkPrecondition(pA->getEffect());
		}
	}

	return b;
}


bool Precondition::checkPrecondition(ActionType gs) const
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