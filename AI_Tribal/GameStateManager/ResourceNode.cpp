#include "ResourceNode.h"
#include "Application.h"
#include "GameStateManager.h"
#include "Agent.h"
#include <vector>

#include "WanderBehaviour.h"
#include "TestState.h"

ResourceNode::ResourceNode(TestState *app)  : GameObject(app)
{
	m_rand = rand() % 1;
	if (m_rand == 0)
	{
		m_image = LoadTexture("./Sprites/big_berryP_c.png");
	}
	else if (m_rand == 1)
	{
		m_image = LoadTexture("./Sprites/big_berryP2_c.png");
	}
	else
	{
		m_image = LoadTexture("./Sprites/big_berryG_c.png");
	}
}
ResourceNode::~ResourceNode()
{

}

void ResourceNode::Update(float deltaTime) {
	// TODO: ResourceNode specific update logic goes here

	// also call our base class update
	GameObject::Update(deltaTime);
}

void ResourceNode::Draw()
{
	// call our base class draw
	DrawTextureV(m_image, Vector2Subtract(m_position, { 16, 16 }), WHITE);
	GameObject::Draw();
}
int ResourceNode::GetRand()
{
	return m_rand;
}