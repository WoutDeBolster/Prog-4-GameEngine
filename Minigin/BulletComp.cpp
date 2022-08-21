#include "MiniginPCH.h"
#include "BulletComp.h"
#include "GameObject.h"
#include "TransformComp.h"

dae::BulletComp::BulletComp(std::shared_ptr<GameObject> pOwner, glm::vec2 direction)
	: BaseComponent(pOwner)
	, m_Direction{ direction }
{
}

void dae::BulletComp::Update(float fixedTime)
{
	std::shared_ptr<TransformComp> tranform = m_GameObject.lock().get()->getComponent<TransformComp>();
	if (tranform != nullptr)
	{
		glm::vec3 currentPos{ tranform.get()->GetPosition() };
		currentPos.x += m_Direction.x * m_Speed * fixedTime;
		currentPos.y += m_Direction.y * m_Speed * fixedTime;
	}
}
