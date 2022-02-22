#pragma once
#include "TransformComp.h"

namespace dae
{
	class BaseComponent;
	class GameObject final
	{
	public:
		GameObject();
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);

		// components
		void addComponent(std::shared_ptr<BaseComponent> myComponent);
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (std::shared_ptr<BaseComponent> bc : m_Components)
			{
				std::shared_ptr<T> castedPointer = dynamic_pointer_cast<T>(bc);
				if (castedPointer)
				{
					return castedPointer;
				}
			}
			return nullptr;
		}
		std::vector<std::shared_ptr<BaseComponent>> m_Components;
	private:
		TransformComp m_Transform;
	};
}
