#include "Common Utilities_Precompiled.h"
#include "RenderCommandInstance.h"

namespace CommonUtilities
{
	RenderCommandInstance::RenderCommandInstance()
	{
		myModel = nullptr;
		myDebugColor = {-1, -1, -1, -1};
	}

	RenderCommandInstance::RenderCommandInstance(GraphicsEngine::Instance* aModel, const Matrix44f& anOrientation, const Matrix44f& aLastFrameOrientation, const Vector4f& aDebugColor, GraphicsEngine::Texture* aTexture, const bool anAffectedByFow)
	{
		myDebugColor = aDebugColor;
		myModel = aModel;
		myOrientation = anOrientation;
		myLastFrameOrientation = aLastFrameOrientation;
		myTexture = aTexture;
		myAffectedByFow = anAffectedByFow;
	}

	RenderCommandInstance::~RenderCommandInstance()
	{

	}
}