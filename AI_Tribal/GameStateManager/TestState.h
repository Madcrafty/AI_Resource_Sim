#pragma once

#include "IGameState.h"
#include "raylib.h"
#include "Button.h"
#include  <vector>

class Graph2D;
class Application;
class GameObject;
class Agent;
class ResourceNode;
class HealingZone;

class TestState : public IGameState
{
public:

	TestState(Application* app);
	virtual ~TestState();

	virtual void Load();
	virtual void Unload();

	virtual void Update(float dt);
	virtual void Draw();

	std::vector<ResourceNode *>& GetBerries();
	Agent* GetAgent(int num);
	HealingZone* GetHome();

	void SpawnBerry(Vector2 pos);
	Graph2D* GetGraph();
	void RemoveBerry(ResourceNode* target);

protected:
private:
	// Map
	Texture2D m_image;
	// House
	HealingZone* m_home;
	// Graph
	Graph2D* m_graph;
	// Agent1
	Agent* m_agent1;
	// Agent2
	Agent* m_agent2;
	// Berries
	std::vector<ResourceNode *> m_berries;

	Application* m_app;
	//GameObject* m_player = nullptr;
};