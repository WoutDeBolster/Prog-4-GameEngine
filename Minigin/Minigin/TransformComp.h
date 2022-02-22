#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComp final : public BaseComponent
	{
	public:
		TransformComp() = default;
		virtual ~TransformComp() = default;

		TransformComp(const TransformComp&) = delete;
		TransformComp(TransformComp&&) = delete;
		TransformComp& operator= (const TransformComp&) = delete;
		TransformComp& operator= (const TransformComp&&) = delete;

		void Update(float deltaTime) override;

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
