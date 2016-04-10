#pragma once

enum class eDirections;

struct BehaviourStruct
{
	eDirections myMoveDirection;
	bool myShouldWalk;
	bool mySwingSword = false;
};

struct ActorInfo
{
	Vector2<float> myPosition;
	float mySwordReach;
};

class Behaviour
{
public:
	Behaviour();
	~Behaviour();

	virtual BehaviourStruct GetBehaviour(const ActorInfo& someActorInfo) = 0;
};

