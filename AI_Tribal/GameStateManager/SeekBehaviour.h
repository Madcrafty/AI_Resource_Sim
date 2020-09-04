#pragma once
#include "Behaviour.h"

class GameObject;

class SeekBehaviour : public Behaviour
{
public:
	SeekBehaviour(GameObject* target);
	//SeekBehaviour(Camera2D* psCamera) { m_camera = psCamera; };
	virtual ~SeekBehaviour() {};

	virtual Vector2 Update(Agent* agent, float deltaTime);

private:
	float m_maxSpeed = 50.0f;
	int m_pointRadius = 8.1f;
	GameObject* m_Target;
	//Camera2D* m_camera;
};