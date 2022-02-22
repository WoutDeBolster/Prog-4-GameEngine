#pragma once
#include "BaseComponent.h"
namespace dae
{
	class FPS final : public BaseComponent
	{
	public:
		FPS() = default;
		~FPS() = default;

		FPS(const FPS&) = delete;
		FPS(FPS&&) = delete;
		FPS& operator= (const FPS&) = delete;
		FPS& operator= (const FPS&&) = delete;

		void Update() override;

		float GetFPS() const { return m_FPS; };

	private:
		// adding text comp ones name fixed
		float m_FPS;
	};
}

