#pragma once

#include "IGameState.h"
#include "Agent.h"
#include "raylib.h"
#include <vector>

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
	
	//Camera2D GetCamera2D();

protected:
private:

	int m_initalPlayerAgents = 10;
	int m_initalEnemyAgents = 10;
	bool m_debugMode = false;

	Vector2 m_worldBorder;

	std::vector<Agent*> m_selection;
	std::vector<Agent*> m_player;
	std::vector<Agent*> m_enemy;

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