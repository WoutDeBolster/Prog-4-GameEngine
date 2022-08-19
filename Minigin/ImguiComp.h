#pragma once
#include "BaseComponent.h"
#include <vector>

namespace dae
{
	class ImguiComp final : public BaseComponent
	{
	public:
		ImguiComp(std::shared_ptr<GameObject> pOwner, SDL_Window* pWindow);
		virtual ~ImguiComp();

		ImguiComp(const ImguiComp&) = delete;
		ImguiComp(ImguiComp&&) = delete;
		ImguiComp& operator= (const ImguiComp&) = delete;
		ImguiComp& operator= (const ImguiComp&&) = delete;

		void Update(float deltaTime) override;
		virtual void Render() const override;

		void Exercise1();
		void Exercise2();
		void Exercise3();
	private:
		SDL_Window* m_pWindow{};

		std::vector<float> m_AverageEx1{};
		std::vector<float> m_AverageEx2{};
		std::vector<float> m_AverageEx3{};
		std::vector<float> m_StepSizes{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

		int m_SampleSizeEx1{ 100 };
		int m_SampleSizeEx23{ 10 };

		bool m_StartEx1{ false };
		bool m_StartEx2{ false };
		bool m_StartEx3{ false };
	};
}

