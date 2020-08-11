#pragma once
#include "Behaviour.h"
class SeekBehaviour :
	public Behaviour
{
public:
	SeekBehaviour() {};
	virtual ~SeekBehaviour() {};

	virtual Vector2 Update(Agent* agent, float deltaTime);
	void SetDestination(Vector2 destination) { m_destination = destination; }

private:
	Vector2 m_destination;
};

