#pragma once

#include "raymath.h"
class Agent;

class Behaviour
{
public:

	// empty constructors and destructors for base class
	Behaviour() {}
	virtual ~Behaviour() {}

	// pure virtual function for executing the behaviour
	virtual Vector2 Update(Agent* agent, float deltaTime) = 0;

	virtual void Draw(Agent* agent) {}
	virtual void BehaviourCheck(Agent* agent) {};
};