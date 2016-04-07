#include "stdafx.h"
#include "ExitComponent.h"





ExitComponent::ExitComponent(GameObject & aGameObject, const Vector2<float>& aPosition, const std::string & aMapName) : Component(aGameObject)
{
	myTargetPosition = aPosition;
	myTargetMapName = aMapName;
}

ExitComponent::~ExitComponent()
{
}

void ExitComponent::Update()
{
}

bool ExitComponent::HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent)
{
	switch (anEvent->GetMyType())
	{
	case CU::eEvent::TRIGGER_EXIT:
	{
		ChangeLevelEvent levelEvent;
		levelEvent.myMapName = myTargetMapName;
		levelEvent.myPosition = myTargetPosition;
		CU::EventManager::GetInstance()->AddEvent(levelEvent);
	}
		break;
	default:
		break;
	}
	return true;
}

void ExitComponent::Destroy()
{
}

void ExitComponent::SetData()
{
}
