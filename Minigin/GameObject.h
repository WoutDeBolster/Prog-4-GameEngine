#pragma once
#include "TransformComp.h"

namespace dae
{
	class BaseComponent;
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject() = default;
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void FixedUpdate(float fixedTime);
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;

		// components
		void addComponent(std::shared_ptr<BaseComponent> myComponent);
		template <typename T>
		std::shared_ptr<T> getComponent() const
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
		void RemoveComponent(std::shared_ptr<BaseComponent> myComponent);

		// parent
		void SetParent(std::shared_ptr<GameObject> parent);
		std::shared_ptr<GameObject> GetParent() const;

		// child
		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(size_t idx) const;
		void RemoveChild(size_t idx);
		void AddChild(std::shared_ptr<GameObject> child);

	private:
		TransformComp m_Transform;
		std::weak_ptr<GameObject> m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Childeren;
	};
}
