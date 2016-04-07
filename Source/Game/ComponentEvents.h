#pragma once
#include "../Common Utilities/Event.h"
#include "../Common Utilities/Vector.h"
#include "ComponentEnums.h"

class CollisionComponent;
class CollisionBoxComponent;

class ActorDirectionEvent : public CU::Event
{
public:
	ActorDirectionEvent() { myEventType = CU::eEvent::ACTOR_DIRECTION; };
	eDirections myDirection;
};

class BlinkSpriteEvent : public CU::Event
{
public:
	BlinkSpriteEvent() { myEventType = CU::eEvent::BLINK_MODEL; };
	float myDuration;
};
class DamageEvent : public CU::Event
{
public:
	DamageEvent() { myEventType = CU::eEvent::TAKE_DAMAGE; };
	float myDamageAmount;
	Vector2<float> myPosition;
};
class HealEvent : public CU::Event
{
public:
	HealEvent() { myEventType = CU::eEvent::HEAL; };
	float myHealAmount;
};
class AnimationEvent : public CU::Event
{
public:
	AnimationEvent() { myEventType = CU::eEvent::CHANGE_ANIMATION; };
	eDirections myDirection;
	eAnimationTypes myAnimationType;
};

class AddDamageVelocity : public CU::Event
{
public:
	AddDamageVelocity() { myEventType = CU::eEvent::ADD_DAMAGE_VELOCITY; };
	Vector2<float> myPosition;
};

class CollisionBoxEvent : public CU::Event
{
public:
	CollisionBoxEvent() { myEventType = CU::eEvent::COLLISION_BOX_COMPONENT; };
	CollisionBoxComponent* myCollisionBoxComponent;
};

class SpawnDamageCircle : public CU::Event
{
public:
	SpawnDamageCircle() { myEventType = CU::eEvent::SPAWN_DAMAGE_CIRCLE; };
	Vector2<float> myPosition;
	float myRadius;
	int myDamageAmount;
};

class ExperienceEvent : public CU::Event
{
public:
	ExperienceEvent() { myEventType = CU::eEvent::GIVE_PLAYER_EXPERIENCE; };
	int myXPAmount;
};

class LockMovementComponentEvent : public CU::Event
{
public:
	LockMovementComponentEvent() { myEventType = CU::eEvent::LOCK_MOVEMENT_COMPONENT; };
	float myTime;
};

class TriggerExit : public CU::Event
{
public:
	TriggerExit() { myEventType = CU::eEvent::TRIGGER_EXIT; };
};

class ChangeLevelEvent : public CU::Event
{
public:
	ChangeLevelEvent() { myEventType = CU::eEvent::CHANGE_LEVEL; };
	std::string myMapName;
	Vector2<float> myPosition;
};