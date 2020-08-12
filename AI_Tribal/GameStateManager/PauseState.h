#pragma once

#include "IGameState.h"
#include "raylib.h"

class Application;
class Button;

class PauseState : public IGameState
{
public:

	PauseState(Application* app);
	virtual ~PauseState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;

	Texture2D m_pause;

	Texture2D m_play1;
	Texture2D m_play2;
	Button* m_play;

	Texture2D m_exit1;
	Texture2D m_exit2;
	Button* m_exit;

	float m_boxWidth = 33 * 3;
	float m_boxHeight = 15 * 3;
};
