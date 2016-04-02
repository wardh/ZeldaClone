#include "stdafx.h"
#include "CollisionComponent.h"


CollisionComponent::CollisionComponent(GameObject& aGameObject) : Component(aGameObject)
{
	myPosition = { 0, 0 };
}

CollisionComponent::CollisionComponent(GameObject& aGameObject, const Vector2<float>& aCenterPosition) : Component(aGameObject)
{
	myPosition = aCenterPosition;
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