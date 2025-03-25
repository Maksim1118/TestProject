#pragma once

#include "State.h"

class StateMachine;

class ShowingWin : public State
{
public:
	ShowingWin();
	void update(BarabanManager& barabanManager, float diff) override;
	void changeState(StateMachine& stateMachine) override;
private:
	bool m_EndShow;
};