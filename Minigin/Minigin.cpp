#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComp.h"
#include "GameObject.h"	
#include "Scene.h"
#include "FPSComp.h"
#include "TextureComp.h"
#include "ImguiComp.h"

#include <chrono>

using namespace std;
using namespace std::chrono;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// background
	std::shared_ptr<TextureComp> textureBackground = std::make_shared<TextureComp>("background.jpg");
	auto go = std::make_shared<GameObject>();
	textureBackground->setGameObject(go);
	go->addComponent(textureBackground);
	scene.Add(go);

	// dae logo
	std::shared_ptr<TextureComp> textureLogo = std::make_shared<TextureComp>("logo.png");

	go = std::make_shared<GameObject>();
	textureLogo->setGameObject(go);
	go->addComponent(textureLogo);
	go->SetPosition(216, 180);
	scene.Add(go);

	// top text
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<TextComp> text = std::make_shared<TextComp>("Programming 4 Assignment", font);

	auto to = std::make_shared<GameObject>();
	text->setGameObject(to);
	to->SetPosition(80, 20);
	to->addComponent(text);
	scene.Add(to);

	// FPSComp
	std::shared_ptr<FPSComp> FPS = std::make_shared<FPSComp>();
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	std::shared_ptr<TextComp> text2 = std::make_shared<TextComp>(std::to_string(FPS->GetFPS()), font2);

	auto FPSCompCounter = std::make_shared<GameObject>();
	FPS->setGameObject(FPSCompCounter);
	text2->setGameObject(FPSCompCounter);
	FPSCompCounter->SetPosition(10, 10);
	FPSCompCounter->addComponent(FPS);
	FPSCompCounter->addComponent(text2);
	scene.Add(FPSCompCounter);

	// ImguiComp
	std::shared_ptr<ImguiComp> imgui = std::make_shared<ImguiComp>(m_Window);

	auto ImguiObj = std::make_shared<GameObject>();
	imgui->setGameObject(ImguiObj);
	ImguiObj->addComponent(imgui);
	scene.Add(ImguiObj);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto lastTime = high_resolution_clock::now();
		float lag = 0;

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		input.SetButtonCommand(0, XboxController::ControllerButton::ButtonA, new JumpCommand, InputType::keyPressed);
		input.SetButtonCommand(0, XboxController::ControllerButton::ButtonB, new FireCommand, InputType::keyPressed);
		input.SetButtonCommand(0, XboxController::ControllerButton::ButtonX, new DuckCommand, InputType::keyPressed);
		input.SetButtonCommand(0, XboxController::ControllerButton::ButtonY, new FartCommand, InputType::keyPressed);

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			while (lag >= static_cast<float>(MsPerFrame / 1000.f))
			{
				sceneManager.FixedUpdate(deltaTime);
				lag -= MsPerFrame;
			}
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
