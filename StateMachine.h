#pragma once
#include <vector>

enum Element
{
	FIRE,
	WATER,
	GRASS,

	NEUTRAL
};

namespace StateMachine
{
	class Transition;
	
	class State
	{
	public:
		std::vector<Transition*> Transitions;
		
		State();
		void AddTransition(Transition* t);

		virtual void OnStateEnter();
	};
	
	class StateMachineBase
	{
	private:
		State* currentState;
		
	public:
		StateMachineBase();

		~StateMachineBase()
		{
			delete currentState;
		}
		
		void CreateStateMachine();

		void ProcessState();
		void ChangeState(State* targetState);
		
		State* getCurrentState() const;
	};


	class BaseTransition
	{
	public:
		State* end;
		BaseTransition() {

		}
		BaseTransition(State* end);
		virtual bool Process(FightData* fightData) = 0;
	};
	class FightData {

	};

	class LifeConditionTransition : BaseTransition
	{
	public:	

		LifeConditionTransition(State* endState, bool greater, char life);

		virtual bool Process(const FightData& fightData);

	private:
		bool greater;
		char life;
	};



	


}

/*
 * 		char life;
		Element element;
		char healQuantity;
 */