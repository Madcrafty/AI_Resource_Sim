
#include "TestState.h"
#include "Application.h"
#include "raylib.h"
#include "GameStateManager.h"
#include "GameObject.h"

#include <iostream>

TestState::TestState(Application* app) : m_app(app)
{

}
TestState::~TestState()
{

}

void TestState::Load()
{
	std::cout << "LOADING TEST" << std::endl;
	m_player = new GameObject();
	m_player->SetPostion({ m_app->GetWindowWidth() / 2, m_app->GetWindowHeight() / 2 });
	m_player->SetFriction(1);
}
void TestState::Unload()
{
	std::cout << "UNLOADING TEST" << std::endl;
	delete m_player;
	m_player = nullptr;
}

void TestState::Update(float dt)
{
	if (IsKeyDown(KEY_W)) m_player->ApplyForce({ 0, -100 });
	if (IsKeyDown(KEY_A)) m_player->ApplyForce({ -100, 0 });
	if (IsKeyDown(KEY_S)) m_player->ApplyForce({ 0, 100 });
	if (IsKeyDown(KEY_D)) m_player->ApplyForce({ 100, 0 });
	//m_player->ApplyForce({ 10, 0 });
	m_player->Update(dt);
}
void TestState::Draw()
{
	m_player->Draw();
}