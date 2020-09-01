#include "ResourceNode.h"
#include "Application.h"
#include "GameStateManager.h"
#include "Agent.h"
#include <vector>

#include "WanderBehaviour.h"
#include "TestState.h"

ResourceNode::ResourceNode(TestState *app)  : GameObject(app)
{
	m_rand = 0;
}
ResourceNode::~ResourceNode()
{

}

void ResourceNode::Update(float deltaTime) {
	float dist_agent1 = Vector2Distance(m_position, m_app->GetAgent(0)->GetPosition());
	float dist_agent2 = Vector2Distance(m_position, m_app->GetAgent(1)->GetPosition());
	if (dist_agent1 < m_range)
	{ 
		for (size_t i = 0; i < m_app->GetBerries().size(); i++)
		{
			if (this == m_app->GetBerries().at(i))
			{
				m_app->GetBerries().erase(m_app->GetBerries().begin() + i);
			}
		}
		if (m_rand > 0)
			m_app->GetAgent(0)->AddScore(1);
		if (m_rand == 0)
			m_app->GetAgent(0)->AddHealth(-1);
		m_app->GetAgent(0)->RemoveBehaviour("SeekBehaviour");
		m_app->GetAgent(0)->AddBehaviour(new WanderBehaviour);
		delete this;
	}
	if (dist_agent2 < m_range)
	{
		for (size_t i = 0; i < m_app->GetBerries().size(); i++)
		{
			if (this == m_app->GetBerries().at(i))
			{
				m_app->GetBerries().erase(m_app->GetBerries().begin() + i);
			}
		}
		if (m_rand > 0)
			m_app->GetAgent(1)->AddScore(1);
		if (m_rand == 0)
			m_app->GetAgent(1)->AddHealth(-1);
		m_app->GetAgent(1)->RemoveBehaviour("SeekBehaviour");
		m_app->GetAgent(1)->AddBehaviour(new WanderBehaviour);
		delete this;
	}

	// TODO: ResourceNode specific update logic goes here

	// also call our base class update
	GameObject::Update(deltaTime);
}

void ResourceNode::Draw()
{
	// call our base class draw
	GameObject::Draw();
}
void ResourceNode::Die()
{
	isDead = true;
}