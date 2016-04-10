#include "stdafx.h"
#include "SwordBehaviour.h"
#include "PollingStation.h"
#include "ComponentEnums.h"

#define ACTIVATION_RANGE 1000.f


SwordBehaviour::SwordBehaviour()
{
}


SwordBehaviour::~SwordBehaviour()
{
}


BehaviourStruct SwordBehaviour::GetBehaviour(const ActorInfo& someActorInfo)
{
	BehaviourStruct toReturn;
	toReturn.myMoveDirection = eDirections::NONE;

	if (myPreparingSwing == true)
	{
		float deltaTime = CU::EventManager::GetInstance()->GetDeltaTime();
		myPrepareTimer -= deltaTime;
		if(myPrepareTimer <=0)
		{
			toReturn.mySwingSword = true;
			myPreparingSwing = false;
			return toReturn;
		}
		return toReturn;
	}
	toReturn.myShouldWalk = true;

	Vector2<float> playerPosition = PollingStation::GetInstance()->GetValue<const Matrix33<float>*>("PlayerPosition")->GetPosition();
	if (Length(someActorInfo.myPosition - playerPosition) < ACTIVATION_RANGE)
	{
		Vector2<float> deltaVector = playerPosition - someActorInfo.myPosition;

		if (abs(deltaVector.x) > abs(deltaVector.y))
		{
			if (deltaVector.x >= 0)
			{
				toReturn.myMoveDirection = eDirections::RIGHT;
			}
			else
			{
				toReturn.myMoveDirection = eDirections::LEFT;
			}
		}
		else
		{
			if (deltaVector.y >= 0)
			{
				toReturn.myMoveDirection = eDirections::DOWN;
			}
			else
			{
				toReturn.myMoveDirection = eDirections::UP;
			}
		}
	}
	float weaponRange = (someActorInfo.mySwordReach * someActorInfo.mySwordReach) + (someActorInfo.mySwordReach * someActorInfo.mySwordReach) + (someActorInfo.mySwordReach * someActorInfo.mySwordReach);
	if (Length2(someActorInfo.myPosition - playerPosition) < weaponRange)
	{
		myPrepareTimer = 0.3f;
		myPreparingSwing = true;
	}
	return toReturn;
}