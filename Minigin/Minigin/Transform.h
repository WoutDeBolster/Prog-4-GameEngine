#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Transform final : public BaseComponent
	{
	public:
		Transform() = default;
		virtual ~Transform() = default;

		Transform(const Transform&) = delete;
		Transform(Transform&&) = delete;
		Transform& operator= (const Transform&) = delete;
		Transform& operator= (const Transform&&) = delete;

		void Update(float) override;

		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
