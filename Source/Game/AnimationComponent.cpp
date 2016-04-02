#include "stdafx.h"
#include "AnimationComponent.h"
#include "RenderCommand.h"
#include "GameObject.h"
#include "Camera.h"
#include "tga2d\sprite\sprite.h"
#include "ResourceManager.h"
#define BLINK_LENGTH 0.2f


AnimationComponent::AnimationComponent(GameObject& aGameObject) : Component(aGameObject)
{
	Vector2<int> screenDim = CU::EventManager::GetInstance()->GetScreenDimensions();
	myRenderLayer = eRenderLayer::ACTORS;
	myIsBlinking = false;
	myShouldRender = true;
	myBlinkTimer = 0;

	AnimationInitData walkAnimationLeft;
	walkAnimationLeft.myFrameTime = 0.1f;
	walkAnimationLeft.myNumberOfFrames = 4;
	walkAnimationLeft.myPath = "Data/Gfx/Characters/hero/HeroWalkLeft.png";
	walkAnimationLeft.myType = eAnimationTypes::WALK;
	walkAnimationLeft.myDirection = eDirections::LEFT;
	walkAnimationLeft.myRectSize = { 64, 64 };
	walkAnimationLeft.mySheetSize = { 256, 64 };

	AnimationInitData walkAnimationRight;
	walkAnimationRight.myFrameTime = 0.1f;
	walkAnimationRight.myNumberOfFrames = 4;
	walkAnimationRight.myPath = "Data/Gfx/Characters/hero/HeroWalkRight.png";
	walkAnimationRight.myType = eAnimationTypes::WALK;
	walkAnimationRight.myDirection = eDirections::RIGHT;
	walkAnimationRight.myRectSize = { 64, 64 };
	walkAnimationRight.mySheetSize = { 256, 64 };

	AnimationInitData walkAnimationUp;
	walkAnimationUp.myFrameTime = 0.1f;
	walkAnimationUp.myNumberOfFrames = 4;
	walkAnimationUp.myPath = "Data/Gfx/Characters/hero/HeroWalkUp.png";
	walkAnimationUp.myType = eAnimationTypes::WALK;
	walkAnimationUp.myDirection = eDirections::UP;
	walkAnimationUp.myRectSize = { 64, 64 };
	walkAnimationUp.mySheetSize = { 256, 64 };

	AnimationInitData walkAnimationDown;
	walkAnimationDown.myFrameTime = 0.1f;
	walkAnimationDown.myNumberOfFrames = 4;
	walkAnimationDown.myPath = "Data/Gfx/Characters/hero/HeroWalkDown.png";
	walkAnimationDown.myType = eAnimationTypes::WALK;
	walkAnimationDown.myDirection = eDirections::DOWN;
	walkAnimationDown.myRectSize = { 64, 64 };
	walkAnimationDown.mySheetSize = { 256, 64 };

	//-----WALK LEFT-----
	AnimationData& walkLeft = myAnimationData[static_cast<int>(walkAnimationLeft.myDirection)][static_cast<int>(walkAnimationLeft.myType)];
	walkLeft.myFrameTime = walkAnimationLeft.myFrameTime;
	walkLeft.myNumberOfFrames = walkAnimationLeft.myNumberOfFrames;
	walkLeft.myRectSize = walkAnimationLeft.myRectSize;
	walkLeft.myIsActive = true;

	mySpriteSheets[static_cast<int>(walkAnimationLeft.myDirection)][static_cast<int>(walkAnimationLeft.myType)] = ResourceManager::GetInstance()->GetSprite(walkAnimationLeft.myPath.c_str());
	DX2D::Vector2<unsigned int> walkLeftSheetSize = mySpriteSheets[static_cast<int>(walkAnimationLeft.myDirection)][static_cast<int>(walkAnimationLeft.myType)]->GetImageSize();
	mySpriteSheets[static_cast<int>(walkAnimationLeft.myDirection)][static_cast<int>(walkAnimationLeft.myType)]->SetTextureRect((walkLeft.myRectSize.x * walkLeft.myCurrentFrame) / walkLeftSheetSize.x, 0, ((walkLeft.myRectSize.x * walkLeft.myCurrentFrame) + walkLeft.myRectSize.x) / walkLeftSheetSize.x, walkLeft.myRectSize.y / walkLeftSheetSize.y);
	mySpriteSheets[static_cast<int>(walkAnimationLeft.myDirection)][static_cast<int>(walkAnimationLeft.myType)]->SetSize({ walkLeft.myRectSize.x / screenDim.y,walkLeft.myRectSize.y / screenDim.y });

	//--END OF WALK LEFT--

	//-----WALK RIGHT-----
	AnimationData& walkRight = myAnimationData[static_cast<int>(walkAnimationRight.myDirection)][static_cast<int>(walkAnimationRight.myType)];
	walkRight.myFrameTime = walkAnimationRight.myFrameTime;
	walkRight.myNumberOfFrames = walkAnimationRight.myNumberOfFrames;
	walkRight.myRectSize = walkAnimationRight.myRectSize;
	walkRight.myIsActive = true;

	mySpriteSheets[static_cast<int>(walkAnimationRight.myDirection)][static_cast<int>(walkAnimationRight.myType)] = ResourceManager::GetInstance()->GetSprite(walkAnimationRight.myPath.c_str());
	DX2D::Vector2<unsigned int> walkRightSheetSize = mySpriteSheets[static_cast<int>(walkAnimationRight.myDirection)][static_cast<int>(walkAnimationRight.myType)]->GetImageSize();
	mySpriteSheets[static_cast<int>(walkAnimationRight.myDirection)][static_cast<int>(walkAnimationRight.myType)]->SetTextureRect((walkRight.myRectSize.x * walkRight.myCurrentFrame) / walkRightSheetSize.x, 0, ((walkRight.myRectSize.x * walkRight.myCurrentFrame) + walkRight.myRectSize.x) / walkRightSheetSize.x, walkRight.myRectSize.y / walkRightSheetSize.y);
	mySpriteSheets[static_cast<int>(walkAnimationRight.myDirection)][static_cast<int>(walkAnimationRight.myType)]->SetSize({ walkRight.myRectSize.x / screenDim.y,walkRight.myRectSize.y / screenDim.y });


	//--END OF WALK RIGHT--

	//-----WALK UP-----
	AnimationData& walkUp = myAnimationData[static_cast<int>(walkAnimationUp.myDirection)][static_cast<int>(walkAnimationUp.myType)];
	walkUp.myFrameTime = walkAnimationUp.myFrameTime;
	walkUp.myNumberOfFrames = walkAnimationUp.myNumberOfFrames;
	walkUp.myRectSize = walkAnimationUp.myRectSize;
	walkUp.myIsActive = true;

	mySpriteSheets[static_cast<int>(walkAnimationUp.myDirection)][static_cast<int>(walkAnimationUp.myType)] = ResourceManager::GetInstance()->GetSprite(walkAnimationUp.myPath.c_str());
	DX2D::Vector2<unsigned int> walkUpSheetSize = mySpriteSheets[static_cast<int>(walkAnimationUp.myDirection)][static_cast<int>(walkAnimationUp.myType)]->GetImageSize();
	mySpriteSheets[static_cast<int>(walkAnimationUp.myDirection)][static_cast<int>(walkAnimationUp.myType)]->SetTextureRect((walkUp.myRectSize.x * walkUp.myCurrentFrame) / walkUpSheetSize.x, 0, ((walkUp.myRectSize.x * walkUp.myCurrentFrame) + walkUp.myRectSize.x) / walkUpSheetSize.x, walkUp.myRectSize.y / walkUpSheetSize.y);
	mySpriteSheets[static_cast<int>(walkAnimationUp.myDirection)][static_cast<int>(walkAnimationUp.myType)]->SetSize({ walkUp.myRectSize.x / screenDim.y,walkUp.myRectSize.y / screenDim.y });

	//--END OF WALK UP--

	//-----WALK DOWN-----
	AnimationData& walkDown = myAnimationData[static_cast<int>(walkAnimationDown.myDirection)][static_cast<int>(walkAnimationUp.myType)];
	walkDown.myFrameTime = walkAnimationDown.myFrameTime;
	walkDown.myNumberOfFrames = walkAnimationDown.myNumberOfFrames;
	walkDown.myRectSize = walkAnimationDown.myRectSize;
	walkDown.myIsActive = true;

	mySpriteSheets[static_cast<int>(walkAnimationDown.myDirection)][static_cast<int>(walkAnimationDown.myType)] = ResourceManager::GetInstance()->GetSprite(walkAnimationDown.myPath.c_str());
	DX2D::Vector2<unsigned int> walkDownSheetSize = mySpriteSheets[static_cast<int>(walkAnimationDown.myDirection)][static_cast<int>(walkAnimationDown.myType)]->GetImageSize();
	mySpriteSheets[static_cast<int>(walkAnimationDown.myDirection)][static_cast<int>(walkAnimationDown.myType)]->SetTextureRect((walkDown.myRectSize.x * walkDown.myCurrentFrame) / walkDownSheetSize.x, 0, ((walkDown.myRectSize.x * walkDown.myCurrentFrame) + walkDown.myRectSize.x) / walkDownSheetSize.x, walkDown.myRectSize.y / walkDownSheetSize.y);
	mySpriteSheets[static_cast<int>(walkAnimationDown.myDirection)][static_cast<int>(walkAnimationDown.myType)]->SetSize({ walkDown.myRectSize.x / screenDim.y,walkDown.myRectSize.y / screenDim.y });
	//--END OF WALK DOWN--


	myCurrentAnimation = eAnimationTypes::WALK;
	myDirection = eDirections::LEFT;
}


