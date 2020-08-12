#include "PauseState.h"
#include "Application.h"
#include "raylib.h"
#include "Button.h"
#include "GameStateManager.h"
//#include "SplashState.h"
#include "raygui.h"

#include <iostream>

PauseState::PauseState(Application* app) : m_app(app)
{

}
PauseState::~PauseState()
{

}

void PauseState::Load()
{
	std::cout << "LOADING MENU" << std::endl;

	m_pause = LoadTexture("./Sprites/Big_pause_c.png");

	m_play1 = LoadTexture("./Sprites/big_play1_c.png");
	m_play2 = LoadTexture("./Sprites/big_play2_c.png");
	m_play = new Button(" ", &m_play1, &m_play2, Rectangle{ m_app->GetWindowWidth() / 2 - m_boxWidth / 2, m_app->GetWindowHeight() / 2 - m_boxHeight / 2, m_boxWidth, m_boxHeight });
	m_play->OnClick([=]() {
		//m_app->GetGameStateManager()->SetState("Splash", new SplashState(m_app));
		m_app->GetGameStateManager()->PopState();
	});

	m_exit1 = LoadTexture("./Sprites/big_exit1_c.png");
	m_exit2 = LoadTexture("./Sprites/big_exit2_c.png");
	m_exit = new Button(" ", &m_exit1, &m_exit2, Rectangle{ m_app->GetWindowWidth() / 2 - m_boxWidth / 2, m_app->GetWindowHeight() / 2 + m_boxHeight / 2, m_boxWidth, m_boxHeight });
	m_exit->OnClick([=]() {
		m_app->Close();
	});
}
void PauseState::Unload()
{
	std::cout << "UNLOADING MENU" << std::endl;
}

void PauseState::Update(float dt)
{
	m_play->Update();
	m_exit->Update();
}
void PauseState::Draw()
{
	DrawRectangle(0, 0, m_app->GetWindowWidth(), m_app->GetWindowHeight(), Color{ 0,0,0,100 });
	DrawTexture(m_pause, m_app->GetWindowWidth()/2 - m_boxWidth / 2.0f, m_app->GetWindowHeight()/4 - m_boxHeight / 2.0f, WHITE);
	DrawRectangle(m_app->GetWindowWidth() / 2 - m_boxWidth / 2.0f, m_app->GetWindowHeight() / 4 + m_boxHeight / 2.0f, m_boxWidth, 8, WHITE);
	m_play->Draw();
	m_exit->Draw();
}