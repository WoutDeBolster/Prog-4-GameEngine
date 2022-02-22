#include "MiniginPCH.h"
#include "BaseComponent.h"

void dae::BaseComponent::FixedUpdate(float)
{
}

void dae::BaseComponent::Render()
{
}

void dae::BaseComponent::setGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_pGameObject = gameObject;
}