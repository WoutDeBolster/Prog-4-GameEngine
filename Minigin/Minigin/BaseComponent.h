#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void setGameObject(std::shared_ptr<GameObject> gameObject);

	protected:
		std::weak_ptr<GameObject> m_GameObject;
	};
}
