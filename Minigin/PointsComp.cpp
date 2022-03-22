#include "MiniginPCH.h"
#include "PointsComp.h"
#include "GameObject.h"
#include "TextComp.h"

dae::PointsComp::PointsComp(std::shared_ptr<GameObject> pOwner, int points)
	:BaseComponent(pOwner)
	, m_Points{ points }
{
}

void dae::PointsComp::Update(float)
{

}

void dae::PointsComp::AddPoints(int amount)
{
	m_Points += amount;
	m_GameObject.lock().get()->getComponent<TextComp>()->SetText(" Pionts: " + std::to_string(m_Points));
}

int dae::PointsComp::GetPoints()
{
	return m_Points;
}
