#pragma once

#include "BarabanManager.h"

class StateMachine;

class State
{
public:
	virtual ~State() = default;
	virtual void update(BarabanManager & barabanManager, float diff) = 0;
	virtual void changeState(StateMachine& stateMachine) = 0;
};