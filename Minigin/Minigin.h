#pragma once
struct SDL_Window;
class GameObject;

namespace dae
{
	class FPSComp;
	class Minigin
	{
	public:
		void Initialize();
		void LoadGame() const;
		void Cleanup();
		void Run();

	private:
		static const int MsPerFrame = 16; //16 for 60 FPSComp, 33 for 30 FPSComp
		const float m_FixedTimeStep = 0.02f;
		SDL_Window* m_Window{};

		// object functions
		GameObject MakeHealthObj(std::shared_ptr<GameObject> gameObject, unsigned int health, SDL_Color color);
		GameObject MakePointObj(std::shared_ptr<GameObject> gameObject, unsigned int points, SDL_Color color);
		GameObject MakePlayerObj(std::shared_ptr<GameObject> gameObject, std::shared_ptr<GameObject> healthObj, std::shared_ptr<GameObject> PointObj);
	};
}