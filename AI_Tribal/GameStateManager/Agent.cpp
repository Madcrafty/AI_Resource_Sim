#include "Agent.h"
#include "Behaviour.h"
#include "KeyboardBehaviour.h"`
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"

Agent::Agent()
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
	// Force is equal to zero
	// For each Behaviour in Behaviour list
	//	 Call the Behaviour’s Update functionand add the returned value to Force
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
	}
	return false;
}

// Draw the agent
void Agent::Draw()
{
	DrawRectangle(m_position.x, m_position.y, 10, 10, m_colour);
}

// Update colour
void Agent::ColourUpdate()
{
	Color newColour = { 0,0,0,255 };
	if (m_behaviourList.size() == 0)
	{
		m_colour = GRAY;
	}
	for (size_t i = 0; i < m_behaviourList.size(); i++)
	{
		if (dynamic_cast<KeyboardBehaviour*>(m_behaviourList[i]))
		{
			newColour.g = 200;
		}
		if (dynamic_cast<SeekBehaviour*>(m_behaviourList[i]))
		{
			newColour.b = 200;
		}
		if (dynamic_cast<FleeBehaviour*>(m_behaviourList[i]))
		{
			newColour.r = 200;
		}
	}
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
		}
		if (dynamic_cast<SeekBehaviour*>(m_behaviourList[i]) && param == "SeekBehaviour")
		{
			m_behaviourList.erase(m_behaviourList.begin() + i);
		}
	}
	ColourUpdate();
}