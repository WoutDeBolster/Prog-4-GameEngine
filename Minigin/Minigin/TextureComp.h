#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class TextureComp final : public BaseComponent
	{
		TextureComp() = default;
		~TextureComp() = default;

		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator= (const TextureComp&) = delete;
		TextureComp& operator= (const TextureComp&&) = delete;

		void Update(float DeltaTime) override;
		void Render() override;

		void SetTexture(const std::string& filename);

	private:
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}