AnimationComponent::~AnimationComponent()
{
}


void AnimationComponent::Update()
{
	float deltaTime = CU::EventManager::GetInstance()->GetDeltaTime();

	AnimationData& animation = myAnimationData[static_cast<int>(myDirection)][static_cast<int>(myCurrentAnimation)];
	animation.myCurrentFrameTime += deltaTime;

	if (animation.myCurrentFrameTime >= animation.myFrameTime)
	{
		animation.myCurrentFrameTime = 0;
		animation.myCurrentFrame++;
		if (animation.myLoop == false && animation.myCurrentFrame >= animation.myNumberOfFrames)
		{
			animation.myCurrentFrame = animation.myNumberOfFrames;
		}
		else if (animation.myCurrentFrame >= animation.myNumberOfFrames)
		{
			animation.myCurrentFrame = 0;
		}
		Vector2<int> screenDim = CU::EventManager::GetInstance()->GetScreenDimensions();
		DX2D::Vector2<unsigned int> sheetSize = mySpriteSheets[static_cast<int>(myDirection)][static_cast<int>(myCurrentAnimation)]->GetImageSize();
		mySpriteSheets[static_cast<int>(myDirection)][static_cast<int>(myCurrentAnimation)]->SetTextureRect((animation.myRectSize.x * animation.myCurrentFrame) / sheetSize.x /*- animation.myRectSize.x*/, 0, ((animation.myRectSize.x * animation.myCurrentFrame) + animation.myRectSize.x) / sheetSize.x, animation.myRectSize.y / sheetSize.y);
	}


	RenderCommand rc;
	rc.mySprite = mySpriteSheets[static_cast<int>(myDirection)][static_cast<int>(myCurrentAnimation)];
	rc.mySpace = myParent->GetSpace();

	if (myIsBlinking == false)
	{
		Renderer::GetInstance()->AddRenderCommand(rc, myRenderLayer);
	}
	else
	{
		myBlinkDuration -= deltaTime;
		myBlinkTimer -= deltaTime;
		if (myBlinkTimer <= 0)
		{
			myShouldRender = !myShouldRender;
			myBlinkTimer = BLINK_LENGTH;
		}
		if (myShouldRender == true)
		{
			Renderer::GetInstance()->AddRenderCommand(rc, myRenderLayer);
		}
		if (myBlinkDuration <= 0)
		{
			myIsBlinking = false;
		}
	}
}

