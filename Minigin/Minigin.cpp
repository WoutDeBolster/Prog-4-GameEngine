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
#include "PlayerComp.h"

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

	// Player 1
	std::shared_ptr<GameObject> healthObj{ MakeHealthObj(10, 250, 3, font2, SDL_Color(0, 255, 0)) };
	scene.Add(healthObj);
	std::shared_ptr<GameObject> pointsObj{ MakePointObj(10, 300, 0, font2, SDL_Color(0, 255, 0)) };
	scene.Add(pointsObj);
	std::shared_ptr<GameObject> PlayerObj = MakePlayerObj(healthObj, pointsObj);
	scene.Add(PlayerObj);

	// Player 2
	std::shared_ptr<GameObject> healthObj2{ MakeHealthObj(10, 350, 3, font2, SDL_Color(255, 255, 0)) };
	scene.Add(healthObj2);
	std::shared_ptr<GameObject> pointsObj2{ MakePointObj(10, 400, 0, font2, SDL_Color(255, 255, 0)) };
	scene.Add(pointsObj2);
	std::shared_ptr<GameObject> PlayerObj2 = MakePlayerObj(healthObj2, pointsObj2);
	scene.Add(PlayerObj2);

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
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Down, new DammageCommand(healthObj.get()->getComponent<HealthComp>()), InputType::keyDown);
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Right, new DammageCommand(healthObj2.get()->getComponent<HealthComp>()), InputType::keyDown);
	input.SetButtonCommand(1, XboxController::ControllerButton::Dpad_Up, new IncreasePointsCommand(pointsObj.get()->getComponent<PointsComp>()), InputType::keyDown);
	input.SetButtonCommand(1, XboxController::ControllerButton::Dpad_Left, new IncreasePointsCommand(healthObj2.get()->getComponent<PointsComp>()), InputType::keyDown);
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

	//LoadGame();
	LoadTankGame();

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

std::shared_ptr<dae::GameObject> dae::Minigin::MakeHealthObj(float x, float y, unsigned int health, std::shared_ptr<Font> font, SDL_Color color) const
{
	// health
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	std::shared_ptr<TransformComp> transformC = std::make_shared<TransformComp>(gameObject);
	std::shared_ptr<HealthComp> healthC = std::make_shared<HealthComp>(gameObject, health);
	std::shared_ptr<TextComp> textC = std::make_shared<TextComp>(gameObject, " Lives: " + std::to_string(health), font, color);

	gameObject->addComponent(transformC);
	gameObject->addComponent(healthC);
	gameObject->addComponent(textC);

	gameObject->SetPosition(x, y);

	return gameObject;
}

std::shared_ptr<dae::GameObject> dae::Minigin::MakePointObj(float x, float y, int points, std::shared_ptr<Font> font, SDL_Color color) const
{
	// Points
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	std::shared_ptr<TransformComp> transformC = std::make_shared<TransformComp>(gameObject);
	std::shared_ptr<PointsComp> pointC = std::make_shared<PointsComp>(gameObject, points);
	std::shared_ptr<TextComp> textC = std::make_shared<TextComp>(gameObject, " Points: " + std::to_string(points), font, color);

	gameObject->addComponent(transformC);
	gameObject->addComponent(pointC);
	gameObject->addComponent(textC);

	gameObject->SetPosition(x, y);

	return gameObject;
}

std::shared_ptr<dae::GameObject> dae::Minigin::MakePlayerObj(std::shared_ptr<GameObject> healthObj, std::shared_ptr<GameObject> PointObj) const
{
	// playerComp
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	std::shared_ptr<Achievements> achievements = std::make_shared<Achievements>();
	std::shared_ptr<TransformComp> transformC = std::make_shared<TransformComp>(gameObject);
	std::shared_ptr<PeterPepperComp> peterC = std::make_shared<PeterPepperComp>(gameObject);

	peterC->AddObserver(achievements);
	gameObject->addComponent(transformC);
	gameObject->addComponent(peterC);

	return gameObject;
}

void dae::Minigin::LoadTankGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Tron");

	MakePlayerTank();
	scene.Add(m_PlayerTank);

	// input
	auto& input = InputManager::GetInstance();

	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Left, new MoveLeftCommand(m_PlayerTank, m_Speed), InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Right, new MoveRightCommand(m_PlayerTank, m_Speed), InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Up, new MoveUpCommand(m_PlayerTank, m_Speed), InputType::keyPressed);
	input.SetButtonCommand(0, XboxController::ControllerButton::Dpad_Down, new MoveDownCommand(m_PlayerTank, m_Speed), InputType::keyPressed);

	//input.SetButtonCommand(0, XboxController::ControllerButton::ButtonX, new ShootBulletCommand(m_Bullet), InputType::keyDown);
}

void dae::Minigin::MakePlayerTank()
{
	// tank Obj
	m_PlayerTank = std::make_shared<GameObject>();
	std::shared_ptr<Achievements> achievements = std::make_shared<Achievements>();
	std::shared_ptr<TransformComp> transformC = std::make_shared<TransformComp>(m_PlayerTank);
	std::shared_ptr<TextureComp> textureC = std::make_shared<TextureComp>(m_PlayerTank, "Tanks/PlayerTank.png");
	std::shared_ptr<PlayerComp> tankC = std::make_shared<PlayerComp>(m_PlayerTank);

	tankC->AddObserver(achievements);
	m_PlayerTank->addComponent(transformC);
	m_PlayerTank->addComponent(textureC);
	m_PlayerTank->addComponent(tankC);
}

void dae::Minigin::SpawnBullet()
{
	shared_ptr<GameObject> bullet{ std::make_shared<GameObject>() };
	std::shared_ptr<TransformComp> transformC = std::make_shared<TransformComp>(bullet);
	std::shared_ptr<TextureComp> textureC = std::make_shared<TextureComp>(bullet, "Tanks/BulletPlayer.png");

	bullet->addComponent(transformC);
	bullet->addComponent(textureC);
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
	ServisLocator::GetSoundSystem().RegisterSound(0, "../Data/05_Jingle_01.mp3");
	ServisLocator::GetSoundSystem().play(0, 100);
}
