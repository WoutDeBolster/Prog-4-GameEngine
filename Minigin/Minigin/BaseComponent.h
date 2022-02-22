#pragma once

namespace dae
{
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime);
		virtual void Render();
	};
}
