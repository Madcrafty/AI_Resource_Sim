
#include "SplashState.h"
#include "raylib.h"
#include "Application.h"
#include "GameStateManager.h"
#include <iostream>

SplashState::SplashState(Application* app) : m_app(app)
{

}
SplashState::~SplashState() 
{

}

void SplashState::Load()
{
	std::cout << "LOADING SPLASH" << std::endl;
}
void SplashState::Unload()
{
	std::cout << "UNLOADING SPLASH" << std::endl;
}

void SplashState::Update(float dt)
{
	m_timer += dt;
	if (m_timer > 3.0f)
	{
		m_app->GetGameStateManager()->SetState("Splash", nullptr); // unload
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Menu");
		// gameStateMannager->PopState();
		// gameStateMannager->PushState("Menu")
	}
}
void SplashState::Draw()
{
	DrawText("No you", 300, 300, 20, RED);
}