#pragma once

#include <functional>
#include <vector>

class Action;
class GameState;

class Effect
{
private:
	std::function<void(GameState&)> effectFunction;
public:
	Effect() = default;
	Effect(std::function<void(GameState&)>& fctn) : effectFunction(std::move(fctn)) {}
	
	void applyEffect(GameState& gs);
};


class Precondition
{
public:
	std::function<bool(int)> effectFunction;
	
	bool checkPrecondition(const Action& act);
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
	
	void performAction(GameState& gs);

	const std::vector<const Precondition* > getPreconditions() const
	{
		return this->preconditions;
		const std::vector<const Precondition* > getPreconditions() const
		{
			return this->preconditions;
		}
		const std::vector<const Precondition* > getPreconditions() const
		{
			return this->preconditions;
		}
		const std::vector<const Precondition* > getPreconditions() const
		{
			return this->preconditions;
			const std::vector<const Precondition* > getPreconditions() const
			{
				return this->preconditions;
			}
			const std::vector<const Precondition* > getPreconditions() const
			{
				return this->preconditions;
			}
		}
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