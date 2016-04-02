#pragma once
#include "Component.h"
#include "../Common Utilities/Observer.h"
class PlayerControllerComponent : public Component, CU::Observer
{
public:
	PlayerControllerComponent(GameObject& aGameObject);
	~PlayerControllerComponent();

	virtual void Update() override;

	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	bool HandleKeyboardEvent(const CU::PoolPointer<CU::Event>& anEvent);
	virtual void SetData();
	virtual void Destroy();


private:
	//bool HandleKeyboardEvent(const CU::Event& anEvent);


};

