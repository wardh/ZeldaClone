#pragma once
#include "Matrix.h"
#include "GrowingArray.h"
#include "PoolPointer.h"
#include <memory>
#include <string>

#include "../Common Utilities/Dictionary.h"

namespace GraphicsEngine
{
	class Model;
	class Camera;
	class Light;
	class Texture;
	class Instance;
}

namespace CommonUtilities
{
	struct RenderCommandInstance
	{
	public:
		RenderCommandInstance(GraphicsEngine::Instance* anInstance, const Matrix44f& anOrientation , const Matrix44f& aLastFrameOrientation, const Vector4f& aDebugColor = { -1, -1, -1, -1 }, GraphicsEngine::Texture* aTexture = nullptr, const bool anAffectedByFow = false);
		RenderCommandInstance();
		~RenderCommandInstance();

		Matrix44f myOrientation;
		Matrix44f myLastFrameOrientation;
		Vector4f myDebugColor;
		GraphicsEngine::Texture* myTexture;
		GraphicsEngine::Instance* myModel;
		bool myAffectedByFow;
	};

}

namespace CU = CommonUtilities;


