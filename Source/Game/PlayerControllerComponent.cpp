#include "stdafx.h"
#include "PlayerControllerComponent.h"
#include "../Common Utilities/EventManager.h"
#include "../Common Utilities/Event.h"
#include "GameObject.h"
#include "PollingStation.h"
#include "ComponentEnums.h"


#define CHARGE_TIME 1.5f;

PlayerControllerComponent::PlayerControllerComponent(GameObject& aGameObject) : Component(aGameObject)
{
	//ObserveEvent(CU::eEvent::KEYBOARD_INPUT_EVENT, 5);
	ObserveEvent(CU::eEvent::KEYBOARD_INPUT_EVENT, HANDLE_EVENT_FUNCTION(HandleKeyboardEvent));
	PollingStation::GetInstance()->SetValue<const Matrix33<float>*>("PlayerPosition", &myParent->GetSpace());

}


PlayerControllerComponent::~PlayerControllerComponent()
{
}

void PlayerControllerComponent::Update()
{

}


bool PlayerControllerComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	anEvent;
	return true;
}


bool PlayerControllerComponent::HandleKeyboardEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	GET_EVENT_DATA(anEvent, CU::KeyboardInputEvent, keyboardEvent);

	switch (keyboardEvent->myKeyboardKey)
	{
	case eKeyboardKeys::KEY_LEFT:
	{
		CU::Event eventToAdd;
		eventToAdd = CU::Event(CU::eEvent::MOVE_LEFT);
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));
	}
	break;
	case eKeyboardKeys::KEY_RIGHT:
	{
		CU::Event eventToAdd;
		eventToAdd = CU::Event(CU::eEvent::MOVE_RIGHT);
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));

	}

	break;
	case eKeyboardKeys::KEY_UP:
	{
		CU::Event eventToAdd;
		eventToAdd = CU::Event(CU::eEvent::MOVE_UP);
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));

	}
	break;
	case eKeyboardKeys::KEY_DOWN:
	{
		CU::Event eventToAdd;
		eventToAdd = CU::Event(CU::eEvent::MOVE_DOWN);
		myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(eventToAdd));

	}
	break;
	case eKeyboardKeys::KEY_C:
	{
		if (keyboardEvent->myKeyState == eKeyState::PRESSED)
		{
			
			CU::Event attackEvent;
			attackEvent = CU::Event(CU::eEvent::SWING_WEAPON);
			myParent->HandleInternalEvent(CU::EventManager::GetInstance()->CreateInternalEvent(attackEvent));

		}

	}
	}

	return true;

	return true;
}

void PlayerControllerComponent::SetData()
{
	PollingStation::GetInstance()->SetValue<const Matrix33<float>*>("PlayerPosition", &myParent->GetSpace());
}


void PlayerControllerComponent::Destroy()
{
	DetachMe();
}