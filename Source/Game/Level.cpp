#include "stdafx.h"
#include "Level.h"
#include "Camera.h"
#include "../Common Utilities/tinyxml2.h"

#include "ModelComponent.h"
#include "MovementComponent.h"
#include "PlayerControllerComponent.h"
#include "StatsComponent.h"
#include "SwordComponent.h"
#include "AnimationComponent.h"
#include "CollisionBoxComponent.h"
#include "AIControllerComponent.h"
#include "WalkTowardsPlayer.h"
#include "ExitComponent.h"

#define NUMBER_OF_GAMEOBJECTS 4096

Level::Level()
{
}


Level::~Level()
{
}

void Level::Init(const std::string & aMapName, GameObject* aPlayer, const Vector2<float>& aPlayerPosition)
{
	ObserveEvent(CU::eEvent::KEYBOARD_INPUT_EVENT, HANDLE_EVENT_FUNCTION(HandleKeyboardInput));

	myCollisionManager.Init();
	myGameObjects.Init(NUMBER_OF_GAMEOBJECTS);
	myTileTypes.Init(128);
	myCollidingTiles.Init(4096);
	myCosmeticTiles.Init(4096);
	myExits.Init(8);
	myPlayer = aPlayer;
	LoadMap(aMapName);
	
	myPlayer->SetPosition(aPlayerPosition);
	Camera::GetInstance()->SetPosition(myPlayer->GetPosition());

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

}

void Level::Update()
{
	Camera::GetInstance()->MoveTo(myPlayer->GetPosition());
	myPlayer->Update();
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
	myCollisionManager.PlayerVsLevelObjects(*myPlayer, myCollidingTiles);
	myCollisionManager.PlayerVsDamageCircles(*myPlayer);
	myCollisionManager.ActorsVsLevelObjects(myGameObjects, myCollidingTiles);
	myCollisionManager.ActorsVsDamageCircles(myGameObjects);
	myCollisionManager.PlayerVsActors(*myPlayer, myGameObjects);
	myCollisionManager.PlayerVsExits(*myPlayer, myExits);
	myCollisionManager.Render();
	myCollisionManager.Update();
	RemoveDeadGameObjects();


	RenderCommandText rct;
	rct.myPosition = { 0.1f, 0.2f };
	rct.myText = "Number of GOs: ";
	rct.myText = std::to_string(myGameObjects.Size() + myCollidingTiles.Size() + myCosmeticTiles.Size());
	rct.mySize = 0.5f;
	Renderer::GetInstance()->AddRenderCommandText(rct);
}

void Level::DestroyLevel()
{
	for (unsigned short i = 0; i < myGameObjects.Size(); i++)
	{
		myGameObjects[i].Destroy();
	}

	for (unsigned short i = 0; i < myCollidingTiles.Size(); i++)
	{
		myCollidingTiles[i].Destroy();
	}

	for (unsigned short i = 0; i < myCosmeticTiles.Size(); i++)
	{
		myCosmeticTiles[i].Destroy();
	}

	for (unsigned short i = 0; i < myExits.Size(); i++)
	{
		myExits[i].Destroy();
	}
	myGameObjects.RemoveAll();
	myCollidingTiles.RemoveAll();
	myCosmeticTiles.RemoveAll();
	myExits.RemoveAll();

}

void Level::RemoveDeadGameObjects()
{
	for (unsigned short i = 0; i < myGameObjects.Size(); i++)
	{
		if (myGameObjects[i].GetShouldBeRemoved() == true)
		{
			myGameObjects[i].Destroy();
			myGameObjects.RemoveAtIndex(i);
			--i;
		}
	}
}

void Level::LoadMap(const std::string & aMapName)
{
	tinyxml2::XMLDocument doc;
	//level01.tmx
	std::string dir = "Data/Maps/";
	dir += aMapName;
	dir += ".tmx";
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
					CollisionBoxComponent* cbToAdd2 = new CollisionBoxComponent(newTile, eCollisionGroup::TILE, { 64, 64 });
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::ACTORS);
					newTile.AddComponent(cbToAdd2);
					newTile.AddComponent(mcToAdd2);
					newTile.SetPosition({ currentWidth * 64.f, currentHeight * 64.f });
					myCollidingTiles.Add(newTile);
				}
				else if (layerName == "GroundBlock")
				{
					GameObject newTile("Tile", "tile");
					CollisionBoxComponent* cbToAdd2 = new CollisionBoxComponent(newTile, eCollisionGroup::TILE, { 64, 64 });
					ModelComponent* mcToAdd2 = new ModelComponent(newTile, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteName, myTileTypes[tileElement->IntAttribute("gid") - 1].mySpriteSize, { 0.5f, 0.5f }, eRenderLayer::GROUND_BLOCK);
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

	tinyxml2::XMLElement *objectGroup = rootElement->FirstChildElement("objectgroup");
	while (objectGroup != nullptr)
	{
		std::string groupName = objectGroup->Attribute("name");
		if (groupName == "Exits")
		{
			tinyxml2::XMLElement *objectElement = objectGroup->FirstChildElement();
			while (objectElement != nullptr)
			{
				Vector2<float> position;
				Vector2<float> size;
				std::string targetName;
				Vector2<float> targetPosition;

				position.x = objectElement->FloatAttribute("x");
				position.y = objectElement->FloatAttribute("y");
				size.x = objectElement->FloatAttribute("width");
				size.y = objectElement->FloatAttribute("height");

				tinyxml2::XMLElement *properties = objectElement->FirstChildElement()->FirstChildElement();

				while (properties != nullptr)
				{
					std::string propertyName = properties->Attribute("name");
					if (propertyName == "PositionX")
					{
						targetPosition.x = properties->FloatAttribute("value");
					}
					else if (propertyName == "PositionY")
					{
						targetPosition.y = properties->FloatAttribute("value");
					}
					else if (propertyName == "TargetMap")
					{
						targetName = properties->Attribute("value");
					}
					properties = properties->NextSiblingElement();
				}

				GameObject exitGO("exit", "exit");
				CollisionBoxComponent* cbToAdd2 = new CollisionBoxComponent(exitGO, eCollisionGroup::EXIT, size, { 0,0 });
				ExitComponent* exitComponent = new ExitComponent(exitGO, targetPosition, targetName);
				exitGO.AddComponent(cbToAdd2);
				exitGO.AddComponent(exitComponent);
				exitGO.SetPosition(position);
				myExits.Add(exitGO);

				objectElement = objectElement->NextSiblingElement();
			}

		}
		objectGroup = objectGroup->NextSiblingElement();
	}
	
}


bool Level::HandleKeyboardInput(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, CU::KeyboardInputEvent, keyEvent);

	switch (keyEvent->myKeyboardKey)
	{
	case eKeyboardKeys::KEY_SPACE:
	{
		if (keyEvent->myKeyState == eKeyState::DOWN)
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
		}
	}
	break;
	default:
		break;
	}
	return true;
}
