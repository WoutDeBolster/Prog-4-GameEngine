#include "MiniginPCH.h"
#include "Achievements.h"

void dae::Achievements::Notify(const GameObject&, Event events)
{
	switch (events)
	{
	case dae::Event::ActorDie:
		if (m_NoONeElseDied)
		{
			Unlock(Achievement::FirstBlood);
			m_NoONeElseDied = false;
		}
		break;
	case dae::Event::ActorFell:
		break;
	default:
		break;
	}
}

void dae::Achievements::Unlock(Achievement)
{
}
