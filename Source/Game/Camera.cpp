#include "stdafx.h"
#include "Camera.h"
#include "Lerp.h"

#include "../Common Utilities/EventManager.h"
Camera* Camera::ourInstance = nullptr;

Camera::Camera()
{
	myCurrentShakeLength = 0;
	myShakeLength = 0;
	myShakeMagnitude = 0;
	myIsShaking = false;
	myIsMoving = false;
}

Camera::~Camera()
{
}

Camera* Camera::Create(float aProjectionHeight, float aProjectionWidth, Vector2<float> aPosition)
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Camera;
		ourInstance->Init(aProjectionHeight, aProjectionWidth, aPosition);
	}
	else
	{
		assert(false && "trying to create more than one camera");
	}

	return ourInstance;
}

void Camera::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;
}

void Camera::Init(float aProjectionHeight, float aProjectionWidth, Vector2<float> aPosition)
{
	myScreenHeight = static_cast<int>(aProjectionHeight);
	myScreenWidth = static_cast<int>(aProjectionWidth);

	CreateProjectionMatrix(aProjectionHeight, aProjectionWidth);

	myOrientation.myMatrix[6] = aPosition.x;
	myOrientation.myMatrix[7] = aPosition.y;

}

void Camera::CalculateScreenPos(RenderCommand aRenderCommand)
{
	aRenderCommand;
	//Vector2<float> textPos;
	//bool isInside = false;
	//
	///*for (int i = 0; i < 4; i++)
	//{
	//	Vector2<float> vertexPos({ quad.v[i].x, quad.v[i].y });

	//	vertexPos = vertexPos * aRenderCommand.mySpace;
	//	vertexPos = (vertexPos * myInverse) * myProjection;

	//	if (vertexPos.x <= 1.f && vertexPos.x >= -1.f && vertexPos.y <= 1.f && vertexPos.y >= -1.f)
	//	{
	//		isInside = true;
	//	}

	//	vertexPos.x += 1;
	//	vertexPos.y += 1;
	//	vertexPos.x /= 2;
	//	vertexPos.y /= 2;

	//	vertexPos.x *= myScreenWidth;
	//	vertexPos.y *= myScreenHeight;

	//	quad.v[i].x = vertexPos.x;
	//	quad.v[i].y = vertexPos.y;
	//	textPos = vertexPos;
	//}*/
	//Vector2<float> position = aRenderCommand.mySpace.GetPosition();
	//position = (position * myInverse) * myProjection;
	//if (position.x <= 1.1f && position.x >= -1.1f && position.y <= 1.1f && position.y >= -1.1f)
	//{
	//	isInside = true;
	//}

	//position.x += 1;
	//position.y += 1;
	//position.x /= 2;
	//position.y /= 2;

	//position.x *= myScreenWidth;
	//position.y *= myScreenHeight;

	//
	//textPos = position;
	//if (isInside == true)
	//{
	//	aRenderCommand.mySpace.SetPosition(Vector2<float>(static_cast<int>(position.x), static_cast<int>(position.y)));
	//	if (aRenderCommand.myFont != nullptr)
	//	{
	//		aRenderCommand.mySpace.SetPosition(textPos);
	//	}
	//	mySynchroniser->AddRenderCommand(aRenderCommand);
	//}
}

bool Camera::GetScreenPosition(const RenderCommand& aRenderCommand, Vector2<float>& anOutScreenPosition)
{
	bool isInside = false;

	Vector2<float> position = aRenderCommand.mySpace.GetPosition();
	position = (position * myInverse) * myProjection;
	if (position.x <= 1.1f && position.x >= -1.1f && position.y <= 1.1f && position.y >= -1.1f)
	{
		isInside = true;
	}

	position.x += 1;
	position.y += 1;
	position.x /= 2;
	position.y /= 2;

	/*position.x *= myScreenWidth;
	position.y *= myScreenHeight;*/

	if (isInside == true)
	{
		anOutScreenPosition = position;
		return true;
	/*	aRenderCommand.mySpace.SetPosition(Vector2<float>(static_cast<int>(position.x), static_cast<int>(position.y)));
		if (aRenderCommand.myFont != nullptr)
		{
			aRenderCommand.mySpace.SetPosition(textPos);
		}
		mySynchroniser->AddRenderCommand(aRenderCommand);*/
	}
	return false;
}

void Camera::Move(const Vector2<float>& aVector)
{
	myOrientation.SetPosition(myOrientation.GetPosition() + aVector);
}

void Camera::ZoomOut(float aZoomOutPercentage)
{
	aZoomOutPercentage += 1.f;

	CreateProjectionMatrix(myProjectionHeight * aZoomOutPercentage, myProjectionWidth * aZoomOutPercentage);
}

void Camera::ZoomIn(float aZoomInPercentage)
{
	aZoomInPercentage = 1.f - aZoomInPercentage;

	CreateProjectionMatrix(myProjectionHeight * aZoomInPercentage, myProjectionWidth * aZoomInPercentage);
}

void Camera::Update()
{
	myInverse = Matrix33<float>::GetInverse(myOrientation);
	float deltaTime = CU::EventManager::GetInstance()->GetDeltaTime();

	if (myIsMoving == true)
	{
		if (deltaTime * 2 > 1.f)
		{
			deltaTime = 1.f;
		}
		Vector2<float> currentPos = myOrientation.GetPosition();
		Vector2<float> newPos = Lerp(currentPos, myGoal, deltaTime * 2);

		myOrientation.SetPosition(newPos);

		if (Length(myGoal - newPos) < 15)
		{
			myIsMoving = false;
		}
	}
}

void Camera::CreateProjectionMatrix(float aProjectionHeight, float aProjectionWidth)
{
	if (aProjectionHeight < myScreenHeight)
	{
		aProjectionHeight = static_cast<float>(myScreenHeight);
	}
	if (aProjectionHeight > 1450.f)
	{
		aProjectionHeight = myProjectionHeight;
		aProjectionWidth = myProjectionWidth;
	}
	if (aProjectionWidth < myScreenWidth)
	{
		aProjectionWidth = static_cast<float>(myScreenWidth);
	}
	myProjection.myMatrix[0] = 2 / aProjectionWidth;
	myProjection.myMatrix[4] = 2 / aProjectionHeight;

	myProjectionHeight = aProjectionHeight;
	myProjectionWidth = aProjectionWidth;
}


void Camera::MoveTo(const Vector2<float>& aPosition)
{
	myIsMoving = true;
	myGoal = aPosition;
}

void Camera::SetPosition(const Vector2<float>& aPosition)
{
	myOrientation.SetPosition(aPosition);
}