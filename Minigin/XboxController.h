#pragma once

namespace dae
{
	class XboxController final
	{
	public:
		enum class ControllerButton
		{
			Dpad_Up = 0x0001,
			Dpad_Down = 0x0002,
			Dpad_Left = 0x0004,
			Dpad_Right = 0x0008,

			GamepadStart = 0x0010,
			GamepadBack = 0x0020,

			LeftThumb = 0x0040,
			RightThumb = 0x0080,

			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,

			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
			//todo: add the other buttons
		};
		explicit XboxController(int controllerIndex);
		~XboxController();

		void Update();

		bool IsDown(ControllerButton button);
		bool IsUp(ControllerButton button);
		bool IsPressed(ControllerButton button);

	private:
		class XboxControllerImpl;
		XboxControllerImpl* pImpl;
	};
}

