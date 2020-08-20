#pragma once

#include "Behaviour.h"
#include <list>
#include <functional>
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
	std::list < std::function<void()> > m_commands;
	float m_maxSpeed = 50.0f;
	int m_pointRadius = 2.0f;
	bool m_targeting = false;
	std::vector<Vector2> m_path;
	size_t m_order = 0;
	Vector2 m_curTarget;
};
