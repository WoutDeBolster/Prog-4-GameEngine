#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject> pOwner)
{
	m_GameObject = pOwner;
}

void dae::BaseComponent::FixedUpdate(float)
{
}

void dae::BaseComponent::Render() const
{
}