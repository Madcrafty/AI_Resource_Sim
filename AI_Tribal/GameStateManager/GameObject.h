#pragma once
#include "raymath.h"

class TestState;

class GameObject
{
public:

	GameObject(TestState* app);
	virtual ~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void ApplyForce(const Vector2& force);

	// Getters
	Vector2& GetPosition();
	const Vector2& GetVelocity() const;
	const float& GetFriction() const;

	// Setters
	void SetPostion(const Vector2& pos);
	void SetVelocity(const Vector2& vel);
	void SetFriction(const float& friction);

	static void SetDebugRendering(bool enabled);
	static bool IsDebugRendering();
	TestState* GetApp();

protected:

	Vector2 m_position = { 0,0 };
	Vector2 m_velocity = { 0,0 };
	Vector2 m_acceleration = { 0,0 };
	float m_friction = 0.0f;
	
	TestState* m_app;

private:


	static bool ms_debugDraw;

};