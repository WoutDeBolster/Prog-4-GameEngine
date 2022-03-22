#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class PeterPepperComp final : public BaseComponent
	{
	public:
		PeterPepperComp(std::shared_ptr<GameObject> pOwner);
		~PeterPepperComp() = default;

		PeterPepperComp(const PeterPepperComp&) = delete;
		PeterPepperComp(PeterPepperComp&&) = delete;
		PeterPepperComp& operator= (const PeterPepperComp&) = delete;
		PeterPepperComp& operator= (const PeterPepperComp&&) = delete;

		void Update(float fixedTime) override;
		void Die();

	private:
		std::unique_ptr<Subject> m_ActorChanged;
	};
}

