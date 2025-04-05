#include "StateMachine.h"

#include "WaitingAction.h"
#include "SpinningReels.h"

#include <random>
#include <iostream>

using namespace std;

StateMachine::StateMachine(BarabanManager& barabanManager)
	: m_BarabanManager(barabanManager), m_CurrentState(nullptr)
{
	setState(make_unique<WaitingAction>());
}

void StateMachine::setState(unique_ptr<State> newState)
{
	m_CurrentState = move(newState);
}

void StateMachine::update(float diff)
{
	m_BarabanManager.update(diff);
	m_CurrentState->update(m_BarabanManager, diff);
	m_CurrentState->changeState(*this);
}

void StateMachine::start()
{
	if (dynamic_cast<WaitingAction*>(m_CurrentState.get()))
	{
		auto waitingAction = make_unique<WaitingAction>();
		waitingAction->startPressed();
		setState(move(waitingAction));
	}
	
}

void StateMachine::stop()
{
	if (dynamic_cast<SpinningReels*>(m_CurrentState.get()))
	{
		auto spiningReels = make_unique<SpinningReels>();
		spiningReels->stopPressed();
		setState(move(spiningReels));
	}
}
