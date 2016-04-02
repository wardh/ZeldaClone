#pragma once

#include "../Common Utilities/Vector2.h"

__forceinline Vector2<float> Lerp(Vector2<float> v0, Vector2<float> v1, float t)
{
	return (v0 * (1 - t)) + (v1 * t);
}

__forceinline float Lerp(float v0, float v1, float t)
{
	return (v0 * (1 - t)) + (v1 * t);
}