#include "MiniginPCH.h"
#include "FPSComp.h"

void dae::FPSComp::Update(float deltaTime)
{
	m_Time += deltaTime;
	++m_Frames;
	if (m_Time > 1.f)
	{
		m_FPS = m_Frames;
		m_Frames = 0;
	}
}

int dae::FPSComp::GetFPS() const
{
	return m_FPS;
}
