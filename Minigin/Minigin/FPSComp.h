#pragma once
#include "BaseComponent.h"
namespace dae
{

	class TextComp;
	class FPSComp final : public BaseComponent
	{
	public:
		FPSComp() = default;
		~FPSComp() = default;

		FPSComp(const FPSComp&) = delete;
		FPSComp(FPSComp&&) = delete;
		FPSComp& operator= (const FPSComp&) = delete;
		FPSComp& operator= (const FPSComp&&) = delete;

		void Update(float deltaTime) override;

		int GetFPS() const;

	private:
		int m_FPS;
		int m_Frames;
		float m_Time;
	};
}

