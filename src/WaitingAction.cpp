#include "WaitingAction.h"
#include "StateMachine.h"
#include "SpinningReels.h"

WaitingAction::WaitingAction()
	:m_StartPressed(false)
{

}

void WaitingAction::update(BarabanManager& barabanManager, float diff)
{
	if (m_StartPressed)
		barabanManager.setState(BarabanManager::States::Start);
}
void WaitingAction::startPressed()
{
	m_StartPressed = true;
}

void WaitingAction::changeState(StateMachine& stateMachine)
{
	if(m_StartPressed)
		stateMachine.setState(std::make_unique<SpinningReels>());
}