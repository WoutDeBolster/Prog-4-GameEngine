#pragma once
#include "Observer.h"

namespace dae
{
	enum class Achievement
	{
		Win,
		FirstBlood,
	};

	class Achievements final : public Observer
	{
	public:
		void Notify(const GameObject& actor, Event events) override;
	private:
		void Unlock(Achievement achievement);
		bool m_NoONeElseDied{ true };
	};
}