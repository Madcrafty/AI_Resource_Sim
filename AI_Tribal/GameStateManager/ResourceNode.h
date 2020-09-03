#pragma once
#include "GameObject.h"
class ResourceNode : public GameObject
{
public:
	ResourceNode(TestState *app);
	virtual ~ResourceNode();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Die();

protected:
private:
	bool isDead = false;
	Texture2D m_image;
	float m_range = 10;
	int m_rand = 0;
};