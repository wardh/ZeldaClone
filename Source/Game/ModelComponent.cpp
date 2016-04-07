#include "stdafx.h"
#include "ModelComponent.h"
#include "RenderCommand.h"
#include "GameObject.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "ComponentEnums.h"
#include "ComponentEvents.h"

#define BLINK_LENGTH 0.2f

ModelComponent::ModelComponent(GameObject& aGameObject) : Component(aGameObject)
{
	mySprite = ResourceManager::GetInstance()->GetSprite("Data/Gfx/Characters/hero.png");
	//mySprite = new DX2D::CSprite("Data/Gfx/Characters/hero.png");
	mySprite->SetPivot({ 0.5f, 0.5f });
	myIsBlinking = false;
	myShouldRender = true;
	myRenderLayer = eRenderLayer::BOTTOM;
	myBlinkTimer = 0;
}

ModelComponent::ModelComponent(GameObject & aGameObject, const std::string & aPath, eRenderLayer aRenderLayer) : Component(aGameObject)
{
	mySprite = ResourceManager::GetInstance()->GetSprite(aPath.c_str());
	//mySprite = ResourceManager::GetInstance()->GetSprite(aPath, aSize, aHotSpot);
	//mySprite = new DX2D::CSprite(aPath.c_str());
	mySprite->SetPivot({ 0.5f, 0.5f });
	//mySprite->SetSize({ aSize.x, aSize.y });
	myRenderLayer = aRenderLayer;
	myIsBlinking = false;
	myBlinkTimer = 0;
	myShouldRender = true;
}

ModelComponent::ModelComponent(GameObject& aGameObject, const std::string& aPath, const Vector2<float>& aSize, const Vector2<float>& aHotSpot, eRenderLayer aRenderLayer) : Component(aGameObject)
{
	mySprite = ResourceManager::GetInstance()->GetSprite(aPath.c_str());
	//mySprite = ResourceManager::GetInstance()->GetSprite(aPath, aSize, aHotSpot);
	//mySprite = new DX2D::CSprite(aPath.c_str());
	mySprite->SetPivot({ aHotSpot.x, aHotSpot.y });
	//mySprite->SetSize({ aSize.x, aSize.y });
	myRenderLayer = aRenderLayer;
	myIsBlinking = false;
	myBlinkTimer = 0;
	myShouldRender = true;
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::Update()
{
	RenderCommand rc;
	rc.mySprite = mySprite;
	rc.mySpace = myParent->GetSpace();
	//rc.myIsFlipped = myIsFlipped;
	Vector2<int> dimensions = CU::EventManager::GetInstance()->GetScreenDimensions();
	Vector2<float> parentPos = myParent->GetPosition();
	DX2D::Vector2<float> finalPosition;
	finalPosition.x = parentPos.x / dimensions.x;
	finalPosition.y = parentPos.y / dimensions.y;
	mySprite->SetPosition(finalPosition);
	if (myIsBlinking == false)
	{
		//Camera::GetInstance()->AddRenderCommand(rc);
		Renderer::GetInstance()->AddRenderCommand(rc, myRenderLayer);
		//mySprite->Render();
	}
	else
	{
		float deltaTime = CU::EventManager::GetInstance()->GetDeltaTime();
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

			//Camera::GetInstance()->AddRenderCommand(rc);
		}
		if (myBlinkDuration <= 0)
		{
			myIsBlinking = false;
		}
	}
}

bool ModelComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	switch (anEvent->GetMyType())
	{
	case CU::eEvent::ACTOR_DIRECTION:
	{
		GET_EVENT_DATA(anEvent, ActorDirectionEvent, actorDirection)
		if (actorDirection->myDirection == eDirections::LEFT)
		{
			myIsFlipped = true;
		}
		else if (actorDirection->myDirection == eDirections::RIGHT)
		{
			myIsFlipped = false;
		}
	}
	break;
	case CU::eEvent::CHANGE_SPRITE:
		//mySprite = ResourceManager::GetInstance()->GetSprite(anEvent.GetMyTextData(), { 32, 32 }, { 16,16 });
		break;
	case CU::eEvent::BLINK_MODEL:
	{
		GET_EVENT_DATA(anEvent, BlinkSpriteEvent, blinkEvent)

		myBlinkDuration = blinkEvent->myDuration;
		myIsBlinking = true;
		myShouldRender = false;
	}
		break;
	default:
		break;
	}
	return true;
}



void ModelComponent::Destroy()
{

}