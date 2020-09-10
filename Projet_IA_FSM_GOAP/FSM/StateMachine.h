#pragma once
#include <iostream>
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
		std::vector<const PairTransitionToState*> Transitions;
		
		State();
		void AddTransition(PairTransitionToState* t);

		virtual ~State();
		
		virtual void OnStateEnter(const Monster& mine, Monster& oth) = 0;
	};
	
#pragma region Default State
	
#pragma endregion 
	
#pragma region Attack State
	class AttackState : public State
	{
	public:
		AttackState() = default;
		
		virtual void OnStateEnter(const Monster& mine, Monster& oth) override;
	};

	class ElementAttackState : public AttackState
	{
	public:
		ElementAttackState() = default;

		virtual void OnStateEnter(const Monster& mine, Monster& oth) override;
	};

	class NormalAttackState : public AttackState
	{
	public:
		NormalAttackState() = default;

		virtual void OnStateEnter(const Monster& mine, Monster& oth) override;
	};
#pragma endregion 

#pragma region Escape State
	class EscapeState : public State
	{
	public:
		EscapeState() = default;

		virtual void OnStateEnter(const Monster& mine, Monster& oth) override;
	};
#pragma endregion 

#pragma region Begin State
	class BeginTurnState : public State
	{
	public:
		BeginTurnState() = default;
		virtual void OnStateEnter(const Monster& mine, Monster& oth) override;
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
			if (currentState != nullptr)
			{
				delete currentState;
				currentState = nullptr;
			}
		}
		
		void ProcessState(const Monster& mine, Monster& oth);
		void ChangeState(State* targetState, const Monster& mine, Monster& oth);

		void SetInitialState(State* st);
		
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

	class LifeConditionAndWeaknessTransition : public BaseTransition
	{
	public:	

		LifeConditionAndWeaknessTransition(char life);

		virtual bool Process(const Monster& mine, Monster& oth);

	private:
		char life;
	};

	class UseElementalTransition : public BaseTransition 
	{
	public:
		UseElementalTransition();

		virtual bool Process(const Monster& mine, Monster& oth);
	};

	class UseNeutralTransition : public BaseTransition
	{
	public:
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
			return this->endState;
		}
	};
}