#pragma once
#include "Behaviour.h"
#include <vector>

class FleeBehaviour : public Behaviour
{
public:
	FleeBehaviour(Camera2D* psCamera) { m_camera = psCamera; };
	virtual ~FleeBehaviour() {};

	virtual Vector2 Update(Agent* agent, float deltaTime);

private:
	float m_maxSpeed = 50.0f;
	int m_pointRadius = 100.0f;
	Vector2 m_Target = { 100, 100 };
	std::vector<Vector2> m_Targets; // std::vector<GameObject*> m_targets;
	Camera2D* m_camera;
};