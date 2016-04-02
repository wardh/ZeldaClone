#pragma once
#include "GameObject.h"
#include "Circle.h"

namespace DX2D
{
	class CSprite;
}

class CollisionManager : CU::Observer
{
public:
	CollisionManager();
	~CollisionManager();

	void Init();
	void Update();
	void Render();

	void ActorsVsLevelObjects(CU::GrowingArray<GameObject>& someActors, CU::GrowingArray<GameObject>& someTiles);
	void ActorsVsDamageCircles(CU::GrowingArray<GameObject>& someActors);
	void ActorsVsBullets(CU::GrowingArray<GameObject>& someActors, CU::GrowingArray<GameObject*>& someBullets);
	void PlayerVsActors(GameObject& aPlayer, CU::GrowingArray<GameObject>& someActors);

	bool HandleSpawnDamageCircleEvent(const CU::PoolPointer<CU::Event>& anEvent);

	CU::GrowingArray<CircleStruct> myCircles;
	DX2D::CSprite* myCircleSprite;
};

