#include "stdafx.h"
#include "StatsComponent.h"
#include "GameObject.h"
#include "../Common Utilities/EventManager.h"
#include "ResourceManager.h"
StatsComponent::StatsComponent(GameObject& aGameObject, const StatsStruct& someStats) : Component(aGameObject)
{
	myMaxHealth = someStats.myMaxHealth;
	myHealth = myMaxHealth;
	myMovementSpeed = someStats.myMovementSpeed;
	myIsFriendly = someStats.myIsFriendly;
	myIsAlive = true;
	myParent->SetValue<const int*>("MaxHealth", &myMaxHealth);
	myParent->SetValue<const int*>("Health", &myHealth);
	myParent->SetValue<const float*>("MovementSpeed", &myMovementSpeed);
	myParent->SetValue<const bool*>("IsAlive", &myIsAlive);
	myParent->SetValue<const bool*>("IsFriendly", &myIsFriendly);
	myIsInvulnerable = false;

	if (myIsFriendly == true)
	{
		myEmptyHealthSprite = ResourceManager::GetInstance()->GetSprite("Data/Gfx/GUI/healthBarEmpty.png");
		myHealthSprite = ResourceManager::GetInstance()->GetSprite("Data/Gfx/GUI/healthBarFilled.png");
	}
}


StatsComponent::~StatsComponent()
{
}


void StatsComponent::Update()
{
	if (myIsInvulnerable == true)
	{
		myInvulnerableTimer -= CU::EventManager::GetInstance()->GetDeltaTime();
		if (myInvulnerableTimer < 0)
		{
			myIsInvulnerable = false;

		}
	}

	if (myIsFriendly == true)
	{
		Vector2<int> screenDim = CU::EventManager::GetInstance()->GetScreenDimensions();
		Matrix33<float> space;

		for (unsigned short i = 0; i < myMaxHealth; i++)
		{
			RenderCommand rc;
			if (i <= myHealth)
			{
				rc.mySprite = myHealthSprite;
			}
			else
			{
				rc.mySprite = myEmptyHealthSprite;
			}
			rc.mySpace.SetPosition({ (64.f / screenDim.x + ((76.f / screenDim.x)*i)) , (64.f / screenDim.y) });
			//rc.mySpace.SetPosition({ 0.1f + 0.1f*i, 0.1f });
			Renderer::GetInstance()->AddRenderCommand(rc, eRenderLayer::GUI);
		}
	}
}

bool StatsComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	switch (anEvent->GetMyType())
	{
	case CU::eEvent::TAKE_DAMAGE:
	{
		GET_EVENT_DATA(anEvent, DamageEvent, damageEvent);
		if (myIsInvulnerable == true)
		{
			return true;
		}
		myHealth -= int(damageEvent->myDamageAmount);
		if (myHealth <= 0)
		{
			myIsAlive = false;
			if (myIsFriendly == false)
			{

				myParent->SetShouldBeRemoved(true);
			}
		}


		myIsInvulnerable = true;
		myInvulnerableTimer = 2.f;
		BlinkSpriteEvent blinkEvent;
		blinkEvent.myDuration = 2.f;
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(blinkEvent));
		AddDamageVelocity damageVelocity;
		damageVelocity.myPosition = damageEvent->myPosition;
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(damageVelocity));
	}
	break;
	case CU::eEvent::HEAL:
	{
		GET_EVENT_DATA(anEvent, HealEvent, healEvent);
		myHealth += healEvent->myHealAmount;
		if (myHealth >= myMaxHealth)
		{
			myHealth = myMaxHealth;
		}
	}
	break;
	default:
		break;
	}
	return true;
}


void StatsComponent::SetData()
{
	myParent->SetValue<const int*>("MaxHealth", &myMaxHealth);
	myParent->SetValue<const int*>("Health", &myHealth);
	myParent->SetValue<const float*>("MovementSpeed", &myMovementSpeed);
	myParent->SetValue<const bool*>("IsAlive", &myIsAlive);
	myParent->SetValue<const bool*>("IsFriendly", &myIsFriendly);
	myIsInvulnerable = false;
}

void StatsComponent::Destroy()
{

}