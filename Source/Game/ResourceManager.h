#pragma once

#include "../Common Utilities/GrowingArray.h"
#include <map>

class ResourceManager
{
public:

	static ResourceManager* GetInstance();

	DX2D::CSprite* GetSprite(const std::string& aPath);


private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, DX2D::CSprite*> mySprites;
	static ResourceManager* ourInstance;
};

