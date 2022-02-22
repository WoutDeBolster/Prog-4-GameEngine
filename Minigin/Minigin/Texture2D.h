#pragma once
#include "BaseComponent.h"

struct SDL_Texture;

namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final : public BaseComponent
	{
	public:
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D&) = delete;
		Texture2D(Texture2D&&) = delete;
		Texture2D& operator= (const Texture2D&) = delete;
		Texture2D& operator= (const Texture2D&&) = delete;

		void Update() override;

		SDL_Texture* GetSDLTexture() const { return m_Texture; };

	private:
		SDL_Texture* m_Texture;
	};
}
