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

class Level;

class CGameWorld : CU::Observer
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta); 
private:

	bool HandleKeyboardInput(const CU::PoolPointer<CU::Event>& anEvent);
	bool HandleXPEvent(const CU::PoolPointer<CU::Event>& anEvent);
	bool HandleChangeLevelEvent(const CU::PoolPointer<CU::Event>& anEvent);

	Level* myCurrentLevel;

	GameObject myPlayer;
};