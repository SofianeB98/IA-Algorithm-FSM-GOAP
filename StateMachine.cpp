#include "StateMachine.h"
#include <iostream>

#pragma region STATE MACHINE CLASS
StateMachine::StateMachineBase::StateMachineBase()
{
	
}

void StateMachine::StateMachineBase::CreateStateMachine()
{
	
}

StateMachine::State* StateMachine::StateMachineBase::getCurrentState() const
{
	return this->currentState;
}

void StateMachine::StateMachineBase::ChangeState(State* targetState)
{
	State* prevState = this->currentState;

	this->currentState = nullptr;
	this->currentState = targetState;

	this->currentState->OnStateEnter();
	
	delete prevState;
}

void StateMachine::StateMachineBase::ProcessState()
{
	for (int i = 0; i < this->currentState->Transitions.size(); ++i)
	{
		if (currentState->Transitions[i])
			ChangeState(currentState->Transitions[i]->end);
	}
}
#pragma endregion 


#pragma region STATE CLASS
StateMachine::State::State()
{
	this->Transitions.reserve(5);
}

void StateMachine::State::AddTransition(const BaseTransition* t)
{
	this->Transitions.push_back(t);
}


StateMachine::State::~State()
{
	for (auto& transition : Transitions)
	{
		delete transition;
	}
}

#pragma endregion

StateMachine::LifeConditionTransition::LifeConditionTransition(State* endState, bool greater, char life) 
{
	this->end = endState;
	this->greater = greater;
	this->life = life;
}

bool StateMachine::LifeConditionTransition::Process(const Monster& mine, Monster& oth)
{
	return false;
}



