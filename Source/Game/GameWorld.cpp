#include "stdafx.h"
#include "GameWorld.h"

#include <tga2d/Engine.h>
#include <tga2d/light/light_manager.h>
#include <tga2d/sprite/sprite.h>
#include "Renderer.h"
#include "Camera.h"
#include "PollingStation.h"

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

CGameWorld::CGameWorld()
{
}


CGameWorld::~CGameWorld()
{
}


void CGameWorld::Init()
{
	ObserveEvent(CU::eEvent::KEYBOARD_INPUT_EVENT, HANDLE_EVENT_FUNCTION(HandleKeyboardInput));

	myGameObjects.Init(1024);
	myTileTypes.Init(128);
	myCollidingTiles.Init(4096);
	myCosmeticTiles.Init(4096);
	GameObject hero("player", "player");
	hero.AddComponent(new PlayerControllerComponent(hero));
	hero.AddComponent(new CollisionBoxComponent(hero, { 40, 32 }, { 0,8 }));
	hero.AddComponent(new MovementComponent(hero));
	hero.AddComponent(new SwordComponent(hero));
	hero.AddComponent(new AnimationComponent(hero));
	StatsStruct stats;
	stats.myMovementSpeed = 250;
	stats.myIsFriendly = true;
	stats.myMaxHealth = 5;
	hero.AddComponent(new StatsComponent(hero, stats));
	hero.SetPosition(Vector2<float>(100, 100));
	myGameObjects.Add(hero);
	myCollisionManager.Init();

	//ENEMY
	GameObject enemy;
	enemy.AddComponent(new AIControllerComponent(enemy, new WalkTowardsPlayer()));
	enemy.AddComponent(new CollisionBoxComponent(enemy, { 40, 32 }, { 0,8 }));
	enemy.AddComponent(new MovementComponent(enemy));
	enemy.AddComponent(new ModelComponent(enemy, "Data/Gfx/Enemies/misterFish.png", eRenderLayer::ACTORS));
	StatsStruct stats2;
	stats2.myMovementSpeed = 100;
	stats2.myIsFriendly = false;
	stats2.myMaxHealth = 3;
	enemy.AddComponent(new StatsComponent(enemy, stats2));
	enemy.SetPosition(Vector2<float>(500, 500));
	myGameObjects.Add(enemy);

	//----------


	LoadMap();

	DX2D::CEngine::GetInstance()->GetLightManager().SetAmbience(1.f);


}



void CGameWorld::Update(float /*aTimeDelta*/)
{
	//mySprite->Render();
	Camera::GetInstance()->MoveTo(myGameObjects[0].GetPosition());
	for (unsigned short i = 0; i < myGameObjects.Size(); i++)
	{
		myGameObjects[i].Update();
	}
	for (unsigned short i = 0; i < myCollidingTiles.Size(); i++)
	{
		myCollidingTiles[i].Update();
	}
	for (unsigned short i = 0; i < myCosmeticTiles.Size(); i++)
	{
		myCosmeticTiles[i].Update();
	}
	myCollisionManager.ActorsVsLevelObjects(myGameObjects, myCollidingTiles);
	myCollisionManager.ActorsVsDamageCircles(myGameObjects);
	myCollisionManager.PlayerVsActors(myGameObjects[0], myGameObjects);
	//myCollisionManager.Render();
	myCollisionManager.Update();
	RemoveDeadGameObjects();
}

bool CGameWorld::HandleKeyboardInput(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, CU::KeyboardInputEvent, keyEvent);

	switch (keyEvent->myKeyboardKey)
	{
	case eKeyboardKeys::KEY_SPACE:
	{
		if (keyEvent->myKeyState == eKeyState::PRESSED)
		{

			GameObject enemy;
			enemy.AddComponent(new AIControllerComponent(enemy, new WalkTowardsPlayer()));
			enemy.AddComponent(new CollisionBoxComponent(enemy, { 40, 32 }, { 0,8 }));
			enemy.AddComponent(new MovementComponent(enemy));
			enemy.AddComponent(new ModelComponent(enemy, "Data/Gfx/Enemies/misterFish.png", eRenderLayer::ACTORS));
			StatsStruct stats2;
			stats2.myMovementSpeed = 100;
			stats2.myIsFriendly = false;
			stats2.myMaxHealth = 3;
			enemy.AddComponent(new StatsComponent(enemy, stats2));
			enemy.SetPosition(Vector2<float>(rand() % 800, rand() % 800));
			myGameObjects.Add(enemy);
		}
	}
	break;
	default:
		break;
	}
	return true;
}

