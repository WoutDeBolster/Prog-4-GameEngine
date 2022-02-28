#include "MiniginPCH.h"
#include "FPSComp.h"
#include "GameObject.h"
#include "TextComp.h"

void dae::FPSComp::Update(float deltaTime)
{
	m_FPS = static_cast<int>(1.f / deltaTime);
	m_GameObject.lock().get()->getComponent<TextComp>()->SetText(std::to_string(m_FPS) + "FPS");
}

int dae::FPSComp::GetFPS() const
{
	return m_FPS;
}
