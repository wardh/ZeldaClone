#pragma once
#include "Component.h"
#include "tga2d\sprite\sprite.h"
struct StatsStruct
{
	int myLevel;
	int myMaxHealth;
	int myDamage;
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

	void AddExperience(const int& anAmountOfXP);

	int myLevel;
	int myMaxHealth;
	int myHealth;
	int myDamage;
	float myMovementSpeed;
	bool myIsAlive;
	bool myIsFriendly;
	float myInvulnerableTimer;
	bool myIsInvulnerable;

	int myExperience;
	int myMaxExperience;

	DX2D::CSprite* myHealthSprite;
};

