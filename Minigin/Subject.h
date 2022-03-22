#pragma once
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:

		void AddObserver(std::shared_ptr<Observer> observer);
		void RemoveObserver(std::shared_ptr<Observer> observer);

	protected:
		void Notify(const GameObject& actor, Event events);

	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
		int m_NumObservers{ 0 };
	};
}

