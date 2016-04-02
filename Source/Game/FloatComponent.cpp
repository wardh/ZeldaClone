#include "stdafx.h"

#include "FloatComponent.h"
#include "../Common Utilities/EventManager.h"
#include "GameObject.h"


FloatComponent::FloatComponent(GameObject& aGameObject) : Component(aGameObject)
{

}

FloatComponent::~FloatComponent()
{
}


void FloatComponent::Update()
{
	myFloatValue += CU::EventManager::GetInstance()->GetDeltaTime();
	float yOffset = (-sin(myFloatValue) * 0.05f);
	myParent->SetPosition(myParent->GetPosition() + Vector2<float>({0, yOffset}));
}

bool FloatComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	return true;
}



void FloatComponent::SetData()
{

}

void FloatComponent::Destroy()
{

}