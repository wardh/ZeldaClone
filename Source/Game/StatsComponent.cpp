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
	myLevel = someStats.myLevel;
	myExperience = 0;
	myMaxExperience = 16 * myLevel + myLevel;
	myDamage = someStats.myDamage;
	myParent->SetValue<const int*>("MaxHealth", &myMaxHealth);
	myParent->SetValue<const int*>("Health", &myHealth);
	myParent->SetValue<const float*>("MovementSpeed", &myMovementSpeed);
	myParent->SetValue<const bool*>("IsAlive", &myIsAlive);
	myParent->SetValue<const bool*>("IsFriendly", &myIsFriendly);
	myParent->SetValue<const int*>("Damage", &myDamage);
	myIsInvulnerable = false;

	if (myIsFriendly == true)
	{
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
		RenderCommand rc;
		rc.mySpace.SetPosition({ (64.f / screenDim.x) , (64.f / screenDim.y) });
		rc.mySprite = myHealthSprite;
		Renderer::GetInstance()->AddRenderCommand(rc, eRenderLayer::GUI);

		RenderCommandText rct;
		rct.myText = std::to_string(myHealth);
		rct.myText += "/";
		rct.myText += std::to_string(myMaxHealth);
		rct.myPosition = { (128.f / static_cast<float>(screenDim.x)) , (80.f / static_cast<float>(screenDim.y)) };
		rct.mySize = 0.7;
		Renderer::GetInstance()->AddRenderCommandText(rct);

		rct.myText = std::to_string(myExperience);
		rct.myText += "/";
		rct.myText += std::to_string(myMaxExperience);
		rct.myPosition = { 0.5f , ((static_cast<float>(screenDim.y) - 64.f) / static_cast<float>(screenDim.y)) };
		rct.mySize = 0.7;
		Renderer::GetInstance()->AddRenderCommandText(rct);


		//for (unsigned short i = 0; i < myMaxHealth; i++)
		//{
		//	if (i <= myHealth)
		//	{
		//		rc.mySprite = myHealthSprite;
		//	}
		//	else
		//	{
		//		rc.mySprite = myEmptyHealthSprite;
		//	}
		//	rc.mySpace.SetPosition({ (64.f / screenDim.x + ((76.f / screenDim.x)*i)) , (64.f / screenDim.y) });
		//	//rc.mySpace.SetPosition({ 0.1f + 0.1f*i, 0.1f });
		//	Renderer::GetInstance()->AddRenderCommand(rc, eRenderLayer::GUI);
		//}
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
				ExperienceEvent xpEvent;
				xpEvent.myXPAmount = myLevel;
				CU::EventManager::GetInstance()->AddEvent(xpEvent);
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
		myHealth += static_cast<int>(healEvent->myHealAmount);
		if (myHealth >= myMaxHealth)
		{
			myHealth = myMaxHealth;
		}
	}
	break;
	case CU::eEvent::GIVE_PLAYER_EXPERIENCE:
	{
		GET_EVENT_DATA(anEvent, ExperienceEvent, xpEvent);
		AddExperience(xpEvent->myXPAmount);
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
	myParent->SetValue<const int*>("Damage", &myDamage);

	myIsInvulnerable = false;
}

void StatsComponent::Destroy()
{

}

void StatsComponent::AddExperience(const int & anAmountOfXP)
{
	myExperience += anAmountOfXP;

	if (myExperience >= myMaxExperience)
	{
		myLevel += 1;
		int healthInc = static_cast<int>(static_cast<float>(myMaxHealth) * 0.1f);
		int dmgInc = static_cast<int>(static_cast<float>(myDamage) * 0.1f);

		if (healthInc > 0)
		{
			myMaxHealth += healthInc;
		}
		else
		{
			myMaxHealth += 1;
		}

		if (dmgInc > 0)
		{
			myDamage += dmgInc;
		}
		else
		{
			myDamage += 1;
		}

		myExperience -= myMaxExperience;

		myMaxExperience = 16 * myLevel + myLevel;
	}
}
