#include "MiniginPCH.h"
#include "Command.h"

dae::KillCommand::KillCommand(std::shared_ptr<PeterPepperComp> player)
	:m_Player{ player }
{
}
