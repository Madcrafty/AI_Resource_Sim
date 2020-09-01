#pragma once
#include "GameObject.h"

class HealingZone : public GameObject
{
public:
	HealingZone(TestState* app);
	virtual ~HealingZone();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	int m_hps = 1;
	float m_range = 50;
	float timer1 = 0;
	float timer2 = 0;
};