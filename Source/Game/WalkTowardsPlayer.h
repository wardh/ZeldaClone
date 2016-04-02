#pragma once
#include "Behaviour.h"

class WalkTowardsPlayer : public Behaviour
{
public:
	WalkTowardsPlayer();
	~WalkTowardsPlayer();
	virtual BehaviourStruct GetBehaviour(const ActorInfo& someActorInfo) override;

};

