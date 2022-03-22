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
#include "PeterPepperComp.h"
#include "Achievements.h"

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
	auto go = std::make_shared<GameObject>();
	std::shared_ptr<TextureComp> textureBackground = std::make_shared<TextureComp>(go, "background.jpg");
	std::shared_ptr<TransformComp> Transform = std::make_shared<TransformComp>(go);

	go->addComponent(textureBackground);
	go->addComponent(Transform);

	scene.Add(go);

	// dae logo
	go = std::make_shared<GameObject>();
	std::shared_ptr<TextureComp> textureLogo = std::make_shared<TextureComp>(go, "logo.png");
	Transform = std::make_shared<TransformComp>(go);

	go->addComponent(textureLogo);
	go->addComponent(Transform);

	go->SetPosition(216, 180);
	scene.Add(go);

	// top text
	auto to = std::make_shared<GameObject>();
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<TextComp> text = std::make_shared<TextComp>(to, "Programming 4 Assignment", font);
	Transform = std::make_shared<TransformComp>(to);

	to->addComponent(text);
	to->addComponent(Transform);

	to->SetPosition(80, 20);
	scene.Add(to);

	// FPSComp
	auto FPSCompCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComp> FPS = std::make_shared<FPSComp>(FPSCompCounter);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	std::shared_ptr<TextComp> text2 = std::make_shared<TextComp>(FPSCompCounter, std::to_string(FPS->GetFPS()), font2);
	Transform = std::make_shared<TransformComp>(FPSCompCounter);

	FPSCompCounter->addComponent(FPS);
	FPSCompCounter->addComponent(text2);
	FPSCompCounter->addComponent(Transform);

	FPSCompCounter->SetPosition(10, 10);
	scene.Add(FPSCompCounter);

	// ImguiComp
	auto ImguiObj = std::make_shared<GameObject>();
	std::shared_ptr<ImguiComp> imgui = std::make_shared<ImguiComp>(ImguiObj, m_Window);

	ImguiObj->addComponent(imgui);
	scene.Add(ImguiObj);

	// playerComp
	auto playerObj = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(playerObj);
	std::shared_ptr<PeterPepperComp> peter = std::make_shared<PeterPepperComp>(playerObj);
	peter->AddObserver(std::make_shared<Achievements>());


	playerObj->addComponent(Transform);
	playerObj->addComponent(peter);
	scene.Add(playerObj);

	// input
	auto& input = InputManager::GetInstance();

	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonA, new JumpCommand, InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonB, new FireCommand, InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonX, new DuckCommand, InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonY, new FartCommand, InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::RightShoulder, new KillCommand(peter), InputType::keyPressed);
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
