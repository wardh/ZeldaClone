#include "stdafx.h"
#include "GameObjectFactory.h"
#include "AIControllerComponent.h"
#include "MovementComponent.h"
#include "StatsComponent.h"
#include "CollisionBoxComponent.h"
#include "ModelComponent.h"
#include "WalkTowardsPlayer.h"
#include "CollisionGroups.h"
#include "SwordComponent.h"
#include "SwordBehaviour.h"

GameObjectFactory* GameObjectFactory::ourInstance = nullptr;

GameObjectFactory::GameObjectFactory()
{
}


GameObjectFactory::~GameObjectFactory()
{
}

GameObjectFactory * GameObjectFactory::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new GameObjectFactory();
		ourInstance->Init();
	}
	return ourInstance;
}

GameObject GameObjectFactory::CreateGameObjectFromFile(const std::string& aFileName)
{
	tinyxml2::XMLDocument doc;
	std::string dir = "Data/Prefabs/";
	dir += aFileName;
	dir += ".xml";
	tinyxml2::XMLError status = doc.LoadFile(dir.c_str());
	if (status == tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND)
	{
		DL_ASSERT(dir.c_str());
	}
	tinyxml2::XMLElement *rootElement = doc.RootElement();
	std::string tag = rootElement->Attribute("tag");

	GameObject gameObject = GameObject(tag, tag);
	tinyxml2::XMLElement *component = rootElement->FirstChildElement();

	while (component != nullptr)
	{
		std::string componentType = component->Name();
		if (componentType == "AIControllerComponent")
		{
			gameObject.AddComponent(CreateAIControllerComponent(component, gameObject));
		}
		else if (componentType == "CollisionBoxComponent")
		{
			gameObject.AddComponent(CreateCollisionBoxComponent(component, gameObject));
		}
		else if (componentType == "MovementComponent")
		{
			gameObject.AddComponent(CreateMovementComponent(component, gameObject));
		}
		else if (componentType == "ModelComponent")
		{
			gameObject.AddComponent(CreateModelComponent(component, gameObject));
		}
		else if (componentType == "StatsComponent")
		{
			gameObject.AddComponent(CreateStatsComponent(component, gameObject));
		}
		else if (componentType == "SwordComponent")
		{
			gameObject.AddComponent(CreateSwordComponent(component, gameObject));
		}
		component = component->NextSiblingElement();
	}

	return gameObject;
}



void GameObjectFactory::Init()
{
}

AIControllerComponent* GameObjectFactory::CreateAIControllerComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject)
{
	std::string behaviourName = aXMLElement->Attribute("behaviour");
	if (behaviourName == "WalkTowardsPlayer")
	{
		return new AIControllerComponent(aGameObject, new WalkTowardsPlayer());
	}
	else if (behaviourName == "SwordBehaviour")
	{
		return new AIControllerComponent(aGameObject, new SwordBehaviour());
	}
}

CollisionBoxComponent* GameObjectFactory::CreateCollisionBoxComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject)
{
	std::string group = aXMLElement->Attribute("group");
	eCollisionGroup collisionGroup;

	Vector2<float> size;
	Vector2<float> centerPosition;

	if (group == "enemy")
	{
		collisionGroup = eCollisionGroup::ENEMY;
	}
	else if (group == "player")
	{
		collisionGroup = eCollisionGroup::PLAYER;
	}
	else if (group == "tile")
	{
		collisionGroup = eCollisionGroup::TILE;
	}
	else if (group == "exit")
	{
		collisionGroup = eCollisionGroup::EXIT;
	}

	size.x = aXMLElement->FloatAttribute("sizeX");
	size.y = aXMLElement->FloatAttribute("sizeY");
	centerPosition.x = aXMLElement->FloatAttribute("centerX");
	centerPosition.y = aXMLElement->FloatAttribute("centerY");

	return new CollisionBoxComponent(aGameObject, collisionGroup, size, centerPosition);
}

MovementComponent* GameObjectFactory::CreateMovementComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject)
{
	return new MovementComponent(aGameObject);
}

ModelComponent* GameObjectFactory::CreateModelComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject)
{
	std::string path = aXMLElement->Attribute("path");
	std::string layer = aXMLElement->Attribute("layer");
	eRenderLayer renderLayer;

	if (layer == "actors")
	{
		renderLayer = eRenderLayer::ACTORS;
	}
	else if (layer == "bottom")
	{
		renderLayer = eRenderLayer::BOTTOM;
	}
	else if (layer == "ground_block")
	{
		renderLayer = eRenderLayer::GROUND_BLOCK;
	}
	else if (layer == "ground")
	{
		renderLayer = eRenderLayer::GROUND;
	}
	else if (layer == "ground2")
	{
		renderLayer = eRenderLayer::GROUND2;
	}
	else if (layer == "upper")
	{
		renderLayer = eRenderLayer::UPPER;
	}
	else if (layer == "top")
	{
		renderLayer = eRenderLayer::TOP;
	}
	else if (layer == "gui")
	{
		renderLayer = eRenderLayer::GUI;
	}

	return new ModelComponent(aGameObject, path, renderLayer);

}

StatsComponent* GameObjectFactory::CreateStatsComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject)
{
	//movementSpeed = "100" isFriendly = "false" health = "3" damage = "1" level = "1" / >
	StatsStruct stats;

	stats.myMovementSpeed = aXMLElement->FloatAttribute("movementSpeed");
	stats.myMaxHealth = aXMLElement->IntAttribute("health");
	stats.myDamage = aXMLElement->IntAttribute("damage");
	stats.myLevel = aXMLElement->IntAttribute("level");
	std::string isFriendly = aXMLElement->Attribute("isFriendly");
	if (isFriendly == "false")
	{
		stats.myIsFriendly = false;
	}
	else
	{
		stats.myIsFriendly = true;
	}

	return new StatsComponent(aGameObject, stats);
}

SwordComponent* GameObjectFactory::CreateSwordComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject)
{
	SwordStruct swordStruct;
	swordStruct.mySpritePath = aXMLElement->Attribute("path");
	swordStruct.myReach = aXMLElement->FloatAttribute("reach");
	swordStruct.mySwingTime = aXMLElement->FloatAttribute("swingTime");
	return new SwordComponent(aGameObject, swordStruct);

}
