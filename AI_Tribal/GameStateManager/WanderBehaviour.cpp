#include "WanderBehaviour.h"
#include "TestState.h"
#include "Agent.h"
#include "ResourceNode.h"
#include "HealingZone.h"

#include "SeekBehaviour.h"
#include "pathfinding.h"
#include "FleeBehaviour.h"

#include <time.h>
#include <stdlib.h>
#include "Agent.h"
#include "Graph2D.h"

WanderBehaviour::WanderBehaviour()
{
	srand(time(nullptr));
}

Vector2 WanderBehaviour::SetAngle(Vector2 vector, float value)
{
	float length = Vector2Length(vector);
	return { cosf(value) * length, sinf(value) * length };
}

Vector2 WanderBehaviour::Update(Agent* agent, float deltatime)
{
	BehaviourCheck(agent);
	Vector2 velocity = agent->GetVelocity();
	if (Vector2Length(velocity) == 0)
	{
		velocity = { 0, -1 };
	}
	Vector2 circleCenter = Vector2Scale(Vector2Normalize(velocity), m_circleDistance);

	Vector2 displacement = { 0, -1 };
	displacement = Vector2Scale(displacement, m_circleRadius);

	displacement = SetAngle(displacement, m_wanderAngle);
	m_wanderAngle += (rand() % (int)m_angleChange) - m_angleChange * .5;

	Vector2 wanderForce = Vector2Add(circleCenter, displacement);

	//Debugging
	debug_circleCenter = Vector2Add(agent->GetPosition(), circleCenter);
	debug_displacement = displacement;
	//Debugging

	return wanderForce;
}

void WanderBehaviour::BehaviourCheck(Agent* agent)
{
	if (agent->GetHealth() <= 0)
	{
		agent->RemoveBehaviour("WanderBehaviour");
		agent->SetDead(true);
		return;
	}
	if (agent->GetHealth() == 1)
	{
		if (agent->FindBehaviour("SeekBehaviour") == true)
		{
			agent->RemoveBehaviour("SeekBehaviour");
		}
		agent->RemoveBehaviour("WanderBehaviour");
		agent->AddBehaviour(new pathfinding());
		pathfinding* behaviour = (pathfinding*)agent->GetBehaviour("FollowPathBehaviour");
		std::vector<Vector2> path = agent->GetApp()->GetGraph()->GetPath(agent, agent->GetApp()->GetHome()->GetPosition());
		behaviour->SetPath(path);
		return;
	}
	for (auto iter : agent->GetApp()->GetBerries())
	{
		if (Vector2Distance(agent->GetPosition(), iter->GetPosition()) < agent->GetRange())
		{
			//if (agent->FindBehaviour("SeekBehaviour") == false)
			//{
			//	agent->RemoveBehaviour("WanderBehaviour");
			//	agent->AddBehaviour(new SeekBehaviour(&iter->GetPosition()));
			//}
			agent->RemoveBehaviour("WanderBehaviour");
			agent->AddBehaviour(new SeekBehaviour(iter));
			return;
		}
	}
	if (Vector2Distance(agent->GetPosition(), agent->GetFleeTarget()->GetPosition()) < agent->GetRange())
	{
		//if (agent->FindBehaviour("SeekBehaviour") == false)
		//{
		//	agent->RemoveBehaviour("WanderBehaviour");
		//	agent->AddBehaviour(new SeekBehaviour(&iter->GetPosition()));
		//}
		agent->RemoveBehaviour("WanderBehaviour");
		agent->AddBehaviour(new FleeBehaviour(agent->GetFleeTarget()));
		return;
	}
}