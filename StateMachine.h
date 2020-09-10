#pragma once
#include <vector>

class WorldMaster;
class Monster;

namespace StateMachine
{	
	class BaseTransition;

#pragma region STATE CLASS
	class State
	{
	public:
		std::vector<BaseTransition*> Transitions;
		
		State();
		void AddTransition(BaseTransition* t);

		virtual ~State();
		
		virtual void OnStateEnter() = 0;
	};
	
#pragma region Default State
	
#pragma endregion 
	
#pragma region Attack State
	class AttackState : public State
	{
	public:
		AttackState();
		
		virtual void OnStateEnter() = 0;
	};

	class ElementAttackState : public AttackState
	{
	public:
		ElementAttackState();

		virtual void OnStateEnter() = 0;
	};

	class NormalAttackState : public AttackState
	{
	public:
		NormalAttackState();

		virtual void OnStateEnter() = 0;
	};
#pragma endregion 

#pragma region Escape State
	class EscapeState : public State
	{
	public:
		EscapeState();

		virtual void OnStateEnter() = 0;
	};
#pragma endregion 
	
#pragma endregion 
	
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
		
		void ProcessState(const Monster& mine, Monster& oth);
		void ChangeState(State* targetState);
		
		State* getCurrentState() const;
	};

#pragma region TRANSITION CLASS
	class BaseTransition
	{
	public:
		State* end;
		BaseTransition() {

		}
		BaseTransition(State* end);
		virtual bool Process(const Monster& mine, Monster& oth) = 0;
	};

	class LifeConditionTransition : BaseTransition
	{
	public:	

		LifeConditionTransition(State* endState, bool greater, char life);

		virtual bool Process(const Monster& mine, Monster& oth);

	private:
		bool greater;
		char life;
	};
#pragma endregion 
}