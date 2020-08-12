#pragma once

#include "IGameState.h"
#include "raylib.h"

class Application;

class PlayState : public IGameState
{
public:

	PlayState(Application* app);
	virtual ~PlayState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Application* m_app;

// player
// map
// path_nodes
// resoures nodes
};