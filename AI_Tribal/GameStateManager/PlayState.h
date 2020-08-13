#pragma once

#include "IGameState.h"
#include "raylib.h"

class Graph2D;
class Graph2DEditor;
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
	Texture2D m_map;
	Camera2D m_camera;
	Graph2D* m_graph;
	Graph2DEditor* m_graphEditor;


// player
// map
// path_nodes
// resoures nodes
};