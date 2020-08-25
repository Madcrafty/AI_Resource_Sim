#pragma once
#include "raymath.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ApplyForce(const Vector2& force);

	// Getters
	const Vector2& GetPostion() const;
	const Vector2& GetVelocity() const;
	const float& GetFriction() const;

	// Setters
	void SetPostion(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& friction);

protected:

	Vector2 m_position = { 0,0 };
	Vector2 m_velocity = { 0,0 };
	Vector2 m_acceleration = { 0,0 };
	float m_friction = 0.0f;

private:
};