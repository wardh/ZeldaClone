#pragma once
#include "../Common Utilities/Vector2.h"
#include "../Common Utilities/Vector4.h"
#include <string>
struct RenderCommandText
{
	Vector2<float> myPosition = { 0.5f, 0.5f };
	Vector4<float> myColor = { 1,1,1,1 };
	std::string myText;
	float mySize = 1;
};