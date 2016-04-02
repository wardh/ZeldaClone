#pragma once
#include "Component.h"
#include <string>
#include "../Common Utilities/Vector2.h"
#include <tga2d\sprite\sprite.h>
enum class eRenderLayer;
class ModelComponent : public Component
{
public:
	ModelComponent(GameObject& aGameObject);
	ModelComponent(GameObject& aGameObject, const std::string& aPath, eRenderLayer aRenderLayer);
	ModelComponent(GameObject& aGameObject, const std::string& aPath, const Vector2<float>& aSize, const Vector2<float>& aHotSpot, eRenderLayer aRenderLayer);

	~ModelComponent();

	virtual void Update() override;
	bool HandleInternalEvent(const CU::PoolPointer<CU::Event>& anEvent) override;
	virtual void Destroy();

private:
	DX2D::CSprite* mySprite;
	eRenderLayer myRenderLayer;
	bool myIsFlipped;
	float myBlinkDuration;
	float myBlinkTimer;
	bool myShouldRender;
	bool myIsBlinking;
};

