#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
}

void dae::GameObject::addComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.push_back(myComponent);
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	//const auto& pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}
