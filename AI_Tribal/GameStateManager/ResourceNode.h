#pragma once
#include "GameObject.h"
class ResourceNode : public GameObject
{
public:
	ResourceNode(TestState *app);
	virtual ~ResourceNode();

	virtual void Update(float deltaTime);
	virtual void Draw();

	int GetRand();

protected:
private:
	Texture2D m_image;
	int m_rand = 0;
};