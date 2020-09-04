#include "pathfinding.h"
#include "WanderBehaviour.h"
#include "TestState.h"
#include "HealingZone.h"

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
	BehaviourCheck(agent);
	// if we dont have a path, than we dont need to do anything
	if (m_path.empty())
	{
		m_curTarget = agent->GetPosition();
		return { 0, 0 };
	}

	Vector2 desiredVelocity = { 0,0 };
	Vector2 steeringForce = { 0,0 };
	
	Vector2 v = Vector2Subtract(m_curTarget, agent->GetPosition());
	if (Vector2Distance(m_curTarget, agent->GetPosition()) < m_pointRadius)
	{
		// check if there is another target in the list
		if (m_order < m_path.size()-1)
		{
			m_order++;
			m_curTarget = m_path.at(m_order);
			v = Vector2Subtract(m_curTarget, agent->GetPosition());
		}
		else
		{
			m_targeting = false;
			m_curTarget = agent->GetPosition();
		}
	}
	if (m_targeting == true)
	{
		desiredVelocity = Vector2Scale(Vector2Normalize(v), agent->GetMaxSpeed());
		//Vector2 desiredVelocity = Vector2Scale(Vector2Normalize(v), m_maxSpeed);
		steeringForce = Vector2Subtract(desiredVelocity, agent->GetVelocity());
	}

	return steeringForce;
}
void pathfinding::Draw(Agent* agent)
{
	// if we dont have a path, than we will not draw it.
	if (m_path.empty() || m_targeting == false)
		return;

	// TODO: draw lines from each point in the path to the next point in the path
	Vector2 p1 = agent->GetPosition();
	Vector2 p2 = m_path.at(m_order);
	for (size_t i = m_order; i < m_path.size(); i++)
	{
		DrawLineV(p1, p2, PURPLE);
		
		p1 = p2;
		if (i+1 < m_path.size())
		{
			p2 = m_path.at(i+1);
		}		
	}
}

void pathfinding::SetPath(const std::vector<Vector2>& path)
{
	if (path.empty() == false)
	{
		m_path = path;
		m_order = 0;
		m_curTarget = m_path.at(m_order);
		m_targeting = true;
	}
}

const std::vector<Vector2>& pathfinding::GetPath() const
{
	return m_path;
}

void pathfinding::BehaviourCheck(Agent* agent)
{
	if (agent->GetHealth() >= 4)
	{
		agent->RemoveBehaviour("FollowPathBehaviour");
		agent->AddBehaviour(new WanderBehaviour());
	}
	if (Vector2Distance(agent->GetPosition(), agent->GetApp()->GetHome()->GetPosition()) > agent->GetApp()->GetHome()->GetRange()
		&& m_targeting == false)
	{
		std::vector<Vector2> path = agent->GetApp()->GetGraph()->GetPath(agent, agent->GetApp()->GetHome()->GetPosition());
		SetPath(path);
	}
}
