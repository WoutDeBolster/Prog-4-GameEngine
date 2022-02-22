#pragma once
struct SDL_Window;

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
		SDL_Window* m_Window{};
	};
}