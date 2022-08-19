#include "MiniginPCH.h"
#include "HealthComp.h"
#include "GameObject.h"
#include "TextComp.h"

dae::HealthComp::HealthComp(std::shared_ptr<GameObject> pOwner, unsigned int health)
	:BaseComponent(pOwner)
	, m_Health{ health }
{
}

void dae::HealthComp::Update(float)
{
}

void dae::HealthComp::DistractHealth(int amount)
{
	m_Health -= amount;
	m_GameObject.lock().get()->getComponent<TextComp>()->SetText(" Lives: " + std::to_string(m_Health));

	if (m_Health == 0)
	{
		Notify(*m_GameObject.lock().get(), Event::ActorDie);
	}
}

int dae::HealthComp::GetHealth()
{
	return m_Health;
}
