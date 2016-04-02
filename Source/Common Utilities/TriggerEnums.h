#pragma once

namespace CommonUtilities
{
	enum class eTrigger
	{
		ON_COLLISION,
		ON_CLICK,
		ON_HOVER,
		ON_DEATH,
		MAX_SIZE
	};

	enum class eCondition
	{
		TAG,
		FLAG,
		MAX_SIZE
	};
}

namespace CU = CommonUtilities;