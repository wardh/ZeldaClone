#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager* ResourceManager::ourInstance = nullptr;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new ResourceManager();
	}
	return ourInstance;
}
DX2D::CSprite * ResourceManager::GetSprite(const std::string & aPath)
{
	if (mySprites.find(aPath) == mySprites.end())
	{
		DX2D::CSprite* sprite = new DX2D::CSprite(aPath.c_str());
		//mySprite = new DX2D::CSprite("Data/Gfx/Characters/hero.png");

		sprite->SetPivot({ 0.5f, 0.5f });
		mySprites[aPath] = sprite;
		return mySprites[aPath];
	}
	else
	{
		return mySprites[aPath];
	}
}
//
//SpriteHGE* ResourceManager::GetSprite(const std::string& aPath, const Vector2<float>& aSize, const Vector2<float>& aHotSpot)
//{
//	if (mySprites.find(aPath) == mySprites.end())
//	{
//		SpriteHGE sprite;
//		sprite.Init(aSize, aHotSpot, aPath);
//		mySprites[aPath] = sprite;
//		return &mySprites[aPath];
//	}
//	else
//	{
//		return &mySprites[aPath];
//	}
//}
