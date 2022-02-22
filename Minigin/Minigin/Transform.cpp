#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::Update(float)
{

}

const glm::vec3& dae::Transform::GetPosition() const
{
	return m_Position;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
