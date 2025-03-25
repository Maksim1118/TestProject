#pragma once

#include "State.h"
#include <memory>

class StateMachine
{
public:
	StateMachine(BarabanManager& barabanManager);

	void start();
	void stop();

	void setState(unique_ptr<State> newState);
	void update(float diff);
private:
	unique_ptr<State> m_CurrentState;
	BarabanManager& m_BarabanManager;
};

