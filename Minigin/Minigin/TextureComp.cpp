#include "MiniginPCH.h"
#include "TextureComp.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"

dae::TextureComp::TextureComp(const std::string& filename)
{
	SetTexture(filename);
}

void dae::TextureComp::Update(float)
{
}

void dae::TextureComp::Render()
{
	const auto& pos = m_GameObject.lock().get()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::TextureComp::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
