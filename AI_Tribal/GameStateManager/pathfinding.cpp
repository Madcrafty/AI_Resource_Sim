#include "pathfinding.h"
#include "Agent.h"
#include "Graph2D.h"

pathfinding::pathfinding()
{
}

pathfinding::~pathfinding()
{

}

Vector2 pathfinding::Update(Agent* agent, float deltaTime)
{
	size_t i = 1;
	Vector2 v = Vector2Subtract(m_curTarget, agent->GetPosition());
	if (Vector2Distance(m_curTarget, agent->GetPosition()) < m_pointRadius)
	{
		// check if there is another target in the list
		if (i < m_path.size())
		{
			m_curTarget = m_path.at(i);
			i++;
		}
	}

	Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), agent->GetMaxSpeed());
	//Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), m_maxSpeed);
	Vector2 steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());
	return steeringForce;
}
void pathfinding::Draw(Agent* agent)
{
	// TODO: draw lines from each point in the path to the next point in the path
	/*Vector2 p1 = agent->GetPosition();
	Vector2 p2 = m_path.front();
	for (size_t i = 0; i < m_path.size(); i++)
	{
		DrawLineV(p1, p2, PURPLE);
		
		p1 = p2;
		if (i+1 < m_path.size())
		{
			p2 = m_path.at(i+1);
		}		
	}*/
}

void pathfinding::SetPath(const std::vector<Vector2>& path)
{
	m_path = path;
}

const std::vector<Vector2>& pathfinding::GetPath() const
{
	return m_path;
}
