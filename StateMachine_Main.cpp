#include <iostream>
#include "StateMachine.h"

using namespace StateMachine;

int main()
{
	State state;
	state.stateFoo();

	StateMachineBase machine;
	machine.foo();
	
    std::cout << "Hello World!\n";

	return EXIT_SUCCESS;
}