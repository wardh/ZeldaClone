#include "stdafx.h"
#include "AIControllerComponent.h"
#include "Behaviour.h"
#include "GameObject.h"
#include "ComponentEnums.h"
#include "../Common Utilities/EventManager.h"

AIControllerComponent::AIControllerComponent(GameObject& aGameObject, Behaviour* aBehaviour) : Component(aGameObject)
{
	myBehaviour = aBehaviour;
}

AIControllerComponent::~AIControllerComponent()
{
}


void AIControllerComponent::Update()
{
	ActorInfo info;
	info.myPosition = myParent->GetPosition();
	BehaviourStruct behaviour;
	behaviour = myBehaviour->GetBehaviour(info);

	switch (behaviour.myMoveDirection)
	{
	case eDirections::NONE:
		break;
	case eDirections::LEFT:
	{
		myDirection = eDirections::LEFT;
		if (behaviour.myShouldWalk == true)
		{
			CU::Event eventToAdd;
			eventToAdd = CU::Event(CU::eEvent::MOVE_LEFT);
			myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent( eventToAdd));
		}
	}
		break;
	case eDirections::RIGHT:
	{
		myDirection = eDirections::RIGHT;
		if (behaviour.myShouldWalk == true)
		{
			CU::Event eventToAdd;
			eventToAdd = CU::Event(CU::eEvent::MOVE_RIGHT);
			myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));

		}
	}
		break;
	case eDirections::UP:
	{
		myDirection = eDirections::UP;
		if (behaviour.myShouldWalk == true)
		{
			CU::Event eventToAdd;
			eventToAdd = CU::Event(CU::eEvent::MOVE_UP);
			myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));

		}
	}
		break;
	case eDirections::DOWN:
	{
		myDirection = eDirections::DOWN;
		if (behaviour.myShouldWalk == true)
		{
			CU::Event eventToAdd;
			eventToAdd = CU::Event(CU::eEvent::MOVE_DOWN);
			myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));

		}
	}
		break;
	default:
		break;
	}

	
	//CU::Event directionEvent(CU::eEvent::ACTOR_DIRECTION, myDirection);
	//myParent->HandleInternalEvent(directionEvent);
}

bool AIControllerComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	return true;
}

bool AIControllerComponent::HandleEvent(const CU::Event& anEvent)
{
	return true;
}

void AIControllerComponent::SetData()
{

}

void AIControllerComponent::Destroy()
{
	SAFE_DELETE(myBehaviour);
}