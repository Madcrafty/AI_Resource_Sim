#include "Agent.h"

#include "Behaviour.h"
#include "KeyboardBehaviour.h"`
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"
#include "pathfinding.h"

#include "TestState.h"
#include "GameObject.h"
#include "ResourceNode.h"
#include "HealingZone.h"

Agent::Agent(TestState* app) : GameObject(app)
{}

Agent::~Agent()
{}

Vector2 Agent::Truncate(Vector2 v, float max)
{
	float i = max / Vector2Length(v);
	i = i < 1.0 ? i : 1.0;
	return Vector2Scale(v, i);
}

// Update the agent and its behaviours
void Agent::Update(float deltaTime)
{
	if (m_dead == true)
	{
		return;
	}
	// BehaviourList Update Paramiters
	//check if enemy agent is close
	// if so flee from agent's postion
	if (m_behaviourList.size() == 0)
	{
		AddBehaviour(new WanderBehaviour());
	}
	if (!FindBehaviour("SeekBehaviour"))
	{
		for (auto iter : m_app->GetBerries())
		{
			if (Vector2Distance(m_position, iter->GetPosition()) < m_detectRange)
			{
				if (FindBehaviour("SeekBehaviour") == false)
				{
					RemoveBehaviour("WanderBehaviour");
					AddBehaviour(new SeekBehaviour(&iter->GetPosition()));
				}
				//RemoveBehaviour("WanderBehaviour");
				//AddBehaviour(new SeekBehaviour(&iter->GetPosition()));
			}
		}
	}
	if (m_health >= 4)
	{
		if (m_healing == true)
		{
			RemoveBehaviour("SeekBehaviour");
			//AddBehaviour(new WanderBehaviour());
			m_healing = false;
		}
	}
	if (m_healing == false && m_health == 1)
	{
		if (FindBehaviour("SeekBehaviour") == true)
		{
			RemoveBehaviour("SeekBehaviour");
		}
		RemoveBehaviour("WanderBehaviour");
		AddBehaviour(new SeekBehaviour(&m_app->GetHome()->GetPosition()));
		m_healing = true;
	}
	if (m_healing == true && Vector2Distance(m_position, m_app->GetHome()->GetPosition()) > m_app->GetHome()->GetRange()
		&& FindBehaviour("SeekBehaviour") == false)
	{
		AddBehaviour(new SeekBehaviour(&m_app->GetHome()->GetPosition()));
	}
	if (m_health <= 0)
	{
		m_dead = true;
	}
	

	// Force is equal to zero
	// For each Behaviour in Behaviour list
	//	 Call the Behaviourís Update functionand add the returned value to Force
	// Add Force multiplied by delta time to Velocity
	// Add Velocity multiplied by delta time to Position
	Vector2 force = { 0,0 };
	for (int i = 0; i < m_behaviourList.size(); i++)
	{
		force = Vector2Add(force, m_behaviourList[i]->Update(this, deltaTime));
	}
	m_velocity = Truncate((Vector2Add(m_velocity, force)), m_maxSpeed);
	m_position = (Vector2Add(m_position, Vector2Scale(m_velocity, deltaTime)));
}

// Find specific behaviour
bool Agent::FindBehaviour(const char* param)
{
	for (size_t i = 0; i < m_behaviourList.size(); i++)
	{
		if (dynamic_cast<KeyboardBehaviour*>(m_behaviourList[i]) && param == "KeyboardBehaviour")
		{
			return true;
		}
		if (dynamic_cast<SeekBehaviour*>(m_behaviourList[i]) && param == "SeekBehaviour")
		{
			return true;
		}
		if (dynamic_cast<FleeBehaviour*>(m_behaviourList[i]) && param == "FleeBehaviour")
		{
			return true;
		}
		if (dynamic_cast<pathfinding*>(m_behaviourList[i]) && param == "FollowPathBehaviour")
		{
			return true;
		}
		if (dynamic_cast<WanderBehaviour*>(m_behaviourList[i]) && param == "WanderBehaviour")
		{
			return true;
		}
	}
	return false;
}

