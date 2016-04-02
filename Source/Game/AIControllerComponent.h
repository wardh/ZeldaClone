#pragma once
#include "Component.h"


class Behaviour;
class AIControllerComponent : public Component
{
public:
	AIControllerComponent(GameObject& aGameObject, Behaviour* aBehaviour);
	~AIControllerComponent();

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	bool HandleEvent(const CU::Event& anEvent);
	virtual void SetData();
	virtual void Destroy();

private:
	Behaviour* myBehaviour;
	eDirections myDirection;

};

