#pragma once
#include <iostream>
#include "PeterPepperComp.h"

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};

	class JumpCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Jumped!\n"; }
		void Undo() override { std::cout << "Player Undo Jumped!\n"; }
	};

	class FireCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Fired!\n"; }
		void Undo() override { std::cout << "Player Undo Fired!\n"; }
	};

	class DuckCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Crouched!\n"; }
		void Undo() override { std::cout << "Player Undo Crouched!\n"; }
	};

	class FartCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Fart!\n"; }
		void Undo() override { std::cout << "Player Undo Fart!\n"; }
	};

	class KillCommand final : public Command
	{
	public:
		KillCommand(std::shared_ptr<PeterPepperComp> player);

		void Execute() override { m_Player.lock().get()->Die(); }
		void Undo() override { std::cout << "Player Undo Killed!\n"; }

	private:
		std::weak_ptr<PeterPepperComp> m_Player;
	};
}
