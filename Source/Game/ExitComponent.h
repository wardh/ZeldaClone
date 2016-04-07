#pragma once
#include "Component.h"

class ExitComponent : public Component
{
public:
	ExitComponent(GameObject& aGameObject, const Vector2<float>& aPosition, const std::string& aMapName);
	~ExitComponent();

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void Destroy();
	virtual void SetData();

private:

	Vector2<float> myTargetPosition;
	std::string myTargetMapName;
};

