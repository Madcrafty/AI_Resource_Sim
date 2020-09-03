
#include "MenuState.h"
#include "Application.h"
#include "raylib.h"
#include "Button.h"
#include "GameStateManager.h"
//#include "SplashState.h"
#include "raygui.h"

#include <iostream>

MenuState::MenuState(Application* app) : m_app(app)
{

}
MenuState::~MenuState()
{

}

void MenuState::Load()
{
	std::cout << "LOADING MENU" << std::endl;
    m_play1 = LoadTexture("./Sprites/big_play1.png");
	m_play2 = LoadTexture("./Sprites/big_play2.png");
	m_play = new Button(" ", &m_play1, &m_play2, Rectangle{m_app->GetWindowWidth()/2 - m_boxWidth/2, m_app->GetWindowHeight() / 2 - m_boxHeight/2, m_boxWidth, m_boxHeight});
	m_play->OnClick([=](){
		//m_app->GetGameStateManager()->SetState("Splash", new SplashState(m_app));
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Test");
	});

	m_exit1 = LoadTexture("./Sprites/big_exit1.png");
	m_exit2 = LoadTexture("./Sprites/big_exit2.png");
	m_exit = new Button(" ", &m_exit1, &m_exit2, Rectangle{ m_app->GetWindowWidth() / 2 - m_boxWidth / 2, m_app->GetWindowHeight() / 2 + m_boxHeight / 2, m_boxWidth, m_boxHeight });
	m_exit->OnClick([=]() {
		m_app->Close();
	});
}
void MenuState::Unload()
{
	std::cout << "UNLOADING MENU" << std::endl;
}

void MenuState::Update(float dt)
{
	m_play->Update();
	m_exit->Update();
}
void MenuState::Draw()
{
	DrawText("Berry Nice", m_app->GetWindowWidth() / 2 - 50, m_app->GetWindowHeight() / 4, 20, DARKGREEN);
	m_play->Draw();
	m_exit->Draw();
}