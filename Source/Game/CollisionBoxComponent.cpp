#include "stdafx.h"
#include "CollisionBoxComponent.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "../Common Utilities/Intersection.h"
#include "Circle.h"
//debug
#include "Camera.h"
#include "RenderCommand.h"

CollisionBoxComponent::CollisionBoxComponent(GameObject& aGameObject, const Vector2<float>& someDimensions) : CollisionComponent(aGameObject)
{
	myDimensions = someDimensions;
	Line<float> aLine;

	Vector2<float> position1(-myDimensions.myX / 2, -myDimensions.myY / 2);
	Vector2<float> position2(-myDimensions.myX / 2, myDimensions.myY / 2);
	Vector2<float> position3(myDimensions.myX / 2, myDimensions.myY / 2);
	Vector2<float> position4(myDimensions.myX / 2, -myDimensions.myY / 2);

	aLine.InitWith2Points(position1, position2);
	myLineVolume.AddLine(aLine);

	aLine.InitWith2Points(position2, position3);
	myLineVolume.AddLine(aLine);

	aLine.InitWith2Points(position3, position4);
	myLineVolume.AddLine(aLine);

	aLine.InitWith2Points(position4, position1);
	myLineVolume.AddLine(aLine);

	myParent->SetValue<CollisionBoxComponent*>("CollisionBoxComponent", this);

	//mySprite = ResourceManager::GetInstance()->GetSprite("../Data/Gfx/debugBox.png", { someDimensions.x, someDimensions.y }, { someDimensions.x / 2.f, someDimensions.y / 2.f });
}

CollisionBoxComponent::CollisionBoxComponent(GameObject& aGameObject, const Vector2<float>& someDimensions, const Vector2<float>& aCenterPosition) : CollisionComponent(aGameObject, aCenterPosition)
{
	myDimensions = someDimensions;
	Line<float> aLine;

	Vector2<float> position1(-myDimensions.myX / 2, -myDimensions.myY / 2);
	Vector2<float> position2(-myDimensions.myX / 2, myDimensions.myY / 2);
	Vector2<float> position3(myDimensions.myX / 2, myDimensions.myY / 2);
	Vector2<float> position4(myDimensions.myX / 2, -myDimensions.myY / 2);

	aLine.InitWith2Points(position1, position2);
	myLineVolume.AddLine(aLine);

	aLine.InitWith2Points(position2, position3);
	myLineVolume.AddLine(aLine);

	aLine.InitWith2Points(position3, position4);
	myLineVolume.AddLine(aLine);

	aLine.InitWith2Points(position4, position1);
	myLineVolume.AddLine(aLine);
	myParent->SetValue<CollisionBoxComponent*>("CollisionBoxComponent", this);
}

CollisionBoxComponent::~CollisionBoxComponent()
{
}

bool CollisionBoxComponent::CheckCollision(const Vector2<float>& aPosition) const
{
	Matrix33<float> localSpace = myParent->GetSpace();


	if (myLineVolume.Inside(aPosition - (myPosition + localSpace.GetPosition())) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionBoxComponent::CheckCollision(const CollisionBoxComponent& aCollisionBox) const
{
	Vector2<float> firstBoxWorldPosition = myPosition * myParent->GetSpace();
	Vector2<float> secondBoxWorldPosition = aCollisionBox.myPosition * aCollisionBox.myParent->GetSpace();

	float firstLeft = firstBoxWorldPosition.x - (myDimensions.x / 2);
	float firstRight = firstBoxWorldPosition.x + (myDimensions.x / 2);
	float firstTop = firstBoxWorldPosition.y - (myDimensions.y / 2);
	float firstBottom = firstBoxWorldPosition.y + (myDimensions.y / 2);

	float secondLeft = secondBoxWorldPosition.x - (aCollisionBox.myDimensions.x / 2);
	float secondRight = secondBoxWorldPosition.x + (aCollisionBox.myDimensions.x / 2);
	float secondTop = secondBoxWorldPosition.y - (aCollisionBox.myDimensions.y / 2);
	float secondBottom = secondBoxWorldPosition.y + (aCollisionBox.myDimensions.y / 2);

	if (firstLeft < secondRight)
	{
		if (firstRight > secondLeft)
		{
			if (firstTop < secondBottom)
			{
				if (firstBottom > secondTop)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CollisionBoxComponent::CheckCollision(const CircleStruct& aCircle) const
{
	return CU::Intersection::CircleInsideBox(myLineVolume, myParent->GetPosition(), aCircle.myPosition, aCircle.myRadius);
}

void CollisionBoxComponent::Update()
{

}

bool CollisionBoxComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	return true;
}



void CollisionBoxComponent::SetData()
{
	myParent->SetValue<CollisionBoxComponent*>("CollisionBoxComponent", this);
}

void CollisionBoxComponent::Destroy()
{
	myLineVolume.RemoveAllLines();
}