#pragma once
#include "Behaviour.h"
#include <vector>

class GameObject;

class FleeBehaviour : public Behaviour
{
public:
	FleeBehaviour(GameObject* target);
	virtual ~FleeBehaviour() {};

	virtual Vector2 Update(Agent* agent, float deltaTime);

private:
	float m_maxSpeed = 50.0f;
	int m_pointRadius = 100.0f;
	GameObject* m_Target;
	std::vector<Vector2> m_Targets; // std::vector<GameObject*> m_targets;
};