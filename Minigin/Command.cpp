#include "MiniginPCH.h"
#include "Command.h"

dae::KillCommand::KillCommand(std::shared_ptr<PeterPepperComp> player)
	:m_Player{ player }
{
}

dae::DammageCommand::DammageCommand(std::shared_ptr<GameObject> obj)
	: m_GameObj{ obj }
{
}

dae::IncreasePointsCommand::IncreasePointsCommand(std::shared_ptr<GameObject> obj)
	: m_GameObj{ obj }
{
}
