#include "StateMachine.h"
#include <iostream>

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

	this->currentState = targetState;

	this->currentState->OnStateEnter();
	
	delete prevState;
}

void StateMachine::StateMachineBase::ProcessState()
{
	for (int i = 0; i < this->currentState->Transitions.size(); ++i)
	{
		if (currentState->Transitions[i])
			ChangeState(new State());
	}
}

#pragma region STATE CLASS
StateMachine::State::State()
{
	this->Transitions.reserve(5);
}

void StateMachine::State::AddTransition(Transition* i)
{
	this->Transitions.push_back(i);
}

void StateMachine::State::OnStateEnter()
{
	//process
}
#pragma endregion
