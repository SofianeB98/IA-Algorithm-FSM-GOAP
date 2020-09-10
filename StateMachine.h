#pragma once
#include <vector>

class WorldMaster;
class Monster;

namespace StateMachine
{
	class PairTransitionToState;
	
#pragma region STATE CLASS
	class State
	{
	public:
		std::vector<PairTransitionToState*> Transitions;
		
		State();
		void AddTransition(PairTransitionToState* t);

		virtual ~State();
		
		virtual void OnStateEnter() = 0;
	};
	
#pragma region Default State
	
#pragma endregion 
	
#pragma region Attack State
	class AttackState : public State
	{
	public:
		AttackState() = default;
		
		virtual void OnStateEnter() override;
	};

	class ElementAttackState : public AttackState
	{
	public:
		ElementAttackState();

		virtual void OnStateEnter();
	};

	class NormalAttackState : public AttackState
	{
	public:
		NormalAttackState();

		virtual void OnStateEnter();
	};
#pragma endregion 

#pragma region Escape State
	class EscapeState : public State
	{
	public:
		EscapeState() = default;

		virtual void OnStateEnter() override;
	};
#pragma endregion 

#pragma region Begin State
	class BeginTurnState : public State
	{
	public:
		BeginTurnState() = default;
		virtual void OnStateEnter() override;
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
		BaseTransition() = default;

		virtual ~BaseTransition();

		virtual bool Process(const Monster& mine, Monster& oth) = 0;
	};

	class LifeConditionTransition : public BaseTransition
	{
	public:	

		LifeConditionTransition(bool greater, bool isTargetMine, char life);

		virtual bool Process(const Monster& mine, Monster& oth);

	private:
		bool greater;
		bool isTargetMine;
		char life;
	};

	class UseElementalTransition : public BaseTransition 
	{
		UseElementalTransition();

		virtual bool Process(const Monster& mine, Monster& oth);
	};

	class UseNeutralTransition : public BaseTransition
	{
		UseNeutralTransition();

		virtual bool Process(const Monster& mine, Monster& oth);
	};

	class IsOpponentMyWeaknessTransition : public BaseTransition {
	public:
		IsOpponentMyWeaknessTransition() = default;

		virtual bool Process(const Monster& mine, Monster& oth);
	};

	class EmptyTransition : public BaseTransition {
	public:
		EmptyTransition() = default;

		virtual bool Process(const Monster& mine, Monster& oth);
	};
#pragma endregion 
#pragma endregion

	class PairTransitionToState
	{
	private:
		State* endState;
		BaseTransition* transition;

	public:
		PairTransitionToState(State* state, BaseTransition* tr)
		{
			this->endState = state;
			this->transition = tr;
		};
		
		bool ProcessTransition(const Monster& mine, Monster& oth) const
		{
			return transition->Process(mine, oth);
		};

		State* GetEndState() const
		{
			return this->GetEndState();
		}
	};
}