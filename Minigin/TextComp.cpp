#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "TextComp.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

dae::TextComp::TextComp(std::shared_ptr<GameObject> pOwner, const std::string& text,
	const std::shared_ptr<Font> Font, const SDL_Color& color)
	: BaseComponent(pOwner)
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(Font)
	, m_TextTexture(nullptr)
	, m_Color{ color }
{
}

void dae::TextComp::Update(float)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComp::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_GameObject.lock().get()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextComp::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
