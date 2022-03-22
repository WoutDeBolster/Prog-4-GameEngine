#pragma once
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void Notify(const GameObject& actor, Event events);

	private:
		std::vector<Observer*> m_pObservers;
		int m_NumObservers;
	};
}

