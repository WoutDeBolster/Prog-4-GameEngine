#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class PointsComp final : public BaseComponent, public Subject
	{
	public:
		PointsComp(std::shared_ptr<GameObject> pOwner, int points);
		~PointsComp() = default;

		PointsComp(const PointsComp&) = delete;
		PointsComp(PointsComp&&) = delete;
		PointsComp& operator= (const PointsComp&) = delete;
		PointsComp& operator= (const PointsComp&&) = delete;

		void Update(float fixedTime) override;
		void AddPoints(int amount);

		int GetPoints();

	private:
		int m_Points{ 0 };
	};
}