void CGameWorld::RemoveDeadGameObjects()
{
	for (unsigned short i = 0; i < myGameObjects.Size(); i++)
	{
		if (myGameObjects[i].GetShouldBeRemoved() == true)
		{
			myGameObjects.RemoveAtIndex(i);
			--i;
		}
	}
}

void CGameWorld::LoadMap()
{
	tinyxml2::XMLDocument doc;
	//level01.tmx
	std::string dir = "Data/Maps/Home.tmx";
	tinyxml2::XMLError status = doc.LoadFile(dir.c_str());
	if (status == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
	{
		DL_ASSERT(dir.c_str());
	}
	tinyxml2::XMLElement *rootElement = doc.RootElement();

	tinyxml2::XMLElement *tileset = rootElement->FirstChildElement("tileset");
	tinyxml2::XMLElement *tile = tileset->FirstChildElement("tile");

	while (tile != nullptr)
	{
		std::string imageName = "Data/Gfx/";
		imageName += tile->FirstChildElement("image")->Attribute("source");
		TileBlueprint tileBP;
		tileBP.mySpriteName = imageName;
		tileBP.mySpriteSize = Vector2<float>(tile->FirstChildElement("image")->IntAttribute("width"), tile->FirstChildElement("image")->IntAttribute("height"));
		myTileTypes.Add(tileBP);

		tile = tile->NextSiblingElement("tile");
	}
	tinyxml2::XMLElement *layerElement = rootElement->FirstChildElement("layer");

	while (layerElement != nullptr)
	{
		std::string layerName = layerElement->Attribute("name");

		myMapDimensions.x = layerElement->IntAttribute("width");
		myMapDimensions.y = layerElement->IntAttribute("height");

		short currentWidth = 0;
		short currentHeight = 0;
		short tileCount = 0;
		tinyxml2::XMLElement *tileElement = layerElement->FirstChildElement()->FirstChildElement();

		while (tileElement != nullptr)
		{
			tileCount++;

			if (tileElement->IntAttribute("gid") > 0)
			{
				if (layerName == "Actor")
				{
					GameObject newTile("Tile", "tile");
					CollisionBoxComponent* cbToAdd2 = new CollisionBoxComponent(newTile, { 64, 64 });
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::ACTORS);
					newTile.AddComponent(cbToAdd2);
					newTile.AddComponent(mcToAdd2);
					newTile.SetPosition({ currentWidth * 64.f, currentHeight * 64.f });
					myCollidingTiles.Add(newTile);
				}
				else if (layerName == "Ground")
				{
					GameObject newTile("Tile", "tile");
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::GROUND);
					newTile.AddComponent(mcToAdd2);
					newTile.SetPosition({ currentWidth * 64.f, currentHeight * 64.f });
					myCosmeticTiles.Add(newTile);
				}
				else if (layerName == "Ground2")
				{
					GameObject newTile("Tile", "tile");
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::GROUND2);
					newTile.AddComponent(mcToAdd2);
					newTile.SetPosition({ currentWidth * 64.f, currentHeight * 64.f });
					myCosmeticTiles.Add(newTile);
				}
				else if (layerName == "Upper")
				{
					GameObject newTile("Tile", "tile");
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::UPPER);
					newTile.AddComponent(mcToAdd2);
					newTile.SetPosition({ currentWidth * 64.f, currentHeight * 64.f });
					myCosmeticTiles.Add(newTile);
				}
				else if (layerName == "Top")
				{
					GameObject newTile("Tile", "tile");
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::TOP);
					newTile.AddComponent(mcToAdd2);
					newTile.SetPosition({ currentWidth * 64.f, currentHeight * 64.f });
					myCosmeticTiles.Add(newTile);
				}

			}

			currentWidth++;
			if (currentWidth >= myMapDimensions.x)
			{
				currentWidth = 0;
				currentHeight++;
			}
			tileElement = tileElement->NextSiblingElement("tile");
		}

		layerElement = layerElement->NextSiblingElement();
	}

	//tinyxml2::XMLElement *objectGroup = rootElement->FirstChildElement("objectgroup");
	//while (objectGroup != nullptr)
	//{
	//	std::string groupName = objectGroup->Attribute("name");
	//	if (groupName == "Spawns")
	//	{
	//		tinyxml2::XMLElement *objectElement = objectGroup->FirstChildElement();
	//		while (objectElement != nullptr)
	//		{
	//			std::string objectName = objectElement->Attribute("name");

	//			if (objectName == "playerspawn")
	//			{
	//				//myPlayer->SetPosition({ objectElement->FloatAttribute("x"), objectElement->FloatAttribute("y") });
	//			}
	//			objectElement = objectElement->NextSiblingElement();
	//		}

	//	}
	//	objectGroup = objectGroup->NextSiblingElement();
	//}
}
