#include "SpinningReels.h"

#include "StateMachine.h"
#include "ShowingWin.h"

SpinningReels::SpinningReels()
	:m_EndSpin(false),m_StopPressed(false)
{

}

void SpinningReels::update(BarabanManager& barabanManager, float diff)	
{
	barabanManager.setState(BarabanManager::States::Spinning);
	if (m_StopPressed)
	{
		barabanManager.setDecelerating();
		m_StopPressed = false;
	}
		
	if (barabanManager.stopSpinStatus())
		m_EndSpin = true;
}
void SpinningReels::stopPressed()
{
	m_StopPressed = true;
}
void SpinningReels::changeState(StateMachine& stateMachine)
{
	if(m_EndSpin)
		stateMachine.setState(std::make_unique<ShowingWin>());
}