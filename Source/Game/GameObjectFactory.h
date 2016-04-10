#pragma once
#include "GameObject.h"
#include "../Common Utilities/tinyxml2.h"

class AIControllerComponent;
class CollisionBoxComponent;
class MovementComponent;
class ModelComponent;
class StatsComponent;
class SwordComponent;

class GameObjectFactory
{
public:

	static GameObjectFactory* GetInstance();
	GameObject CreateGameObjectFromFile(const std::string& aFileName);
private:
	GameObjectFactory();
	~GameObjectFactory();

	void Init();

	AIControllerComponent* CreateAIControllerComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject);
	CollisionBoxComponent* CreateCollisionBoxComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject);
	MovementComponent* CreateMovementComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject);
	ModelComponent* CreateModelComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject);
	StatsComponent* CreateStatsComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject);
	SwordComponent* CreateSwordComponent(tinyxml2::XMLElement* aXMLElement, GameObject& aGameObject);

	static GameObjectFactory* ourInstance;
};

