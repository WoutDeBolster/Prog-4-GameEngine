#include "MiniginPCH.h"
#include "PeterPepperComp.h"

dae::PeterPepperComp::PeterPepperComp(std::shared_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
}

void dae::PeterPepperComp::Update(float)
{

}

void dae::PeterPepperComp::Die()
{
	Notify(*m_GameObject.lock().get(), Event::ActorDie);
}
