#pragma once
#include "Behaviour.h"
class FleeBehaviour : public Behaviour
{
public:
	FleeBehaviour() {};
	virtual ~FleeBehaviour() {};

	virtual Vector2 Update(Agent* agent, float deltaTime);

private:
	float m_maxSpeed = 50.0f;
	int m_pointRadius = 100.0f;
	Vector2 m_Target = { 100, 100 };
};