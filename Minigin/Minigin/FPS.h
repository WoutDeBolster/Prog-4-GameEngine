#pragma once
#include "BaseComponent.h"
namespace dae
{

	class TextObject;
	class FPS final : public BaseComponent
	{
	public:
		FPS() = default;
		~FPS() = default;

		FPS(const FPS&) = delete;
		FPS(FPS&&) = delete;
		FPS& operator= (const FPS&) = delete;
		FPS& operator= (const FPS&&) = delete;

		void Update(float DeltaTime) override;

		float GetFPS() const { return m_FPS; };

	private:
		// adding text comp ones name fixed
		std::shared_ptr<TextObject> m_Text;
		float m_FPS;
	};
}

