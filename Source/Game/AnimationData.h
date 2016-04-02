#pragma once
#include <string>
#include "../Common Utilities/Vector2.h"
#include "ComponentEnums.h"
struct AnimationInitData
{
	eAnimationTypes myType;
	eDirections myDirection;
	Vector2<float> myRectSize;
	Vector2<float> mySheetSize;

	float myFrameTime;
	int myNumberOfFrames;
	std::string myPath = "";
};

struct AnimationData
{
	Vector2<float> myRectSize;
	int myNumberOfFrames;
	int myCurrentFrame = 0;
	float myFrameTime;
	float myCurrentFrameTime = 0;
	bool myLoop = true;
	bool myIsActive = false;
};