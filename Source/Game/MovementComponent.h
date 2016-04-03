#pragma once
#include "Component.h"
#include "../Common Utilities/Vector.h"
#include "tga2d\text\text.h"


enum class eDirections;
class MovementComponent : public Component
{
public:
	MovementComponent(GameObject& aGameObject);
	~MovementComponent();
	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void Destroy();
	virtual void SetData();

private:
	
	void HandleCollider(const CU::PoolPointer<CU::Event>& anEvent);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	float myLockTime;

	Vector2<float> myVelocity;
	Vector2<float> myMovementDirection;
	Vector2<float> myOldPosition;
	Vector2<float> myDamageVelocity;
	eDirections myDirection;
	bool myWalkedThisFrame;
};

