#include "stdafx.h"
#include "MovementComponent.h"
#include "GameObject.h"
#include "CollisionBoxComponent.h"
#include "ComponentEnums.h"
	
#define GRAVITY 1000.f
#define PUSH_BACK_STRENGTH 500.f

MovementComponent::MovementComponent(GameObject& aGameObject) : Component(aGameObject)
{
	myVelocity = { 0, 0 };
	myWalkedThisFrame = false;
	myParent->SetValue<const eDirections*>("Direction", &myDirection);
	myDirection = eDirections::DOWN;
	myDamageVelocity = { 0,0 };
}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::Update()
{
	float deltaTime = CU::EventManager::GetInstance()->GetDeltaTime();
	myOldPosition = myParent->GetPosition();
	float movementSpeed = 10.f;
	if (myParent->ValueExists<const float*>("MovementSpeed") == true)
	{
		movementSpeed = *myParent->GetValue<const float*>("MovementSpeed");
	}

	if (myWalkedThisFrame == true)
	{
		Vector2<float> movementVector = GetNormalized(myMovementDirection) * movementSpeed;
		myParent->SetPosition(myParent->GetPosition() + (movementVector*deltaTime));
		//CU::Event animationEvent(CU::eEvent::CHANGE_ANIMATION, eAnimationTypes::WALK, myDirection);
		//myParent->HandleInternalEvent(animationEvent);
		AnimationEvent animationEvent;
		animationEvent.myAnimationType = eAnimationTypes::WALK;
		animationEvent.myDirection = myDirection;                     
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(animationEvent));
	}
	myParent->SetPosition(myParent->GetPosition() + (myDamageVelocity*deltaTime));
	myDamageVelocity -= myDamageVelocity *4.f* deltaTime;

	myMovementDirection = { 0, 0 };
	myWalkedThisFrame = false;
}

bool MovementComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	switch (anEvent->GetMyType())
	{
	case CU::eEvent::MOVE_LEFT:
		MoveLeft();
		break;
	case CU::eEvent::MOVE_RIGHT:
		MoveRight();
		break;
	case CU::eEvent::MOVE_UP:
		MoveUp();
		break;
	case CU::eEvent::MOVE_DOWN:
		MoveDown();
		break;
	case CU::eEvent::COLLISION_BOX_COMPONENT:
		HandleCollider(anEvent);
		break;
	case CU::eEvent::ADD_DAMAGE_VELOCITY:
	{
		GET_EVENT_DATA(anEvent, AddDamageVelocity, velocityEvent)
		Vector2<float> damageDirection = GetNormalized(myParent->GetPosition() - velocityEvent->myPosition);
		myDamageVelocity = damageDirection * PUSH_BACK_STRENGTH;
	}
	break;

	default:
		break;
	}
	return true;
}

void MovementComponent::HandleCollider(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, CollisionBoxEvent, boxEvent);
	CollisionBoxComponent* parentCollider = myParent->GetValue<CollisionBoxComponent*>("CollisionBoxComponent");
	
	Vector2<float> position = myParent->GetPosition();
	myParent->SetPosition(myOldPosition);
	myParent->SetPosition({ position.x, myOldPosition.y });
	if (parentCollider->CheckCollision(*boxEvent->myCollisionBoxComponent))
	{
		myParent->SetPosition(myOldPosition);
	}
	myParent->SetPosition({ myParent->GetPosition().x, position.y });
	if (parentCollider->CheckCollision(*boxEvent->myCollisionBoxComponent))
	{
		myParent->SetPosition({ myParent->GetPosition().x, myOldPosition.y });
	}
}


void MovementComponent::MoveLeft()
{
	myMovementDirection.x -= 1;
	myWalkedThisFrame = true;
	myDirection = eDirections::LEFT;
}

void MovementComponent::MoveRight()
{
	myMovementDirection.x += 1;
	myWalkedThisFrame = true;
	myDirection = eDirections::RIGHT;

}

void MovementComponent::MoveUp()
{
	myMovementDirection.y -= 1;
	myWalkedThisFrame = true;
	myDirection = eDirections::UP;

}

void MovementComponent::MoveDown()
{
	myMovementDirection.y += 1;
	myWalkedThisFrame = true;
	myDirection = eDirections::DOWN;

}

void MovementComponent::SetData()
{
	myParent->SetValue<const eDirections*>("Direction", &myDirection);
}

void MovementComponent::Destroy()
{

}