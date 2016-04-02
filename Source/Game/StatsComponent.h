#pragma once
#include "Component.h"
#include "tga2d\sprite\sprite.h"
struct StatsStruct
{
	int myMaxHealth;
	float myMovementSpeed;
	bool myIsFriendly;
};

class StatsComponent : public Component
{
public:
	StatsComponent(GameObject& aGameObject, const StatsStruct& someStats);
	~StatsComponent();
	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void SetData();
	virtual void Destroy();

private:
	int myMaxHealth;
	int myHealth;
	float myMovementSpeed;
	bool myIsAlive;
	bool myIsFriendly;
	float myInvulnerableTimer;
	bool myIsInvulnerable;

	DX2D::CSprite* myHealthSprite;
	DX2D::CSprite* myEmptyHealthSprite;
};

