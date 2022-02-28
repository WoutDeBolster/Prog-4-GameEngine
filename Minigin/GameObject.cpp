#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::addComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.push_back(myComponent);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> myComponent)
{
	m_Components.erase(std::find(m_Components.begin(), m_Components.end(), myComponent));
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	if (m_Parent.lock().get() != nullptr)
	{
		for (size_t i = 0; i < m_Childeren.size(); i++)
		{
			m_Parent.lock().get()->RemoveChild(i);
		}
	}
	m_Parent = parent;
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_Parent.lock();
}

size_t dae::GameObject::GetChildCount() const
{
	return m_Childeren.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(size_t idx) const
{
	if (idx < m_Childeren.size())
	{
		return m_Childeren[idx];
	}
	return std::shared_ptr<dae::GameObject>();
}

void dae::GameObject::RemoveChild(size_t idx)
{
	m_Childeren[idx]->SetParent(nullptr);
	m_Childeren.erase(std::find(m_Childeren.begin(), m_Childeren.end(), GetChildAt(idx)));
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_Childeren.push_back(child);
}

void dae::GameObject::FixedUpdate(float fixedTime)
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->FixedUpdate(fixedTime);
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
