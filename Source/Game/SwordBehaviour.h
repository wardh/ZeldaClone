#pragma once
#include "Behaviour.h"
class SwordBehaviour : public Behaviour
{
public:
	SwordBehaviour();
	~SwordBehaviour();
	virtual BehaviourStruct GetBehaviour(const ActorInfo& someActorInfo) override;

	bool myPreparingSwing;
	float myPrepareTimer;
};

