#pragma once
#include "RenderCommand.h"
#include "RenderCommandText.h"
#include "RenderLayers.h"
#include "tga2d\text\text.h"

class Camera;

class Renderer
{
public:
	static void Create();
	static Renderer* GetInstance();

	void AddRenderCommand(const RenderCommand& aRenderCommand, eRenderLayer aLayer = eRenderLayer::BOTTOM);
	void AddRenderCommandText(const RenderCommandText& aRenderCommand);
	void RenderFrame();
private:
	Renderer();
	~Renderer();

	void Init();
	void CleanUp();

	CU::StaticArray<CU::GrowingArray<RenderCommand>, static_cast<int>(eRenderLayer::MAX_SIZE)> myRenderCommands;
	CU::GrowingArray<RenderCommandText> myRenderCommandTexts;
	Vector2<int> myScreenDimensions;
	
	DX2D::CText* myFont;

	Camera* myCamera;

	static Renderer* ourInstance;
};

