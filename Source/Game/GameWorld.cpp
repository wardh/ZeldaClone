#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include "Renderer.h"
#include "Camera.h"
#include "PollingStation.h"

#include "Level.h"

//GAMEOBJECT CREATION
#include "ModelComponent.h"
#include "MovementComponent.h"
#include "PlayerControllerComponent.h"
#include "StatsComponent.h"
#include "SwordComponent.h"
#include "AnimationComponent.h"
#include "CollisionBoxComponent.h"
#include "AIControllerComponent.h"
#include "WalkTowardsPlayer.h"
//---------------------
//MapCreation
#include "../Common Utilities/tinyxml2.h"
//---------------------

#define NUMBER_OF_GAMEOBJECTS 4096

CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
}


void CGameWorld::Init()
{
	ObserveEvent(CU::eEvent::KEYBOARD_INPUT_EVENT, HANDLE_EVENT_FUNCTION(HandleKeyboardInput));
	ObserveEvent(CU::eEvent::GIVE_PLAYER_EXPERIENCE, HANDLE_EVENT_FUNCTION(HandleXPEvent));
	ObserveEvent(CU::eEvent::CHANGE_LEVEL, HANDLE_EVENT_FUNCTION(HandleChangeLevelEvent));

	GameObject hero("player", "player");
	hero.AddComponent(new PlayerControllerComponent(hero));
	hero.AddComponent(new CollisionBoxComponent(hero, eCollisionGroup::PLAYER, { 40, 54 }, { 0,8 }));
	hero.AddComponent(new MovementComponent(hero));
	hero.AddComponent(new SwordComponent(hero));
	hero.AddComponent(new AnimationComponent(hero));
	StatsStruct stats;
	stats.myMovementSpeed = 250;
	stats.myIsFriendly = true;
	stats.myMaxHealth = 5;
	stats.myDamage = 2;
	stats.myLevel = 1;
	hero.AddComponent(new StatsComponent(hero, stats));
	hero.SetPosition(Vector2<float>(200, 200));
	myPlayer = hero;
	DX2D::CEngine::GetInstance()->GetLightManager().SetAmbience(1.f);

	myCurrentLevel = new Level();
	myCurrentLevel->Init("Awakening", &myPlayer, { 30*64,50*64 });
}



void CGameWorld::Update(float /*aTimeDelta*/)
{
	myCurrentLevel->Update();
}

bool CGameWorld::HandleKeyboardInput(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, CU::KeyboardInputEvent, keyEvent);

	switch (keyEvent->myKeyboardKey)
	{
	case eKeyboardKeys::KEY_SPACE:
	{
		/*if (keyEvent->myKeyState == eKeyState::DOWN)
		{

			GameObject enemy;
			enemy.AddComponent(new AIControllerComponent(enemy, new WalkTowardsPlayer()));
			enemy.AddComponent(new CollisionBoxComponent(enemy, eCollisionGroup::ENEMY, { 40, 32 }, { 0,8 }));
			enemy.AddComponent(new MovementComponent(enemy));
			enemy.AddComponent(new ModelComponent(enemy, "Data/Gfx/Enemies/misterFish.png", eRenderLayer::ACTORS));
			StatsStruct stats2;
			stats2.myMovementSpeed = 100;
			stats2.myIsFriendly = false;
			stats2.myMaxHealth = 3;
			stats2.myDamage = 1;
			stats2.myLevel = 1;
			enemy.AddComponent(new StatsComponent(enemy, stats2));
			enemy.SetPosition(Vector2<float>(rand() % 800, rand() % 800));
			myGameObjects.Add(enemy);
		}*/
	}
	break;
	default:
		break;
	}
	return true;
}

bool CGameWorld::HandleXPEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, ExperienceEvent, recievedXPEvent);
	ExperienceEvent xpEvent;
	xpEvent.myXPAmount = recievedXPEvent->myXPAmount;

	myPlayer.HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(xpEvent));
	return true;
}

bool CGameWorld::HandleChangeLevelEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, ChangeLevelEvent, levelEvent);

	myCurrentLevel->DestroyLevel();
	myCurrentLevel->Init(levelEvent->myMapName, &myPlayer, levelEvent->myPosition);

	return true;
}
