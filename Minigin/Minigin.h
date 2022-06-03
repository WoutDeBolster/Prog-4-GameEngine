#pragma once
struct SDL_Window;

namespace dae
{
	class FPSComp;
	class GameObject;
	class Font;

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
		std::shared_ptr<GameObject> MakeHealthObj(float x, float y, unsigned int health, std::shared_ptr<Font> font, SDL_Color color) const;
		std::shared_ptr<GameObject> MakePointObj(float x, float y, int points, std::shared_ptr<Font> font, SDL_Color color) const;
		std::shared_ptr<GameObject> MakePlayerObj(std::shared_ptr<GameObject> healthObj, std::shared_ptr<GameObject> PointObj) const;
		std::shared_ptr<GameObject> MakeTextObj(float x, float y, std::string& text, std::shared_ptr<Font> font, SDL_Color& color) const;

		void TestSound() const;
	};
}