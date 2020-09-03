#include "GameObject.h"
#include "TestState.h"

bool GameObject::ms_debugDraw = false;

GameObject::GameObject(TestState* app) : m_app(app)
{
	
}
GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{
	// m_velocity += m_acceleration * deltaTime;
	// m_position += m_velocity * deltaTime;
	// m_acceleration = {0,0};
	// AddForce -m_velocity * m_friction

	ApplyForce(Vector2Scale(Vector2Negate(m_velocity), m_friction));
	m_velocity = Vector2Add(m_velocity, Vector2Scale(m_acceleration, deltaTime));
	m_position = Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime));
	m_acceleration = { 0,0 };
}
void GameObject::Draw()
{
	if (GameObject::IsDebugRendering())
	{
		Vector2 heading = Vector2Add(m_position, m_velocity);
		DrawCircleV(m_position, 8, GRAY);
		DrawLineV(m_position, heading, BLACK);
	}
}
void GameObject::ApplyForce(const Vector2& force)
{
	// m_acceleration += force;
	m_acceleration = Vector2Add(m_acceleration, force);
}

// Getters
Vector2& GameObject::GetPosition() 
{
	return m_position;
}
const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}
const float& GameObject::GetFriction() const
{
	return m_friction;
}

// Setters
void GameObject::SetPostion(const Vector2& pos)
{
	m_position = pos;
}
void GameObject::SetVelocity(const Vector2& vel)
{
	m_velocity = vel;
}
void GameObject::SetFriction(const float& friction)
{
	m_friction = friction;
}

void GameObject::SetDebugRendering(bool enabled)
{
	ms_debugDraw = enabled;
}
bool GameObject::IsDebugRendering()
{
	return ms_debugDraw;
}