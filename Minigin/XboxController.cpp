#include "MiniginPCH.h"
#include "XboxController.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include <iostream>

using namespace dae;

class XboxController::XboxControllerImpl
{
public:
	XboxControllerImpl(unsigned int controllerIndex);

	void Update();

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviusState{};

	WORD m_ButtonPressedThisFrame;
	WORD m_ButtonReleasedThisFrame;

	unsigned int m_ControlerIndex{ 0 };
};

dae::XboxController::XboxController(int controllerIndex)
{
	pImpl = new XboxControllerImpl(controllerIndex);
}

dae::XboxController::~XboxController()
{
	delete pImpl;
}

void dae::XboxController::Update()
{
	pImpl->Update();
}

bool dae::XboxController::IsDown(ControllerButton button)
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool dae::XboxController::IsUp(ControllerButton button)
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool dae::XboxController::IsPressed(ControllerButton button)
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

//XboxControllerImpl
//------------------
XboxController::XboxControllerImpl::XboxControllerImpl(unsigned int controllerIndex)
{
	ZeroMemory(&m_PreviusState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	m_ControlerIndex = controllerIndex;
}

void XboxController::XboxControllerImpl::Update()
{
	CopyMemory(&m_PreviusState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControlerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviusState.Gamepad.wButtons;
	m_ButtonPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool XboxController::XboxControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonPressedThisFrame & static_cast<int>(button);
}

bool XboxController::XboxControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonReleasedThisFrame & static_cast<int>(button);
}

bool XboxController::XboxControllerImpl::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<int>(button);
}