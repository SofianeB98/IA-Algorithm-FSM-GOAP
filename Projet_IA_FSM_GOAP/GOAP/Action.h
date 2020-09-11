#pragma once

#include <functional>
#include <vector>

class Action;
class GameState;

enum ConditionType
{
	STOCK_WOOD,
	STOCK_STONE,
	
};

class Effect
{
private:
	ConditionType effect;
	
	std::function<void(GameState&)> effectFunction;
public:
	Effect() = default;
	Effect(const ConditionType c) : effect(c) {}

	~Effect();
	
	void applyEffect(GameState& gs) const;
	
	void setEffect(std::function<void(GameState&)> fctn)
	{
		effectFunction = std::move(fctn);
	}
	ConditionType getEffect() const
	{
		return this->effect;
	}
};


class Precondition
{
	ConditionType condition;
	
public:
	Precondition() = default;
	Precondition(const ConditionType c) : condition(c){}
	
	~Precondition();
	
	bool checkPrecondition(ConditionType c) const;
	ConditionType getPrecondition() const
	{
		return this->condition;
	}
};


class Action
{
	uint8_t cost;

	std::vector<const Precondition*> preconditions;
	std::vector<const Effect*> effects;
public:
	Action();
	Action(int cst);

	~Action();

	void addEffects(const Effect& e);
	void addPreconditions(const Precondition& p);
	
	void performAction(GameState& gs) const;
	
	bool checkPreconditions(const Action& a) const;
	
	const std::vector<const Precondition* > getPreconditions() const
	{
		return this->preconditions;
	}
	const std::vector<const Effect* > getEffects() const
	{
		return this->effects;
	}
	const int getCost() const
	{
		return this->cost;
	}
};