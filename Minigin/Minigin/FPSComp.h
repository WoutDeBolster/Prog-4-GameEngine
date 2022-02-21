#pragma once
#include "BaseComponent.h"
namespace dae
{
	class FPSComp final : public BaseComponent
	{
	public:
		FPSComp() = default;
		~FPSComp() = default;

		FPSComp(const FPSComp&) = delete;
		FPSComp(FPSComp&&) = delete;
		FPSComp& operator= (const FPSComp&) = delete;
		FPSComp& operator= (const FPSComp&&) = delete;

		void Update() override;

		float GetFPS() const { return m_FPS; };

	private:
		// adding text comp ones name fixed
		float m_FPS;
	};
}

