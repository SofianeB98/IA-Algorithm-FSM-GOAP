#include "StateMachine.h"
#include <iostream>
#include "Monster.h"
#include "WorldMaster.h"

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

	for (int i = 0; i < this->currentState->Transitions.size(); ++i)
	{
		if (currentState->Transitions[i]->ProcessTransition(mine, oth))
		{
			ChangeState(currentState->Transitions[i]->GetEndState(), mine, oth);
			break;
		}
	}
}

void StateMachine::StateMachineBase::SetInitialState(State* st)
{
	this->currentState = st;
}

#pragma endregion 


#pragma region STATE CLASS
StateMachine::State::State()
{
	this->Transitions.reserve(3);
}

void StateMachine::State::AddTransition(PairTransitionToState* t)
{
	this->Transitions.push_back(t);
}

StateMachine::State::~State()
{
	for (auto& transition : Transitions)
	{
		if (transition != nullptr)
		{
			delete transition;
			transition = nullptr;
		}
	}

	Transitions.clear();
}

void StateMachine::State::OnStateEnter(const Monster& mine, Monster& oth)
{

}

void StateMachine::AttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << "	- Monster have choosen Attack Action !" << std::endl;

	mine.machine->ProcessState(mine, oth);

}

void StateMachine::BeginTurnState::OnStateEnter(const Monster& mine, Monster& oth)
{
	//std::cout << "--" << std::endl;
}

void StateMachine::ElementAttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << "		- Monster have choosen Element Attack !" << std::endl;

	oth.takeDamage(10, mine.getElement());
	mine.machine->ProcessState(mine, oth);
}

void StateMachine::NormalAttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << "		- Monster have choosen Normal Attack !" << std::endl;
	oth.takeDamage(10, Element::NEUTRAL);
	mine.machine->ProcessState(mine, oth);
}

void StateMachine::EscapeState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << " - Monster try to Escape ..." << std::endl;

	if (mine.tryExit())
	{
		std::cout << " - Monster escape the battle !" << std::endl;
		WorldMaster::EscapeBattle();
	}
	else
	{
		std::cout << " - Monster no escape..." << std::endl;
	}

	mine.machine->ProcessState(mine, oth);
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

StateMachine::LifeConditionTransition::LifeConditionTransition(bool greater, bool isTargetMine, char life)
{
	this->greater = greater;
	this->life = life;
	this->isTargetMine = isTargetMine;
}

bool StateMachine::LifeConditionTransition::Process(const Monster& mine, Monster& oth)
{
	const Monster& target = isTargetMine ? mine : oth;

	if (this->greater)
	{
		if (target.getLife() >= this->life)
			return true;
	}
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

bool StateMachine::LifeConditionAndWeaknessTransition::Process(const Monster& mine, Monster& oth)
{
	if (mine.getLife() < this->life)
		if (mine.getWeakness() == oth.getElement())
			return true;
		
	return false;
}

StateMachine::LifeConditionAndWeaknessTransition::LifeConditionAndWeaknessTransition(char life)
{
	this->life = life;
}