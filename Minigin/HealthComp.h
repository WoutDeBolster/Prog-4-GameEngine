#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComp : public BaseComponent, public Subject
	{
	public:
		HealthComp(std::shared_ptr<GameObject> pOwner, unsigned int health);
		~HealthComp() = default;

		HealthComp(const HealthComp&) = delete;
		HealthComp(HealthComp&&) = delete;
		HealthComp& operator= (const HealthComp&) = delete;
		HealthComp& operator= (const HealthComp&&) = delete;

		void Update(float fixedTime) override;
		void DistractHealth(int amount);

		int GetHealth();

	private:
		unsigned int m_Health{ 3 };
	};
}

