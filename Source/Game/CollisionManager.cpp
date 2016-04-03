#include "stdafx.h"
#include "CollisionManager.h"
#include "CollisionBoxComponent.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "../Common Utilities/EventManager.h"
#include "tga2d\sprite\sprite.h"
#define COLLISION_CULLING_RANGE 512.f

CollisionManager::CollisionManager()
{

	//myDamageCircle = ResourceManager::GetInstance()->GetSprite("../Data/Gfx/debug/debugCircle32x32.png", { 32, 32 }, { 16, 16 });

}


CollisionManager::~CollisionManager()
{
}


void CollisionManager::Init()
{
	myCircles.Init(16);
	ObserveEvent(CU::eEvent::SPAWN_DAMAGE_CIRCLE, HANDLE_EVENT_FUNCTION(HandleSpawnDamageCircleEvent));
	myCircleSprite = ResourceManager::GetInstance()->GetSprite("Data/Gfx/debug/debugCircle32x32.png");
}

void CollisionManager::Update()
{
	myCircles.RemoveAll();
}

void CollisionManager::Render()
{
	for (unsigned short i = 0; i < myCircles.Size(); i++)
	{
		RenderCommand rc;
		rc.mySprite = myCircleSprite;
		rc.mySpace.SetPosition(myCircles[i].myPosition);
		Renderer::GetInstance()->AddRenderCommand(rc, eRenderLayer::TOP);
	}
}

void CollisionManager::ActorsVsLevelObjects(CU::GrowingArray<GameObject>& someActors, CU::GrowingArray<GameObject>& someTiles)
{
	for (unsigned short i = 0; i < someActors.Size(); i++)
	{
		for (unsigned short l = 0; l < someTiles.Size(); l++)
		{
			if (someTiles[l].ValueExists<CollisionBoxComponent*>("CollisionBoxComponent") == true)
			{
				if (Length2(someActors[i].GetPosition() - someTiles[l].GetPosition()) < COLLISION_CULLING_RANGE*COLLISION_CULLING_RANGE)
				{
					CollisionBoxComponent* second = someTiles[l].GetValue<CollisionBoxComponent*>("CollisionBoxComponent");

					CollisionBoxEvent boxEvent;
					boxEvent.myCollisionBoxComponent = second;
					someActors[i].HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(boxEvent));

					//someActors[i].HandleInternalEvent(CU::Event(CU::eEvent::COLLISION_BOX_COMPONENT, second));
				}
			}
		}
	}
}



void CollisionManager::ActorsVsDamageCircles(CU::GrowingArray<GameObject>& someActors)
{
	for (unsigned short i = 0; i < someActors.Size(); i++)
	{
		for (unsigned short l = 0; l < myCircles.Size(); l++)
		{
			if (Length2(someActors[i].GetPosition() - myCircles[l].myPosition) < COLLISION_CULLING_RANGE*COLLISION_CULLING_RANGE)
			{
				if (*someActors[i].GetValue<const bool*>("IsFriendly") != myCircles[l].myIsFriendly)
				{
					CollisionBoxComponent* actor = someActors[i].GetValue<CollisionBoxComponent*>("CollisionBoxComponent");

					if (actor->CheckCollision(myCircles[l]) == true)
					{
						DamageEvent dmgEvent;
						dmgEvent.myDamageAmount = myCircles[l].myDamage;
						dmgEvent.myPosition = myCircles[l].myPosition;
						someActors[i].HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(dmgEvent));
					}
				}
			}

		}
	}
}

void CollisionManager::ActorsVsBullets(CU::GrowingArray<GameObject>& someActors, CU::GrowingArray<GameObject*>& someBullets)
{
	for (unsigned short i = 0; i < someActors.Size(); i++)
	{
		for (unsigned short l = 0; l < someBullets.Size(); l++)
		{
			if (Length2(someActors[i].GetPosition() - someBullets[l]->GetPosition()) < COLLISION_CULLING_RANGE*COLLISION_CULLING_RANGE)
			{
				if (*someActors[i].GetValue<const bool*>("IsFriendly") != *someBullets[l]->GetValue<const bool*>("BulletFriendly"))
				{
					CollisionBoxComponent* actor = someActors[i].GetValue<CollisionBoxComponent*>("CollisionBoxComponent");
					CollisionBoxComponent* second = someBullets[l]->GetValue<CollisionBoxComponent*>("CollisionBoxComponent");
					if (actor->CheckCollision(*second) == true)
					{


						//someActors[i].HandleInternalEvent(CU::Event(CU::eEvent::TAKE_DAMAGE, *someBullets[l]->GetValue<const int*>("Damage"), someBullets[l]->GetPosition()));
						//someBullets[l]->HandleInternalEvent(CU::Event(CU::eEvent::BULLET_COLLIDED));
					}
				}
			}
		}
	}
}



void CollisionManager::PlayerVsActors(GameObject& aPlayer, CU::GrowingArray<GameObject>& someActors)
{
	for (unsigned short i = 0; i < someActors.Size(); i++)
	{
		if (someActors[i].GetTag() != "player")
		{
			CollisionBoxComponent* actor = aPlayer.GetValue<CollisionBoxComponent*>("CollisionBoxComponent");
			CollisionBoxComponent* second = someActors[i].GetValue<CollisionBoxComponent*>("CollisionBoxComponent");

			if (actor->CheckCollision(*second) == true)
			{
				DamageEvent dmgEvent;
				if (someActors[i].ValueExists<const int*>("Damage"))
				{
					dmgEvent.myDamageAmount = *someActors[i].GetValue<const int*>("Damage");
				}
				else
				{
					dmgEvent.myDamageAmount = 1;
				}
				dmgEvent.myPosition = someActors[i].GetPosition();
				aPlayer.HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(dmgEvent));
			}
		}
	}
}



bool CollisionManager::HandleSpawnDamageCircleEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, SpawnDamageCircle, circleEvent);
	CircleStruct circleToAdd;
	circleToAdd.myPosition = circleEvent->myPosition;
	circleToAdd.myRadius = circleEvent->myRadius;
	circleToAdd.myDamage = circleEvent->myDamageAmount;
	myCircles.Add(circleToAdd);
	return true;
}
