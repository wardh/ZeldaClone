#pragma once
#include "Component.h"


class FloatComponent : public Component
{
public:
	FloatComponent(GameObject& aGameObject);
	~FloatComponent();
	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void SetData();
	virtual void Destroy();
private:

	float myFloatValue;
};

