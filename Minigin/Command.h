#pragma once
#include <iostream>
#include "PeterPepperComp.h"
#include "HealthComp.h"
#include "PointsComp.h"

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

	class DammageCommand final : public Command
	{
	public:
		DammageCommand(std::shared_ptr<HealthComp> health);

		void Execute() override { m_Health.lock().get()->DistractHealth(1); }
		void Undo() override { std::cout << "Player Undo Killed!\n"; }

	private:
		std::weak_ptr<HealthComp> m_Health;
	};

	class IncreasePointsCommand final : public Command
	{
	public:
		IncreasePointsCommand(std::shared_ptr<PointsComp> points);

		void Execute() override { m_Points.lock().get()->AddPoints(25); }
		void Undo() override { std::cout << "Player Undo Killed!\n"; }

	private:
		std::weak_ptr<PointsComp> m_Points;
	};
}
