#pragma once
#include "Behaviour.h"

class SeekBehaviour : public Behaviour
{
public:
	SeekBehaviour(Camera2D* psCamera) { m_camera = psCamera; };
	virtual ~SeekBehaviour() {};

	virtual Vector2 Update(Agent* agent, float deltaTime);

private:
	float m_maxSpeed = 50.0f;
	int m_pointRadius = 2.0f;
	Vector2 m_Target = { 100, 100 };
	Camera2D* m_camera;
};