#pragma once
#include "Synchronizer.h"
#include <unordered_map>
#include "../Common Utilities/Matrix.h"
#include "../Common Utilities/Vector.h"
#include "../Common Utilities/GrowingArray.h"

struct RenderCommand;

struct ScreenShakeData
{
	float myMagnitude;
	float myLength;
};

class Camera
{
public:
	static Camera* Create(float aProjectionHeight, float aProjectionWidth, Vector2<float> aPosition);
	static void Destroy();
	static __forceinline Camera* GetInstance();

	void Init(float aProjectionHeight, float aProjectionWidth, Vector2<float> aPosition);



	void Update();

	void Move(const Vector2<float>& aVector);

	void MoveTo(const Vector2<float>& aPosition);

	void SetPosition(const Vector2<float>& aPosition);

	void ZoomOut(float aZoomOutPercentage);
	void ZoomIn(float aZoomInPercentage);

	bool GetScreenPosition(const RenderCommand& aRenderCommand, Vector2<float>& anOutScreenPosition);
	inline Vector2<float> GetPosition() const;

	inline Vector2<float> GetScreenDimensions() const;

private:
	Camera();
	~Camera();

	static Camera* ourInstance;

	void CalculateScreenPos(RenderCommand aRenderCommand);

	void CreateProjectionMatrix(float aProjectionHeight, float aProjectionWidth);

	Matrix33<float> myOrientation;
	Matrix33<float> myInverse;
	Matrix33<float> myProjection;

	Vector2<float> myGoal;

	int myScreenHeight;
	int myScreenWidth;

	float myProjectionHeight;
	float myProjectionWidth;

	int myLevelSize;

	float myCurrentShakeLength;
	float myShakeLength;
	float myShakeMagnitude;
	bool myIsShaking;
	bool myIsMoving;
};

Camera* Camera::GetInstance()
{
	return ourInstance;
}

Vector2<float> Camera::GetScreenDimensions() const
{
	return Vector2<float>(static_cast<float>(myScreenWidth), static_cast<float>(myScreenHeight));
}




Vector2<float> Camera::GetPosition() const
{
	return myOrientation.GetPosition();
}