#include "ShowingWin.h"

#include "StateMachine.h"
#include "WaitingAction.h"


ShowingWin::ShowingWin()
	:m_EndShow(false)
{

}

void ShowingWin::update(BarabanManager& barabanManager, float diff)
{
	if (barabanManager.getState() == BarabanManager::States::Wait)
		m_EndShow = true;
	else
		barabanManager.setState(BarabanManager::States::ShowWin);
}

void ShowingWin::changeState(StateMachine& stateMachine)
{
	if (m_EndShow)
		stateMachine.setState(make_unique<WaitingAction>());
}