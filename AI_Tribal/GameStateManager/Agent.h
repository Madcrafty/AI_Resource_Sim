#pragma once
#include "raymath.h"
#include "GameObject.h"
#include <vector>

class Behaviour;
class TestState;
class Graph2D;

class Agent : public GameObject
{
public:
	Agent(TestState* app);
	virtual ~Agent();

	// Update the agent and its behaviours
	virtual void Update(float deltaTime);

	// Draw the agent
	virtual void Draw();

	// Add a behaviour to the agent
	void AddBehaviour(Behaviour* behaviour);

	// Remove a behaviour from agent
	void RemoveBehaviour(const char* param);

	// Find specific behaviour
	bool FindBehaviour(const char* param);

	// Get specific behaviour
	Behaviour* GetBehaviour(const char* param);

	void SetGraph(Graph2D* graph);

	// Set as player
	void SetPlayer();

	// Add Score
	void AddScore(int i);

	// Get Score
	int GetScore();

	// Add health
	void AddHealth(int i);

	// Get health
	int GetHealth();
	// Movement functions
	//void SetPosition(Vector2 position) { m_position = position; }
	//Vector2 GetPosition() { return m_position; }

	//void SetVelocity(Vector2 velocity) { m_velocity = velocity; }
	//Vector2 GetVelocity() { return m_velocity; }

	void SetMaxSpeed(float speed) { m_maxSpeed = speed; }
	float GetMaxSpeed() { return m_maxSpeed; }

private:
	Vector2 Truncate(Vector2 v, float max);
	void ColourUpdate();

protected:
	std::vector<Behaviour*> m_behaviourList;
	// std::vector<Atribute*> m_atributeList;

	//Vector2 m_position = { 0, 0 };
	//Vector2 m_velocity = { 0, 0 };
	float m_maxSpeed = 100;
	bool player = false;
	Color m_colour = GRAY;
	float m_detectRange = 100;
	bool m_healing = false;
	bool m_dead = false;
	Graph2D* m_graph;

	int m_score = 0;
	int m_health = 4;
};