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
