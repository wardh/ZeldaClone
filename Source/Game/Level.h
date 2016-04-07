#pragma once

#include "GameObject.h"
#include "TileBlueprints.h"
#include "CollisionManager.h"
#include "../Common Utilities/Observer.h"

class Level : CU::Observer
{
public:
	Level();
	~Level();

	void Init(const std::string& aMapName, GameObject* aPlayer, const Vector2<float>& aPlayerPosition);
	void Update();
	void DestroyLevel();
private:
	bool HandleKeyboardInput(const CU::PoolPointer<CU::Event>& anEvent);

	void RemoveDeadGameObjects();

	void LoadMap(const std::string& aMapName);


	GameObject* myPlayer;


	CU::GrowingArray<TileBlueprint> myTileTypes;
	CU::GrowingArray<GameObject> myGameObjects;
	CU::GrowingArray<GameObject> myCollidingTiles;
	CU::GrowingArray<GameObject> myExits;
	CU::GrowingArray<GameObject> myCosmeticTiles;
	CollisionManager myCollisionManager;
	Vector2<int> myMapDimensions;
};

