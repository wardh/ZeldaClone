#include "stdafx.h"
#include "Component.h"


Component::Component(GameObject& aGameObject)
{
	myParent = &aGameObject;
}


Component::~Component()
{
}

void Component::SetParent(GameObject* aParent)
{
	myParent = aParent;
}

bool Component::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	anEvent;
	return true;
}

void Component::SetData()
{

}