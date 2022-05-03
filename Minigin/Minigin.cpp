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
#include "PeterPepperComp.h"
#include "Achievements.h"
#include "HealthComp.h"
#include "PointsComp.h"
#include "SoundSystem.h"

#include <chrono>
//#include <steam_api.h>

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

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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
	TestSound();

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
	std::shared_ptr<TextComp> text = std::make_shared<TextComp>(to, "Programming 4 Assignment"
		, font, SDL_Color(255, 255, 255));
	Transform = std::make_shared<TransformComp>(to);

	to->addComponent(text);
	to->addComponent(Transform);

	to->SetPosition(80, 20);
	scene.Add(to);

	// FPSComp
	auto FPSCompCounter = std::make_shared<GameObject>();
	std::shared_ptr<FPSComp> FPS = std::make_shared<FPSComp>(FPSCompCounter);
	std::shared_ptr<Font> font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	std::shared_ptr<TextComp> text2 = std::make_shared<TextComp>(FPSCompCounter, std::to_string(FPS->GetFPS())
		, font2, SDL_Color(255, 255, 255));
	Transform = std::make_shared<TransformComp>(FPSCompCounter);

	FPSCompCounter->addComponent(FPS);
	FPSCompCounter->addComponent(text2);
	FPSCompCounter->addComponent(Transform);

	FPSCompCounter->SetPosition(10, 10);
	scene.Add(FPSCompCounter);

	//// ImguiComp
	//auto ImguiObj = std::make_shared<GameObject>();
	//std::shared_ptr<ImguiComp> imgui = std::make_shared<ImguiComp>(ImguiObj, m_Window);

	//ImguiObj->addComponent(imgui);
	////scene.Add(ImguiObj);

	// Player 1
	// playerComp
	std::shared_ptr<Achievements> achievements = std::make_shared<Achievements>();
	auto playerObj = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(playerObj);

	std::shared_ptr<PeterPepperComp> peter = std::make_shared<PeterPepperComp>(playerObj);
	peter->AddObserver(achievements);

	playerObj->addComponent(Transform);
	playerObj->addComponent(peter);

	scene.Add(playerObj);

	// health
	auto HealthObj = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(HealthObj);
	std::shared_ptr<HealthComp> health = std::make_shared<HealthComp>(HealthObj, 3);
	health->AddObserver(achievements);
	text = std::make_shared<TextComp>(HealthObj, " Lives: " + std::to_string(health->GetHealth()), font2, SDL_Color(0, 255, 0));

	HealthObj->addComponent(Transform);
	HealthObj->addComponent(health);
	HealthObj->addComponent(text);

	HealthObj->SetPosition(10, 250);
	scene.Add(HealthObj);

	// points
	auto PointsObj = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(PointsObj);
	std::shared_ptr<PointsComp> points = std::make_shared<PointsComp>(PointsObj, 0);
	points->AddObserver(achievements);
	text2 = std::make_shared<TextComp>(PointsObj, " Pionts: " + std::to_string(points->GetPoints()), font2, SDL_Color(0, 255, 0));

	PointsObj->addComponent(Transform);
	PointsObj->addComponent(points);
	PointsObj->addComponent(text2);

	PointsObj->SetPosition(10, 300);
	scene.Add(PointsObj);

	// Player 2
	// playerComp
	std::shared_ptr<Achievements> achievements2 = std::make_shared<Achievements>();
	auto playerObj2 = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(playerObj2);

	peter = std::make_shared<PeterPepperComp>(playerObj2);
	peter->AddObserver(achievements2);

	playerObj2->addComponent(Transform);
	playerObj2->addComponent(peter);

	scene.Add(playerObj);

	// health
	auto HealthObj2 = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(HealthObj2);
	std::shared_ptr<HealthComp> health2 = std::make_shared<HealthComp>(HealthObj2, 3);
	health2->AddObserver(achievements2);
	text = std::make_shared<TextComp>(HealthObj2, " Lives: " + std::to_string(health2->GetHealth()), font2, SDL_Color(255, 255, 0));

	HealthObj2->addComponent(Transform);
	HealthObj2->addComponent(health2);
	HealthObj2->addComponent(text);

	HealthObj2->SetPosition(10, 350);
	scene.Add(HealthObj2);

	// points
	auto PointsObj2 = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(PointsObj2);
	std::shared_ptr<PointsComp> points2 = std::make_shared<PointsComp>(PointsObj2, 0);
	points2->AddObserver(achievements2);
	text2 = std::make_shared<TextComp>(PointsObj2, " Pionts: " + std::to_string(points2->GetPoints()), font2, SDL_Color(255, 255, 0));

	PointsObj2->addComponent(Transform);
	PointsObj2->addComponent(points2);
	PointsObj2->addComponent(text2);

	PointsObj2->SetPosition(10, 400);
	scene.Add(PointsObj2);

	// explations
	// EndGame
	auto expl = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(expl);
	text = std::make_shared<TextComp>(expl, "To end game Press RightBumper", font2, SDL_Color(200, 200, 200));

	expl->addComponent(Transform);
	expl->addComponent(text);

	expl->SetPosition(10, 90);
	scene.Add(expl);

	// player 1
	expl = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(expl);
	text = std::make_shared<TextComp>(expl, "Player1: Decrease Health: Dpad_Down | increase points: Dpad_Up", font2, SDL_Color(200, 200, 200));

	expl->addComponent(Transform);
	expl->addComponent(text);

	expl->SetPosition(10, 120);
	scene.Add(expl);

	// player 2
	expl = std::make_shared<GameObject>();
	Transform = std::make_shared<TransformComp>(expl);
	text = std::make_shared<TextComp>(expl, "Player2: Decrease Health: Dpad_Right | increase points: Dpad_Left", font2, SDL_Color(200, 200, 200));

	expl->addComponent(Transform);
	expl->addComponent(text);

	expl->SetPosition(10, 150);
	scene.Add(expl);


	// input
	auto& input = InputManager::GetInstance();

	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonA, new JumpCommand, InputType::keyDown);
	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonB, new FireCommand, InputType::keyDown);
	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonX, new DuckCommand, InputType::keyDown);
	input.SetButtonCommand(0, XboxController::ControllerButton::ButtonY, new FartCommand, InputType::keyDown);
	//input.SetButtonCommand(0, XboxController::ControllerButton::RightShoulder, new KillCommand(peter), InputType::keyDown);
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Down, new DammageCommand(HealthObj.get()->getComponent<HealthComp>()), InputType::keyDown);
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Right, new DammageCommand(HealthObj2.get()->getComponent<HealthComp>()), InputType::keyDown);
	input.SetButtonCommand(1, XboxController::ControllerButton::Dpad_Up, new IncreasePointsCommand(PointsObj.get()->getComponent<PointsComp>()), InputType::keyDown);
	input.SetButtonCommand(1, XboxController::ControllerButton::Dpad_Left, new IncreasePointsCommand(PointsObj2.get()->getComponent<PointsComp>()), InputType::keyDown);
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
			//SteamAPI_RunCallbacks();

			while (lag >= static_cast<float>(m_FixedTimeStep / 1000.f))
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

void dae::Minigin::TestSound() const
{
#if _DEBUG
	ServisLocator::RegisterSoundSystem(std::make_shared<LogginSoundSystem>(std::make_shared<SdlSoundSystem>()));
#else
	ServisLocator::RegisterSoundSystem(std::make_shared<SdlSoundSystem>());
#endif

	//ServisLocator::RegisterSoundSystem(std::make_shared<LogginSoundSystem>(std::make_shared < SdlSoundSystem>()));

	ServisLocator::GetSoundSystem().InitSoundSystem();
	ServisLocator::GetSoundSystem().RegisterSound(0, "../Data/05 Jingle #01.mp3");
	ServisLocator::GetSoundSystem().play(0, 80);
}
