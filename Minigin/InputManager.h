#pragma once
#include <memory>
#include <map>
#include "Command.h"
#include "XboxController.h"
#include "Singleton.h"

namespace dae
{
	enum class InputType
	{
		keyPressed,
		keyUp,
		keyDown
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		void SetButtonCommand(unsigned int controllerIndex, XboxController::ControllerButton button, Command* command, InputType inputType);

	private:
		XboxController* m_pXboxController = nullptr;
		InputType m_InputType = InputType::keyDown;
		std::vector<XboxController*> m_pControllers;

		std::map<std::pair<unsigned, XboxController::ControllerButton>, std::pair<std::unique_ptr<Command>, InputType>> m_Commands;
	};
}