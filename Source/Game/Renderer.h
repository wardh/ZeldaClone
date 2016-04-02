#pragma once
#include "RenderCommand.h"
#include "RenderLayers.h"

class Camera;

class Renderer
{
public:
	static void Create();
	static Renderer* GetInstance();

	void AddRenderCommand(const RenderCommand& aRenderCommand, eRenderLayer aLayer = eRenderLayer::BOTTOM);
	void RenderFrame();
private:
	Renderer();
	~Renderer();

	void Init();
	void CleanUp();

	CU::StaticArray<CU::GrowingArray<RenderCommand>, static_cast<int>(eRenderLayer::MAX_SIZE)> myRenderCommands;
	Vector2<int> myScreenDimensions;
	
	Camera* myCamera;

	static Renderer* ourInstance;
};

