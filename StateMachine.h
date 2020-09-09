#pragma once
namespace StateMachine
{
	class StateMachineBase
	{
	public:
		void foo();
	};

	class State
	{
	public:
		void stateFoo();
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
