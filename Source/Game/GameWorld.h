#pragma once
#include <vector>
#include "GameObject.h"
#include "TileBlueprints.h"
#include "CollisionManager.h"
#include "../Common Utilities/Observer.h"
namespace DX2D
{
	class CSprite;
	class CSpriteBatch;
	class CText;
	class CCustomShape;
} 

class CGameWorld : CU::Observer
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
private:

	bool HandleKeyboardInput(const CU::PoolPointer<CU::Event>& anEvent);

	void RemoveDeadGameObjects();

	void LoadMap();
	CU::GrowingArray<TileBlueprint> myTileTypes;
	CU::GrowingArray<GameObject> myGameObjects;
	CU::GrowingArray<GameObject> myCollidingTiles;
	CU::GrowingArray<GameObject> myCosmeticTiles;
	CollisionManager myCollisionManager;
	Vector2<int> myMapDimensions;

	
};