#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	//struct Movement
	//{
	//	bool MoveLeft{ false };
	//	bool MoveRight{ false };
	//	bool MoveUp{ false };
	//	bool MoveDown{ false };
	//};

	class PlayerComp final : public BaseComponent, public Subject
	{
	public:
		PlayerComp(std::shared_ptr<GameObject> pOwner);
		~PlayerComp() = default;

		PlayerComp(const PlayerComp&) = delete;
		PlayerComp(PlayerComp&&) = delete;
		PlayerComp& operator= (const PlayerComp&) = delete;
		PlayerComp& operator= (const PlayerComp&&) = delete;

		void Update(float fixedTime) override;
		void Die();

		//	void SetMovement(Movement newMovement);
		//	Movement GetMovement();

		//private:
		//	Movement m_Movement;
	};
}

