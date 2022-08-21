#include "MiniginPCH.h"
#include "PlayerComp.h"
#include "TransformComp.h"
#include "GameObject.h"

dae::PlayerComp::PlayerComp(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::PlayerComp::Update(float)
{

}

void dae::PlayerComp::Die()
{
	Notify(*m_GameObject.lock().get(), Event::ActorDie);
}

//void dae::PlayerComp::SetMovement(Movement newMovement)
//{
//	m_Movement = newMovement;
//}
//
//dae::Movement dae::PlayerComp::GetMovement()
//{
//	return m_Movement;
//}
