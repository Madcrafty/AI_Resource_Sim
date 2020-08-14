#include "WanderBehaviour.h"
#include <time.h>

WanderBehaviour::WanderBehaviour()
{
	srand(time(nullptr));
}

Vector2 WanderBehaviour::SetAngle(Vector2 vector, float value)
{
	float length = Vector2Length(vector);
	return { cosf(value) * length, sinf(value) * length };
}

Vector2 WanderBehaviour::Update(Agent* agent, float deltatime)
{
	Vector2 velocity = agent->GetVelocity();
	if (Vector2Length(velocity) == 0)
	{
		velocity = { 0, -1 };
	}
	Vector2 circleCenter = Vector2Scale(Vector2Normalize(velocity), m_circleDistance);

	Vector2 displacement = { 0, -1 };
	displacement = Vector2Scale(displacement, m_circleRadius);

	displacement = SetAngle(displacement, m_wanderAngle);
	m_wanderAngle += (rand() % (int)m_angleChange) - m_angleChange * .5;

	Vector2 wanderForce = Vector2Add(circleCenter, displacement);

	//Debugging
	debug_circleCenter = Vector2Add(agent->GetPosition(), circleCenter);
	debug_displacement = displacement;
	//Debugging

	return wanderForce;
}