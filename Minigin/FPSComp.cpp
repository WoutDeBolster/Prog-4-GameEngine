#include "MiniginPCH.h"
#include "FPSComp.h"
#include "GameObject.h"
#include "TextComp.h"

dae::FPSComp::FPSComp(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::FPSComp::Update(float deltaTime)
{
	m_FPS = static_cast<int>(1.f / deltaTime);
	m_TextUpdateTimer += deltaTime;

	if (m_TextUpdateTimer >= 0.5f)
	{
		m_GameObject.lock().get()->getComponent<TextComp>()->SetText(std::to_string(m_FPS) + "FPS");
		m_TextUpdateTimer = 0.f;
	}
}

int dae::FPSComp::GetFPS() const
{
	return m_FPS;
}
