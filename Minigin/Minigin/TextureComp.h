#pragma once
#include "BaseComponent.h"
#include "TransformComp.h"

namespace dae
{
	class Texture2D;
	class TextureComp final : public BaseComponent
	{
	public:
		TextureComp(const std::string& filename);
		~TextureComp() = default;

		TextureComp(const TextureComp&) = delete;
		TextureComp(TextureComp&&) = delete;
		TextureComp& operator= (const TextureComp&) = delete;
		TextureComp& operator= (const TextureComp&&) = delete;

		void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetTexture(const std::string& filename);

	private:
		TransformComp m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
	};
}

