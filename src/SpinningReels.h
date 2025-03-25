#pragma once
#include "State.h"

class StateMachine;

class SpinningReels : public State
{
public:
	SpinningReels();
	void update(BarabanManager& barabanManager, float diff) override;
	void changeState(StateMachine& stateMachine) override;
	void stopPressed();
private:
	bool m_EndSpin;
	bool m_StopPressed;
};