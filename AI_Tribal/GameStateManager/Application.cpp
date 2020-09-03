#include "Application.h"
#include "raylib.h"
#include "GameStateManager.h"
#include "IGameState.h"
#include "SplashState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "TestState.h"
#include "GameObject.h"

Application::Application(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth), m_windowHeight(windowHeight)
{

}
Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "Berry Nice");
	SetTargetFPS(60);

	m_gameStateManager = new GameStateManager();
	m_gameStateManager->SetState("Test", new TestState(this)); // Load()
	m_gameStateManager->SetState("Splash", new SplashState(this)); // Load()
	m_gameStateManager->SetState("Menu", new MenuState(this)); // Load()
	//m_gameStateManager->SetState("Play", new PlayState(this)); // Load()
	m_gameStateManager->SetState("Pause", new PauseState(this)); // Load()

	//m_gameStateManager->SetState("Menu", nullptr); // Unload()
	//m_gameStateManager->SetState("Play", new PlayState());
	//m_gameStateManager->SetState("GameOver", new GameOver());
	//m_gameStateManager->SetState("RubenTest", new RubenTestState());

	m_gameStateManager->PushState("Splash");

	//m_gameStateManager->PopState();
	//m_gameStateManager->PushState("Menu");

	//m_gameStateManager->PopState();
	//m_gameStateManager->PushState("Play");

	//m_gameStateManager->PushState("Pause");

    while (!WindowShouldClose() &&  !m_shouldClose)    // Detect window close button or ESC key
    {
		float dt = GetFrameTime();
		Update(dt);
		Draw();
    }
	delete m_gameStateManager;
	CloseWindow();
}

void Application::Update(float deltaTime)
{

	if (IsKeyPressed(KEY_TAB))
		GameObject::SetDebugRendering(!GameObject::IsDebugRendering());

	m_gameStateManager->Update(deltaTime);
}
void Application::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);
	
	m_gameStateManager->Draw();

	EndDrawing();
}

void Application::Close()
{
	m_shouldClose = true;
}