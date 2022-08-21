#pragma once
#include "BaseComponent.h"

namespace dae
{
	class BulletComp final : public BaseComponent
	{
	public:
		BulletComp(std::shared_ptr<GameObject> pOwner, glm::vec2 direction);
		~BulletComp() = default;

		BulletComp(const BulletComp&) = delete;
		BulletComp(BulletComp&&) = delete;
		BulletComp& operator= (const BulletComp&) = delete;
		BulletComp& operator= (const BulletComp&&) = delete;

		void Update(float fixedTime) override;

	private:
		float m_Speed{ 10.f };
		glm::vec2 m_Direction;
	};
}

