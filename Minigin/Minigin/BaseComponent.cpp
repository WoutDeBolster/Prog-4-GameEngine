#include "MiniginPCH.h"
#include "BaseComponent.h"

void dae::BaseComponent::FixedUpdate(float)
{
}

void dae::BaseComponent::Render() const
{
}

void dae::BaseComponent::setGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_GameObject = gameObject;
}