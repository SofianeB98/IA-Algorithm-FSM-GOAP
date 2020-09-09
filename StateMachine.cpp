#include "StateMachine.h"

#include <iostream>

void StateMachine::StateMachineBase::foo()
{
	std::cout << "State MAchine foo" << std::endl;

}

void StateMachine::State::stateFoo()
{
	std::cout << "State foo" << std::endl;
}

StateMachine::LifeConditionTransition::LifeConditionTransition(State* endState, bool greater, char life) 
{
	this->end = endState;
	this->greater = greater;
	this->life = life;
}

bool StateMachine::LifeConditionTransition::Process(const FightData& fightData)
{
	return false;
}