Behaviour* Agent::GetBehaviour(const char* param)
{
	for (size_t i = 0; i < m_behaviourList.size(); i++)
	{
		if (dynamic_cast<KeyboardBehaviour*>(m_behaviourList[i]) && param == "KeyboardBehaviour")
		{
			return m_behaviourList[i];
		}
		if (dynamic_cast<SeekBehaviour*>(m_behaviourList[i]) && param == "SeekBehaviour")
		{
			return m_behaviourList[i];
		}
		if (dynamic_cast<FleeBehaviour*>(m_behaviourList[i]) && param == "FleeBehaviour")
		{
			return m_behaviourList[i];
		}
		if (dynamic_cast<pathfinding*>(m_behaviourList[i]) && param == "FollowPathBehaviour")
		{
			return m_behaviourList[i];
		}
		if (dynamic_cast<WanderBehaviour*>(m_behaviourList[i]) && param == "WanderBehaviour")
		{
			return m_behaviourList[i];
		}
	}
	return nullptr;
}

// Draw the agent
void Agent::Draw()
{
	DrawRectangle(m_position.x, m_position.y, 10, 10, m_colour);
	for (size_t i = 0; i < m_behaviourList.size(); i++)
	{
		m_behaviourList[i]->Draw(this);
	}
}

void Agent::SetPlayer()
{
	player = true;
	ColourUpdate();
}

// Update colour
void Agent::ColourUpdate()
{
	Color newColour = { 0,0,0,255 };
	if (player == true)
	{
		newColour = RED;
	}
	else
	{
		newColour = GREEN;
	}
	//if (m_behaviourList.size() == 0)
	//{
	//	m_colour = GRAY;
	//}
	//for (size_t i = 0; i < m_behaviourList.size(); i++)
	//{
	//	if (dynamic_cast<KeyboardBehaviour*>(m_behaviourList[i]))
	//	{
	//		newColour.g = 200;
	//	}
	//	if (dynamic_cast<SeekBehaviour*>(m_behaviourList[i]))
	//	{
	//		newColour.b = 200;
	//	}
	//	if (dynamic_cast<FleeBehaviour*>(m_behaviourList[i]))
	//	{
	//		newColour.r = 200;
	//	}
	//}
	m_colour = newColour;
}

// Add a behaviour to the agent
void Agent::AddBehaviour(Behaviour* behaviour)
{
	m_behaviourList.push_back(behaviour);
	ColourUpdate();
}
void Agent::RemoveBehaviour(const char* param)
{
	for (size_t i = 0; i < m_behaviourList.size(); i++)
	{
		if (dynamic_cast<KeyboardBehaviour*>(m_behaviourList[i]) && param == "KeyboardBehaviour")
		{
			m_behaviourList.erase(m_behaviourList.begin() + i);
			return;
		}
		if (dynamic_cast<SeekBehaviour*>(m_behaviourList[i]) && param == "SeekBehaviour")
		{
			m_behaviourList.erase(m_behaviourList.begin() + i);
			return;
		}
		if (dynamic_cast<FleeBehaviour*>(m_behaviourList[i]) && param == "FleeBehaviour")
		{
			m_behaviourList.erase(m_behaviourList.begin() + i);
			return;
		}
		if (dynamic_cast<pathfinding*>(m_behaviourList[i]) && param == "FollowPathBehaviour")
		{
			m_behaviourList.erase(m_behaviourList.begin() + i);
			return;
		}
		if (dynamic_cast<WanderBehaviour*>(m_behaviourList[i]) && param == "WanderBehaviour")
		{
			m_behaviourList.erase(m_behaviourList.begin() + i);
			return;
		}
	}
	ColourUpdate();
}
void Agent::AddScore(int i)
{
	m_score += i;
}
int Agent::GetScore()
{
	return m_score;
}

void Agent::AddHealth(int i)
{
	m_health += i;
}
int Agent::GetHealth()
{
	return m_health;
}