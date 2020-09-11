#pragma once


#include <iostream>
#include <functional>
#include <string>
#include <vector>

class GameState;

class Effect
{
public:
	std::string pName;
	bool val;

	void applyEffect(/**/);
};


class Precondition
{
public:
	std::string pName;
	bool val;

	void checkPrecondition(const Effect& effect);
};


class Action
{
	std::string actionName;

	uint8_t cost;

	std::vector<Precondition> preconditions;
	std::vector<Effect> effects; //std::pair<const std::string, const bool>
public:
	Action();
	Action(const std::string& name, int cost);

	void performAction(std::function<void(GameState&)> fctn);

	const int getCost() const
	{
		return this->cost;
	}
	const std::string getActionName() const
	{
		return this->actionName;
	}
};