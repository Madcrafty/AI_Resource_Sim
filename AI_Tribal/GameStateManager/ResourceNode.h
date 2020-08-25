#pragma once
#include "GameObject.h"
class ResourceNode : public GameObject
{
public:
	ResourceNode();
	~ResourceNode();

	void SetResource1(int amount);
	void SetResource2(int amount);
	void GiveResource1(int amount);
	void GiveResource2(int amount);
protected:
	int m_resource1;
	int m_resource2;
private:
	Texture2D m_image;
};