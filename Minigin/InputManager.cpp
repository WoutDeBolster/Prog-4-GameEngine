#include "MiniginPCH.h"
#include "InputManager.h"

dae::InputManager::InputManager()
{
	m_pControllers.push_back(new XboxController(0));
}

dae::InputManager::~InputManager()
{
	for (size_t i = 0; i < m_pControllers.size(); ++i)
	{
		delete m_pControllers[i];
	}
}

bool dae::InputManager::ProcessInput()
{
	for (size_t i = 0; i < m_pControllers.size(); ++i)
	{
		m_pControllers[i]->Update();

		for (auto CommandsIterator = m_Commands.begin(); CommandsIterator != m_Commands.end(); ++CommandsIterator)
		{
			switch (CommandsIterator->second.second)
			{
			case dae::InputType::keyPressed:
				if (m_pControllers[i]->IsPressed(CommandsIterator->first.second))
				{
					CommandsIterator->second.first.get()->Execute();
				}
				break;
			case dae::InputType::keyUp:
				if (m_pControllers[i]->IsUp(CommandsIterator->first.second))
				{
					CommandsIterator->second.first.get()->Execute();
				}
				break;
			case dae::InputType::keyDown:
				if (m_pControllers[i]->IsDown(CommandsIterator->first.second))
				{
					CommandsIterator->second.first.get()->Execute();
				}
				break;
			default:
				continue;
				break;
			}

			if (m_pControllers[i]->IsPressed(XboxController::ControllerButton::LeftShoulder))
			{
				return false;
			}
		}
	}

	return true;
}

void dae::InputManager::SetButtonCommand(unsigned int controllerIndex, XboxController::ControllerButton button,
	Command* command, InputType InputType)
{
	m_Commands[std::make_pair(controllerIndex, button)] = std::make_pair(std::unique_ptr<Command>(command), InputType);
}
