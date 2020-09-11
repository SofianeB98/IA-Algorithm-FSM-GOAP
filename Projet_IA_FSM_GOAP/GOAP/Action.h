#pragma once

#include <functional>
#include <vector>

class Action;
class GameState;

enum ActionType
{
	STOCK_WOOD,
	STOCK_STONE,
	
};

class Effect
{
private:
	ActionType effect;
	std::function<void(GameState&)> effectFunction;
public:
	Effect() = default;
	Effect(const ActionType c) : effect(c) {}

	~Effect();
	
	void applyEffect(GameState& gs) const;
	
	void setEffect(std::function<void(GameState&)> fctn)
	{
		effectFunction = std::move(fctn);
	}
	ActionType getEffectType() const
	{
		return this->effect;
	}
};


class Precondition
{
	ActionType condition;
	std::function<bool(const GameState&)> preconditionFunction;
public:
	Precondition() = default;
	Precondition(const ActionType c) : condition(c){}
	
	~Precondition();

	bool checkPreconditionOnGs(const GameState& gs) const
	{
		return preconditionFunction(gs);
	}
	void setPrecondition(std::function<bool(const GameState&)> fctn)
	{
		preconditionFunction = std::move(fctn);
	}
	
	bool checkPrecondition(const ActionType c) const;
	ActionType getPrecondition() const
	{
		return this->condition;
	}
};


class Action
{
	uint8_t cost;

	Precondition* preconditions;
	Effect* effects;
public:
	Action();
	Action(int cst);

	~Action();

	void setEffect( Effect* e);
	void setPrecondition( Precondition* p);
	
	void performAction(GameState& gs) const;
	
	bool checkPreconditions(const Action& a) const;
	
	const Precondition* getPreconditions() const
	{
		return this->preconditions;
	}
	const Effect* getEffects() const
	{
		return this->effects;
	}
	const int getCost() const
	{
		return this->cost;
	}
};