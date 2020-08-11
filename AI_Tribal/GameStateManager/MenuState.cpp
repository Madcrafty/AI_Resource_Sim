
#include "MenuState.h"
#include "Application.h"
#include "raylib.h"
#include "Button.h"

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
    m_button1 = LoadTexture("./Sprites/big_play1.png");
	m_button2 = LoadTexture("./Sprites/big_play2.png");
	m_play = new Button(" ", &m_button1, &m_button2, Rectangle{m_app->GetWindowWidth()/2 - m_boxWidth, m_app->GetWindowHeight()/2 - m_boxHeight, m_boxWidth, m_boxHeight});
	m_play->OnClick({
		m_gameStateManager->SetState("Splash", new SplashState(this));
		m_gameStateManager->PushState("Splash");
		});
}
void MenuState::Unload()
{
	std::cout << "UNLOADING MENU" << std::endl;
}

void MenuState::Update(float dt)
{
	m_play->Update();
}
void MenuState::Draw()
{
	DrawText("Memes", 10, 10, 20, RED);
	m_play->Draw();
}