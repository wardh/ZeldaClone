#pragma once
#include <vector>
#include "AnalogueLog.h"
#include "SingleControllerLog.h"

#define _GROWINGARRAY std::vector

namespace CommonUtilities
{
	struct XboxControllersEventLog
	{
	public:
		XboxControllersEventLog();
		~XboxControllersEventLog();

		_GROWINGARRAY<SingleControllerLog> myControllerLogs;
	};
}

namespace CU = CommonUtilities;