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
	
}

/*
 * 		char life;
		Element element;
		char healQuantity;
 */