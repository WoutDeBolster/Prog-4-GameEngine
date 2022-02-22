#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Update(float) = 0;
		virtual void FixedUpdate(float);
		virtual void Render();

		void setGameObject(std::shared_ptr<GameObject> gameObject);

	protected:
		std::weak_ptr<GameObject> m_GameObject;
	};
}
