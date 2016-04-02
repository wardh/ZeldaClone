#pragma once
#include "../Common Utilities/PoolPointer.h"
namespace CommonUtilities
{
	class Event;
}
namespace CU = CommonUtilities;
class GameObject;

class Component
{
public:
	Component(GameObject& aGameObject);
	~Component();

	virtual void Update() = 0;
	virtual bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent);
	virtual void SetData();
	virtual void Destroy() = 0;
	void SetParent(GameObject* aParent);

protected:
	GameObject* myParent;

private:
};

