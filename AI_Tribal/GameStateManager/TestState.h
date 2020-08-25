#pragma once

#include "IGameState.h"
#include "raylib.h"
#include "Button.h"

class Application;
class GameObject;

class TestState : public IGameState
{
public:

	TestState(Application* app);
	virtual ~TestState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;
	GameObject* m_player = nullptr;
};