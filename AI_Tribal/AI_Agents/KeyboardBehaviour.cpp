#include "KeyboardBehaviour.h"

Vector2 KeyboardBehaviour::Update(Agent* agent, float deltaTime)
{
	Vector2 force = { 0, 0 };

	if (IsKeyDown(KEY_UP))
		force.y = -agent->GetMaxSpeed();
	if (IsKeyDown(KEY_DOWN))
		force.y = agent->GetMaxSpeed();
	if (IsKeyDown(KEY_LEFT))
		force.x = -agent->GetMaxSpeed();
	if (IsKeyDown(KEY_RIGHT))
		force.x = agent->GetMaxSpeed();

	//if (IsKeyDown(KEY_UP))
	//	force.y = -m_speedIncrement;
	//if (IsKeyDown(KEY_DOWN))
	//	force.y = m_speedIncrement;
	//if (IsKeyDown(KEY_LEFT))
	//	force.x = -m_speedIncrement;
	//if (IsKeyDown(KEY_RIGHT))
	//	force.x = m_speedIncrement;

	return force;
}

