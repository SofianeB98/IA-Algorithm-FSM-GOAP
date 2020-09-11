#pragma once

#include <functional>
#include <vector>

class Action;
class GameState;

//Tout les type d'action possible, sera stocker dans les effet et precondition
//afin de les compare
enum ActionType
{
	BUILD_HOUSE,
	STOCK_WOOD,
	HAVE_AXE,
	BUILD_AXE,
	NO_ACTION //Permet de dire qu'il n'y a pas de precondition necessaire
};

/// <summary>
/// La classe effet repond au condition et applique l'action sur le gamestate
/// </summary>
class Effect
{
private:
	ActionType effect;
	std::function<void(GameState&)> effectFunction; //Lambda stocké qui sera appliqué sur une ref de gamestate
public:
	Effect() = default;
	Effect(const ActionType c) : effect(c) {}

	~Effect();
	
	void applyEffect(GameState& gs) const; //applique l'effet sur un gamestate donné
	
	void setEffect(std::function<void(GameState&)> fctn)
	{
		effectFunction = std::move(fctn);
	}
	ActionType getEffectType() const
	{
		return this->effect;
	}
};

/// <summary>
/// La calsse precondition demande a une autre action si son effet correspond
/// ET lorsqu'on applique les effet, demande au Gamestate s'il est necessaire d'appliquer cet effet
/// </summary>
class Precondition
{
	ActionType condition;
	std::function<bool(const GameState&)> preconditionFunction;
public:
	Precondition() = default;
	Precondition(const ActionType c) : condition(c){}
	
	~Precondition();

	//Check la lambda sur un gs donné
	bool checkPreconditionOnGs(const GameState& gs) const
	{
		return preconditionFunction(gs);
	}
	
	void setPrecondition(std::function<bool(const GameState&)> fctn)
	{
		preconditionFunction = std::move(fctn);
	}
	
	bool checkPrecondition(const ActionType c) const;
	ActionType getPrecType() const
	{
		return this->condition;
	}
};

/// <summary>
/// Classe principale (en plus du planner)
/// Contient un precondition, un effet et un coup
/// </summary>
class Action
{
	uint8_t cost;

	Precondition* precondition;
	Effect* effect;
public:
	Action();
	Action(int cst);

	~Action();

	void setEffect( Effect* e);
	void setPrecondition( Precondition* p);

	//Appelle le perform de l'actio nsur le GS
	void performAction(GameState& gs) const;
	
	bool checkPreconditions(const Action& a) const;
	
	const Precondition* getPrecondition() const
	{
		return this->precondition;
	}
	const Effect* getEffect() const
	{
		return this->effect;
	}
	const int getCost() const
	{
		return this->cost;
	}
};