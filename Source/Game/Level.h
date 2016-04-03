#pragma once

#include "GameObject.h"
#include "TileBlueprints.h"
#include "CollisionManager.h"
#include "../Common Utilities/Observer.h"

class Level
{
public:
	Level();
	~Level();

	void Init(const std::string& aMapName);
	void Update(float aTimeDelta);

private:

	void RemoveDeadGameObjects();

	void LoadMap(const std::string& aMapName);
	CU::GrowingArray<TileBlueprint> myTileTypes;
	CU::GrowingArray<GameObject> myGameObjects;
	CU::GrowingArray<GameObject> myCollidingTiles;
	CU::GrowingArray<GameObject> myCosmeticTiles;
	CollisionManager myCollisionManager;
	Vector2<int> myMapDimensions;
};

