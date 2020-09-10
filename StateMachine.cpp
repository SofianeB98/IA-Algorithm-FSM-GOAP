#include "StateMachine.h"
#include <iostream>
#include "Monster.h"
#pragma region STATE MACHINE CLASS
StateMachine::StateMachineBase::StateMachineBase()
{
	this->currentState = nullptr;
}

StateMachine::State* StateMachine::StateMachineBase::getCurrentState() const
{
	return this->currentState;
}

void StateMachine::StateMachineBase::ChangeState(State* targetState, const Monster& mine, Monster& oth)
{
	//State* prevState = this->currentState;

	//this->currentState = nullptr;
	this->currentState = targetState;

	this->currentState->OnStateEnter(mine, oth);
	
	//delete prevState;
}


void StateMachine::StateMachineBase::ProcessState(const Monster& mine, Monster& oth)
{
	return;
	
	for (int i = 0; i < this->currentState->Transitions.size(); ++i)
	{
		if (currentState->Transitions[i]->ProcessTransition(mine, oth))
		{
			ChangeState(currentState->Transitions[i]->GetEndState(), mine, oth);
			break;
		}
	}
}
#pragma endregion 


#pragma region STATE CLASS
StateMachine::State::State()
{
	this->Transitions.reserve(5);
}

void StateMachine::State::AddTransition(PairTransitionToState* t)
{
	this->Transitions.push_back(t);
}


StateMachine::State::~State()
{
	for (auto& transition : Transitions)
	{
		if(transition != nullptr)
			delete transition;
	}
}
void StateMachine::State::OnStateEnter(const Monster& mine, Monster& oth)
{
	
}

void StateMachine::AttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	
}

void StateMachine::BeginTurnState::OnStateEnter(const Monster& mine, Monster& oth)
{
	
}

void StateMachine::ElementAttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	oth.takeDamage(10, mine.getElement());

	mine.machine->ProcessState(mine, oth);
}

void StateMachine::EscapeState::OnStateEnter(const Monster& mine, Monster& oth)
{
	
}

void StateMachine::NormalAttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	
}


#pragma endregion

#pragma region Life Condition

StateMachine::BaseTransition::~BaseTransition()
{
}

bool StateMachine::BaseTransition::Process(const Monster& mine, Monster& oth)
{
	return false;
}

StateMachine::LifeConditionTransition::LifeConditionTransition( bool greater, bool isTargetMine, char life)
{
	this->greater = greater;
	this->life = life;
	this->isTargetMine = isTargetMine;
}

bool StateMachine::LifeConditionTransition::Process(const Monster& mine, Monster& oth)
{
	Monster target;
	if (this->isTargetMine == true)
		target = mine;
	else
		target = oth;
	
	if (this->greater)
		if (target.getLife() >= this->life)
			return true;
	else
		if (target.getLife() <= this->life)
			return true;

	return false;
}

#pragma endregion

#pragma region Use Elemental transition
StateMachine::UseElementalTransition::UseElementalTransition() {
}

bool StateMachine::UseElementalTransition::Process(const Monster& mine, Monster& oth) {
	if (oth.getWeakness() == mine.getElement())
		return true;
	return false;
}
#pragma endregion

#pragma region Use Elemental transition
StateMachine::UseNeutralTransition::UseNeutralTransition() {
}

bool StateMachine::UseNeutralTransition::Process(const Monster& mine, Monster& oth) {
	if (oth.getWeakness() != mine.getElement())
		return true;
	return false;
}
#pragma endregion

bool StateMachine::IsOpponentMyWeaknessTransition::Process(const Monster& mine, Monster& oth)
{
	if (mine.getWeakness() == oth.getElement())
		return true;
	return false;
}

bool StateMachine::EmptyTransition::Process(const Monster& mine, Monster& oth)
{
	return true;
}
