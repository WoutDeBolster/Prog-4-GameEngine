#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent&) = delete;
		BaseComponent(BaseComponent&&) = delete;
		BaseComponent& operator= (const BaseComponent&) = delete;
		BaseComponent& operator= (const BaseComponent&&) = delete;

		virtual void Update(float fixedTime) = 0;
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void setGameObject(std::shared_ptr<GameObject> gameObject);

	protected:
		std::weak_ptr<GameObject> m_GameObject;
	};
}
