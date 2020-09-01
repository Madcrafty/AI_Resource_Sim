#include "HealingZone.h"
#include "Application.h"
#include "GameStateManager.h"
#include "Agent.h"
#include <vector>

#include "WanderBehaviour.h"
#include "TestState.h"

HealingZone::HealingZone(TestState* app) : GameObject(app)
{

}
HealingZone::~HealingZone()
{

}

void HealingZone::Update(float deltaTime)
{
	float dist_agent1 = Vector2Distance(m_position, m_app->GetAgent(0)->GetPosition());
	float dist_agent2 = Vector2Distance(m_position, m_app->GetAgent(1)->GetPosition());
	if (dist_agent1 < m_range)
	{
		timer1 += deltaTime;
		if (timer1 >= 1/m_hps)
		{
			m_app->GetAgent(0)->AddHealth(1);
			timer1 = 0;
		}
	}
	if (dist_agent2 < m_range)
	{
		timer2 += deltaTime;
		if (timer2 >= 1 / m_hps)
		{
			m_app->GetAgent(01)->AddHealth(1);
			timer2 = 0;
		}
	}
	GameObject::Update(deltaTime);
}
void HealingZone::Draw()
{
	GameObject::Draw();
}