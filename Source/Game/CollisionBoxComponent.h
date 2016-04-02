#pragma once
#include "CollisionComponent.h"
#include "../Common Utilities/LineVolume.h"

class CollisionBoxComponent : public CollisionComponent
{
public:
	CollisionBoxComponent(GameObject& aGameObject, const Vector2<float>& someDimensions);
	CollisionBoxComponent(GameObject& aGameObject, const Vector2<float>& someDimensions, const Vector2<float>& aCenterPosition);

	~CollisionBoxComponent();
	virtual bool CheckCollision(const Vector2<float>& aPosition) const;
	virtual bool CheckCollision(const CollisionBoxComponent& aCollisionBox) const;
	virtual bool CheckCollision(const CircleStruct& aCircle) const;

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;

	virtual void SetData() override;
	virtual void Destroy();


protected:
	LineVolume<float> myLineVolume;
	Vector2<float> myDimensions;

};

