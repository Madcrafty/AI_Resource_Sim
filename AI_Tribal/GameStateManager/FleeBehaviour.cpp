#include "FleeBehaviour.h"
#include "WanderBehaviour.h"
#include "Agent.h"

FleeBehaviour::FleeBehaviour(GameObject* target) : m_Target(target)
{

};
Vector2 FleeBehaviour::Update(Agent* agent, float deltaTime)
{
	//if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	//{
	//	m_Target = GetScreenToWorld2D(GetMousePosition(), *m_camera);
	//}
	// DrawCircle(m_Target.x, m_Target.y, m_pointRadius, { 125, 0, 125, 125 });
	Vector2 v = Vector2Subtract(m_Target->GetPosition(), agent->GetPosition());
	Vector2 desiredVelocity;
	Vector2 steeringForce = { 0,0 };
	if (Vector2Distance(m_Target->GetPosition(), agent->GetPosition()) < m_pointRadius)
	{
		// if seeker on top of target, v is 0 so following calculations are not needed
		desiredVelocity = Vector2Scale(Vector2Normalize(v), -agent->GetMaxSpeed());
		//Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), m_maxSpeed);
		steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());
	}
	else
	{
		agent->RemoveBehaviour("FleeBehaviour");
		agent->AddBehaviour(new WanderBehaviour());
	}

	return steeringForce;
}