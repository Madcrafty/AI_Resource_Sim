#pragma once

#include "IGameState.h"
#include "raylib.h"
#include "Button.h"

class Application;
class Button;

class MenuState : public IGameState
{
public:

	MenuState(Application* app);
	virtual ~MenuState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;
	Texture2D m_button1;
	Texture2D m_button2;
	Button* m_play;
	float m_boxWidth = 33 * 3;
	float m_boxHeight = 15 * 3;
};