#pragma once
#include "Component.h"

class SpriteHGE;

class SwordComponent : public Component
{
public:
	SwordComponent(GameObject& aGameObject);
	~SwordComponent();

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void Destroy();

private:
	DX2D::CSprite* mySwordSprite;
	bool myIsSwinging;
	float mySwingTime;
	float myCurrentSwingTime;
	float mySwingRotation;
};

