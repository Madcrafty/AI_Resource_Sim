#include "SeekBehaviour.h"

Vector2 SeekBehaviour::Update(Agent* agent, float deltaTime)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		m_Target = GetMousePosition();
	}
	DrawCircle(m_Target.x, m_Target.y, m_pointRadius, BLUE);

	Vector2 v = Vector2Subtract(m_Target, agent->GetPosition());
	if (v.x > -m_pointRadius &&
		v.x < m_pointRadius &&
		v.y > -m_pointRadius &&
		v.y < m_pointRadius)
	{
		// if seeker on top of target, v is 0 so following calculations are not needed
		agent->RemoveBehaviour("SeekBehaviour");
	}

	Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), agent->GetMaxSpeed());
	//Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), m_maxSpeed);
	Vector2 steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());

	return steeringForce;
	//Self written stuff
	//
	//Vector2 DesiredVelocity = Vector2Scale(Vector2Normalize(Vector2Subtract(m_Target, agent->GetPosition())),m_maxSpeed);
	//Vector2 SteeringForce = Vector2Subtract(DesiredVelocity, agent->GetVelocity());
	//if (agent->GetPosition().x > m_Target.x - m_pointRadius &&
	//	agent->GetPosition().x < m_Target.x + m_pointRadius &&
	//	agent->GetPosition().y > m_Target.y - m_pointRadius &&
	//	agent->GetPosition().y < m_Target.y + m_pointRadius)
	//{
	//	agent->RemoveBehaviour("SeekBehaviour");
	//}
	//return SteeringForce;
}