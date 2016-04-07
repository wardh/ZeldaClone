#include "stdafx.h"
#include "CollisionComponent.h"


CollisionComponent::CollisionComponent(GameObject& aGameObject, eCollisionGroup aCollisionGroup) : Component(aGameObject)
{
	myPosition = { 0, 0 };
	myCollisionGroup = aCollisionGroup;
}

CollisionComponent::CollisionComponent(GameObject& aGameObject, eCollisionGroup aCollisionGroup, const Vector2<float>& aCenterPosition) : Component(aGameObject)
{
	myPosition = aCenterPosition;
	myCollisionGroup = aCollisionGroup;
}



CollisionComponent::~CollisionComponent()
{
}


void CollisionComponent::SetPosition(const Vector2<float>& aPosition)
{
	myPosition = aPosition;
}

const Vector2<float>& CollisionComponent::GetPosition() const
{
	return myPosition;
}

void CollisionComponent::SetData() 
{

}