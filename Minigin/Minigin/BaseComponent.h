#pragma once

namespace dae
{
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;

		virtual void Update() = 0;
	};
}
