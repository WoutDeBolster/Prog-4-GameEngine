#include "MiniginPCH.h"
#include "Command.h"

dae::KillCommand::KillCommand(std::shared_ptr<PeterPepperComp> player)
	:m_Player{ player }
{
}

dae::DammageCommand::DammageCommand(std::shared_ptr<HealthComp> health)
	: m_Health{ health }
{
}

dae::IncreasePointsCommand::IncreasePointsCommand(std::shared_ptr<PointsComp> points)
	: m_Points{ points }
{
}

dae::MoveLeftCommand::MoveLeftCommand(std::shared_ptr<GameObject> object, float speed)
	: m_ObjC{ object }
	, m_Speed{ speed }
{
}

dae::MoveRightCommand::MoveRightCommand(std::shared_ptr<GameObject> object, float speed)
	: m_ObjC{ object }
	, m_Speed{ speed }
{
}

dae::MoveUpCommand::MoveUpCommand(std::shared_ptr<GameObject> object, float speed)
	: m_ObjC{ object }
	, m_Speed{ speed }
{
}

dae::MoveDownCommand::MoveDownCommand(std::shared_ptr<GameObject> object, float speed)
	: m_ObjC{ object }
	, m_Speed{ speed }
{
}