bool AnimationComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	switch (anEvent->GetMyType())
	{
	case CU::eEvent::CHANGE_ANIMATION:
		HandleAnimationEvent(anEvent);
		//ChangeAnimation(anEvent);
		break;
	case CU::eEvent::BLINK_MODEL:
	{
		GET_EVENT_DATA(anEvent, BlinkSpriteEvent, blinkEvent);

		myBlinkDuration = blinkEvent->myDuration;
		myIsBlinking = true;
		myShouldRender = false;
	}
	break;
	default:
		break;
	}
	return true;;
}

bool AnimationComponent::HandleAnimationEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, AnimationEvent, animationEvent)
		myDirection = animationEvent->myDirection;
	eAnimationTypes animationType = animationEvent->myAnimationType;
	if (myCurrentAnimation != animationType && myAnimationData[static_cast<int>(myDirection)][static_cast<int>(animationType)].myIsActive == true)
	{
		myAnimationData[static_cast<int>(myDirection)][static_cast<int>(myCurrentAnimation)].myCurrentFrame = 0;
		myAnimationData[static_cast<int>(myDirection)][static_cast<int>(myCurrentAnimation)].myCurrentFrameTime = 0;
		myCurrentAnimation = animationType;
	}
	return true;
}

void AnimationComponent::Destroy()
{

}