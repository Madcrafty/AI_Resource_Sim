#include "PlayState.h"
#include "Application.h"
#include "GameStateManager.h"

PlayState::PlayState(Application* app) : m_app(app)
{

}
PlayState::~PlayState()
{

}

void PlayState::Load()
{

}
void PlayState::Unload()
{

}

void PlayState::Update(float dt)
{
	if (IsKeyPressed(KEY_P))
	{
		auto gms = m_app->GetGameStateManager();
		if (gms->GetActiveState() == this )
		{
			m_app->GetGameStateManager()->PushState("Pause");
		}
		
	}
}
void PlayState::Draw()
{
	DrawText("Playing the game", 10, 10, 30, RED);
}