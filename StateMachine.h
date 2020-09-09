#pragma once
#include <vector>

class FightData;
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
		
		void CreateStateMachine();

		void ProcessState();
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
		virtual bool Process(FightData* fightData) = 0;
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
#pragma endregion 
}