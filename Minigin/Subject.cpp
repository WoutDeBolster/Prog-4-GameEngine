#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
	++m_NumObservers;
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::find(m_pObservers.begin(), m_pObservers.end(), observer));
	--m_NumObservers;
}

void dae::Subject::Notify(const GameObject& actor, Event events)
{
	for (int i = 0; i < m_NumObservers; i++)
	{
		m_pObservers[i]->Notify(actor, events);
	}
}
