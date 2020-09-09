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
