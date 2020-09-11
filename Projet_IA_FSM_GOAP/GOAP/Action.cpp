#include "Action.h"

Action::Action()
{
	this->cost = 1;

	this->preconditions.reserve(5);
	this->effects.reserve(2);
}

Action::Action(int cst) : cost(cst)
{
	this->preconditions.reserve(5);
	this->effects.reserve(2);
}

void Action::addEffects(const Effect& e)
{
	this->effects.emplace_back(e);
}

void Action::addPreconditions(const Precondition& p)
{
	this->preconditions.emplace_back(p);
}

Action::~Action()
{
	for (auto& p : preconditions)
	{
		if (p != nullptr)
		{
			delete p;
			p = nullptr;
		}
	}
	preconditions.clear();

	for (auto& e : effects)
	{
		if (e != nullptr)
		{
			delete e;
			e = nullptr;
		}
	}
	effects.clear();
}

void Action::performAction(GameState& gs) const
{
	for(auto& e : effects)
	{
		e->applyEffect(gs);
	}
}

bool Action::checkPreconditions(const Action& a) const
{
	bool b = false;
	
	for (auto& p : preconditions)
	{
		for (auto& pA : a.getEffects())
		{
			b |= p->checkPrecondition(pA->getEffect());
		}
	}
	
	return b;
}


bool Precondition::checkPrecondition(ConditionType gs) const
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