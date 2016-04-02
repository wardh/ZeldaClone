#include "stdafx.h"
#include "WalkTowardsPlayer.h"
#include "PollingStation.h"
#include "ComponentEnums.h"

#define ACTIVATION_RANGE 1000.f

WalkTowardsPlayer::WalkTowardsPlayer()
{
}


WalkTowardsPlayer::~WalkTowardsPlayer()
{
}


BehaviourStruct WalkTowardsPlayer::GetBehaviour(const ActorInfo& someActorInfo)
{
	BehaviourStruct toReturn;
	toReturn.myMoveDirection = eDirections::NONE;
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

	return toReturn;
}