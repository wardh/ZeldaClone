#include "stdafx.h"
#include "SwordComponent.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "ComponentEnums.h"

#include "../Common Utilities/EventManager.h"

SwordComponent::SwordComponent(GameObject& aGameObject) : Component(aGameObject)
{
	mySwordSprite = ResourceManager::GetInstance()->GetSprite("Data/Gfx/Swords/stick.png");
	mySwordSprite->SetPivot({ 8.f / 64.f, 2.f / 64.f });
	mySwingTime = 0.2f;
	myIsSwinging = false;
	myCurrentSwingTime = 0;
	mySwingRotation = 0;
}


SwordComponent::~SwordComponent()
{
}


void SwordComponent::Update()
{
	if (myIsSwinging == true)
	{
		float deltaTime = CU::EventManager::GetInstance()->GetDeltaTime();

		eDirections direction = *myParent->GetValue<const eDirections*>("Direction");
		Vector2<float> weaponOffsetFromDirection = { 0,0 };
		Matrix33<float> objectSpace = myParent->GetSpace();
		Matrix33<float> swordSpace = objectSpace;
		swordSpace.SetPosition({ 0, 0 });
		float rotation = 0;
		switch (direction)
		{
		case eDirections::LEFT:
			rotation = (-PI *0.5f);
			weaponOffsetFromDirection.x = -1;
			weaponOffsetFromDirection.y = 3;
			break;
		case eDirections::RIGHT:
			rotation = (PI *0.5f);
			weaponOffsetFromDirection.x = 1;
			weaponOffsetFromDirection.y = 3;
			break;
		case eDirections::UP:
			rotation = (PI);
			weaponOffsetFromDirection.y = -6;
			break;
		case eDirections::DOWN:
			weaponOffsetFromDirection.y = 6;
			break;
		default:
			break;
		}


		myCurrentSwingTime -= deltaTime;
		rotation -= (PI * 0.4f);
		float maxRotation = PI*0.6f;
		float swingAmount = myCurrentSwingTime / mySwingTime;
		rotation += maxRotation * swingAmount;
		swordSpace.Rotate2D(rotation);
		if (myCurrentSwingTime <= 0)
		{
			myIsSwinging = false;
		}

		swordSpace.SetPosition(objectSpace.GetPosition()+weaponOffsetFromDirection);

		RenderCommand rc;
		rc.mySprite = mySwordSprite;
		rc.mySpace = swordSpace;
		Renderer::GetInstance()->AddRenderCommand(rc, eRenderLayer::ACTORS);
		Vector2<float> swordDamageDirection = {-cos(rotation), sin(rotation)};
		swordDamageDirection = GetNormalized(swordDamageDirection);
		swordDamageDirection = swordDamageDirection * Matrix33<float>::CreateRotateAroundZ(-PI*0.5f);
		//CU::Event damageCircle(CU::eEvent::SPAWN_DAMAGE_CIRCLE, (swordSpace.GetPosition() + (swordDamageDirection*40.f)), 16.f);
		SpawnDamageCircle damageCircleEvent;
		damageCircleEvent.SetMyType(CU::eEvent::SPAWN_DAMAGE_CIRCLE);
		damageCircleEvent.myPosition = (swordSpace.GetPosition() + (swordDamageDirection*40.f));
		damageCircleEvent.myRadius = 16.f;
		CU::EventManager::GetInstance()->AddEvent(damageCircleEvent);
	}
}
bool SwordComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	switch (anEvent->GetMyType())
	{
	case CU::eEvent::SWING_WEAPON:
		if (myIsSwinging == false)
		{
			myIsSwinging = true;
			myCurrentSwingTime = mySwingTime;
		}
		break;
	default:
		break;
	}

	anEvent;
	return true;
}

void SwordComponent::Destroy()
{

}