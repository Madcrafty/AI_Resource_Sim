#include "FleeBehaviour.h"

Vector2 FleeBehaviour::Update(Agent* agent, float deltaTime)
{
	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		m_Target = GetMousePosition();
	}
	DrawCircle(m_Target.x, m_Target.y, m_pointRadius, { 125, 0, 125, 125 });
	Vector2 v = Vector2Subtract(m_Target, agent->GetPosition());
	Vector2 desiredVelocity;
	Vector2 steeringForce = { 0,0 };
	if (v.x > -m_pointRadius &&
		v.x < m_pointRadius &&
		v.y > -m_pointRadius &&
		v.y < m_pointRadius)
	{
		// if seeker on top of target, v is 0 so following calculations are not needed
		desiredVelocity = Vector2Scale(Vector2Normalize(v), -agent->GetMaxSpeed());
		//Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), m_maxSpeed);
		steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());
	}

	return steeringForce;
}