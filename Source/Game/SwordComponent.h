#pragma once
#include "Component.h"

class SpriteHGE;

struct SwordStruct
{
	std::string mySpritePath;
	float mySwingTime;
	float myReach;
};

class SwordComponent : public Component
{
public:
	SwordComponent(GameObject& aGameObject);
	SwordComponent(GameObject& aGameObject, const SwordStruct& aSwordStruct);
	~SwordComponent();

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void SetData();
	virtual void Destroy();

private:
	DX2D::CSprite* mySwordSprite;
	bool myIsSwinging;
	float mySwingTime;
	float myCurrentSwingTime;
	float mySwingRotation;
	float myReach;
};

