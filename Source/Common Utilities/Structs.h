#pragma once
#include "GrowingArray.h"
#include "TriggerEnums.h"
#include "EventEnums.h"
#include <string>
#include "Event.h"	
#include "PoolPointer.h"
#include "CUString.h"
#include "EnumKeys.h"
#include "EventEnums.h"
#include <functional>
#include "Matrix.h"
#include "RayStruct.h"

namespace ComponentSystem
{
	enum class eUnitState;
	enum class eFaction;
	enum class eUnitType;
}
class GameObject;

enum class eControlCommands;

namespace CS = ComponentSystem;

namespace CommonUtilities
{
	struct EventStruct
	{
		eToolEvents myEventType;
		float myTimeDelay;
		std::string myFirstStringArgument;
		std::string mySecondStringArgument;
		bool myFlag;
	};

	struct ConditionStruct
	{
		CU::eCondition myConditionType;
		std::string myStringArgument;
		bool myWhenTrue;
	};



	struct TriggerStruct
	{
		CU::eTrigger myTriggerType;
		bool myIsOneTimeTrigger;
		CU::GrowingArray <EventStruct> myEventStructs;
		CU::GrowingArray <ConditionStruct> myConditionStructs;

		inline TriggerStruct();
	};

	struct VersionStruct
	{
		inline VersionStruct();
		inline VersionStruct(const int aMajor, const int aPatch, const int aMinor);
		inline bool operator>=(const VersionStruct& aVersion);
		int myMajor;
		int myPatch;
		int myMinor;
	};

	VersionStruct::VersionStruct()
	{
		myMajor = 0;
		myMinor = 0;
		myPatch = 0;
	}

	VersionStruct::VersionStruct(const int aMajor, const int aPatch, const int aMinor)
	{
		myMajor = aMajor;
		myPatch = aPatch;
		myMinor = aMinor;
	}

	bool VersionStruct::operator>=(const VersionStruct& aVersion)
	{
		if (myMajor > aVersion.myMajor)
		{
			return true;
		}
		else if (myMajor == aVersion.myMajor)
		{
			if (myPatch > aVersion.myPatch)
			{
				return true;
			}
			else if (myPatch == aVersion.myPatch)
			{
				if (myMinor >= aVersion.myMinor)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}


	}

	TriggerStruct::TriggerStruct()
	{
		myIsOneTimeTrigger = true;
		myEventStructs.Init(4);
		myConditionStructs.Init(4);
	}

	class MultiEvent : public Event
	{
	public:
		GrowingArray<PoolPointer<Event>> myPoolpointers;
	};

	class FunctionEvent : public Event
	{
	public:
		std::function<void()> myFunction;
	};

	class SetFlagEvent : public Event
	{
	public:
		CU::String<128> myFlagName;
		bool mySetFlagTo;
	};

	class TimedEvent : public Event
	{
	public:
		float myTimeLeft;
		GrowingArray<PoolPointer<Event>> myPoolpointers;
		std::function<void()> myFunction;
	};

	class StartSceneEvent : public Event
	{
	public:
		CU::String<128> mySceneName;
	};

	class PlayerInputEnabledEvent : public Event
	{
	public:
		bool myIsEnabled;
	};



	class UnitMoveCommandEvent : public Event
	{
	public:
		Vector3<float> myPosition;
	};

	class ModifyDeltaTimeEvent : public Event
	{
	public:
		float myModifier;
	};

	class LoadingEvent : public Event
	{
	public:
		bool myIsLoading;
	};

	class KeyboardInputEvent : public Event
	{
	public:
		eKeyboardKeys myKeyboardKey;
		eKeyState myKeyState;
	};

	class PlaySubtitleEvent : public Event
	{
	public:
		CU::String<128> mySubtitle;
	};

	class LoadSubtitleEvent : public Event
	{
	public:
		CU::String<128> mySubtitle;
	};

	class VibrateControllerEvent : public Event
	{
	public:
		unsigned short myPlayernumber;
		float myLowFrequencyMotorStrength;
		float myHighFrequencyMotorStrength;
		float myTimeToVibrate;
	};

	class MouseMoveEvent : public Event
	{
	public:
		Vector2f myMovement;
	};

	class CommandInputEvent : public Event
	{
	public:
		Vector2f myMovement;
		eControlCommands myCommand;
		eKeyState myKeyState;
	};

	class MouseScrollEvent : public Event
	{
	public:
		float myScrollValue;
	};

	class MouseInputEvent : public Event
	{
	public:
		Vector2f myMousePosition;
		eMouseButtons myMouseButton;
		eKeyState myKeyState;
	};

	class ControllerButtonInputEvent : public Event
	{
	public:
		eXboxControllerButtons myButton;
		eKeyState myKeyState;
	};

	class ControllerAnalogueInputEvent : public Event
	{
	public:
		eXboxAnalogue myAnalogue;
		Vector2f myNormalizedValue;
	};



	class KeyboardStateEvent : public Event
	{
	public:
		char* myKeyboardState;
	};

	



}

namespace CU = CommonUtilities;
