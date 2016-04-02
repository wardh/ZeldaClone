#pragma once

enum class eDirections;

struct BehaviourStruct
{
	eDirections myMoveDirection;
	bool myShouldWalk;
};

struct ActorInfo
{
	Vector2<float> myPosition;
};

class Behaviour
{
public:
	Behaviour();
	~Behaviour();

	virtual BehaviourStruct GetBehaviour(const ActorInfo& someActorInfo) = 0;
};

