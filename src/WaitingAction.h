#pragma once

#include "State.h"

class StateMachine;

class WaitingAction : public State
{
public:
	WaitingAction();
	void update(BarabanManager& barabanManager, float diff) override;
	void changeState(StateMachine& stateMachine) override;
	void startPressed();
private:
	bool m_StartPressed;
};