#pragma once

#include "Behaviour.h"

class pathfinding : public Behaviour
{
public:

	pathfinding();
	virtual ~pathfinding();

	virtual Vector2 Update(Agent* agent, float deltaTime);
	virtual void Draw(Agent* agent);

	const std::vector<Vector2>& GetPath() const;
	void SetPath(const std::vector<Vector2>& path);

private:

	float m_maxSpeed = 50.0f;
	int m_pointRadius = 100.0f;
	std::vector<Vector2> m_path;

	Vector2 m_curTarget;

};
