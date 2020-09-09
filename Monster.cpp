#include "Monster.h"

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
	delete this->machine;
}


void Monster::takeDamage(char val, Element attackElement)
{
	if (attackElement == this->weakness)
		this->life -= val * 2;
	else if (attackElement == Element::NEUTRAL || attackElement == this->element)
		this->life -= val;
	else
		this->life -= val * 0.5f;
}

bool Monster::isAlive()
{
	return this->life > 0;
}
