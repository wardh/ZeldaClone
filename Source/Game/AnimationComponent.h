#pragma once
#include "Component.h"

#include <string>
#include "../Common Utilities/StaticArray.h"
#include "AnimationData.h"

namespace DX2D
{
	class CSprite;
}

class AnimationComponent : public Component
{
public:
	AnimationComponent(GameObject& aGameObject);
	~AnimationComponent();

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;

	virtual void Destroy();
private:
	bool HandleAnimationEvent(const CU::PoolPointer<CU::Event>& anEvent);


	//CU::StaticArray<CU::StaticArray<SpriteHGE*, static_cast<int>(eAnimationTypes::MAX_SIZE)>, static_cast<int>(eDirections::NONE)> mySpriteSheets;
	CU::StaticArray<CU::StaticArray<DX2D::CSprite*, static_cast<int>(eAnimationTypes::MAX_SIZE)>, static_cast<int>(eDirections::NONE)> mySpriteSheets;
	CU::StaticArray<CU::StaticArray<AnimationData, static_cast<int>(eAnimationTypes::MAX_SIZE)>, static_cast<int>(eDirections::NONE)> myAnimationData;
	eDirections myDirection;
	eAnimationTypes myCurrentAnimation;

	eRenderLayer myRenderLayer;

	float myBlinkDuration;
	float myBlinkTimer;
	bool myShouldRender;
	bool myIsBlinking;
};

