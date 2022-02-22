#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComp final : public BaseComponent
	{
	public:
		void Update(float) override;
		void Render() const;

		void SetText(const std::string& text);

		explicit TextComp(const std::string& text, const std::shared_ptr<Font>& Font);
		virtual ~TextComp() = default;
		TextComp(const TextComp& other) = delete;
		TextComp(TextComp&& other) = delete;
		TextComp& operator=(const TextComp& other) = delete;
		TextComp& operator=(TextComp&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
