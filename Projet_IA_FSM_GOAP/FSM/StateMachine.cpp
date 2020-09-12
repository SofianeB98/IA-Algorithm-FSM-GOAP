#include "StateMachine.h"
#include <iostream>
#include "Monster.h"
#include "WorldMaster.h"

#pragma region STATE MACHINE CLASS
StateMachine::StateMachineBase::StateMachineBase()
{
	this->currentState = nullptr;
}

const StateMachine::State* StateMachine::StateMachineBase::getCurrentState() const
{
	return this->currentState;
}

// Met à jour l'état courant du monstre et joue l'action associé à l'état
void StateMachine::StateMachineBase::ChangeState(State* targetState, const Monster& mine, Monster& oth)
{
	//State* prevState = this->currentState;

	//this->currentState = nullptr;
	this->currentState = targetState;

	this->currentState->OnStateEnter(mine, oth);

	//delete prevState;
}

// Progresse dans la state machine
void StateMachine::StateMachineBase::ProcessState(const Monster& mine, Monster& oth)
{
	// Pour chaque transition du state courant
	for (int i = 0; i < this->currentState->Transitions.size(); ++i)
	{
		// On test la validité de la transition en passant les deux monstres en paramètres
		if (currentState->Transitions[i]->ProcessTransition(mine, oth))
		{
			// On met à jour la state machine si les conditions pour changer de state sont remplit
			ChangeState(currentState->Transitions[i]->GetEndState(), mine, oth);
			break;
		}
	}
}
// Définit le state initial de la state machine
void StateMachine::StateMachineBase::SetInitialState(State* st)
{
	this->currentState = st;
}

#pragma endregion 


#pragma region STATE CLASS
StateMachine::State::State()
{
	// On réserve par défaut trois emplacement mémoire pour les transitions
	this->Transitions.reserve(3);
}
// Ajoute une transition au vector
void StateMachine::State::AddTransition(PairTransitionToState* t)
{
	this->Transitions.push_back(t);
}

StateMachine::State::~State()
{
	// Delete de toutes les transitions contenues dans le state
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
	// On passe au state suivant pour choisir entre une attaque élémentaire et une attaque neutre
	mine.machine->ProcessState(mine, oth);

}

void StateMachine::BeginTurnState::OnStateEnter(const Monster& mine, Monster& oth)
{
	//std::cout << "--" << std::endl;
}

void StateMachine::ElementAttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << "		- Monster have choosen Element Attack !" << std::endl;
	// On applique les dégats et on passe au state suivant
	oth.takeDamage(10, mine.getElement());
	mine.machine->ProcessState(mine, oth);
}

void StateMachine::NormalAttackState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << "		- Monster have choosen Normal Attack !" << std::endl;
	// On applique les dégats et on passe au state suivant
	oth.takeDamage(10, Element::NEUTRAL);
	mine.machine->ProcessState(mine, oth);
}

void StateMachine::EscapeState::OnStateEnter(const Monster& mine, Monster& oth)
{
	std::cout << " - Monster try to Escape ..." << std::endl;
	// Tentative de fuite
	if (mine.tryExit())
	{
		std::cout << " - Monster escape the battle !" << std::endl;
		WorldMaster::EscapeBattle();
	}
	else
	{
		std::cout << " - Monster no escape..." << std::endl;
	}
	// On passe au state suivant
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
	// Process de la condition de vie.
	// Permet de checker si le monstre du joueur ou le monstre adverse a plus ou moins de x point de vie (variable greater et life)
		
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