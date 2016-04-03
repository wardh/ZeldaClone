#include "stdafx.h"
#include "Renderer.h"
#include "tga2d\sprite\sprite.h"
#include "Camera.h"


#define RENDERCOMMAND_BUFFER_SIZE 4096
Renderer* Renderer::ourInstance = nullptr;

void Renderer::Create()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new Renderer();
		ourInstance->Init();
	}
}

Renderer * Renderer::GetInstance()
{
	return ourInstance;
}

void Renderer::AddRenderCommand(const RenderCommand & aRenderCommand, eRenderLayer aLayer)
{
	if (aLayer != eRenderLayer::ACTORS)
	{
		myRenderCommands[static_cast<int>(aLayer)].Add(aRenderCommand);
		return;
	}
	if (myRenderCommands[static_cast<int>(aLayer)].Size() == 0)
	{
		myRenderCommands[static_cast<int>(aLayer)].Add(aRenderCommand);
		return;
	}
	for (unsigned short i = 0; i < myRenderCommands[static_cast<int>(aLayer)].Size(); i++)
	{
		if (aRenderCommand.mySpace.GetTranslation().y < myRenderCommands[static_cast<int>(aLayer)][i].mySpace.GetTranslation().y)
		{
			myRenderCommands[static_cast<int>(aLayer)].Insert(i, aRenderCommand);
			return;
		}
	}
	myRenderCommands[static_cast<int>(aLayer)].Add(aRenderCommand);
}

void Renderer::AddRenderCommandText(const RenderCommandText & aRenderCommand)
{
	myRenderCommandTexts.Add(aRenderCommand);
}

void Renderer::RenderFrame()
{
	for (unsigned short i = 0; i < static_cast<int>(eRenderLayer::MAX_SIZE); i++)
	{
		DX2D::CSprite* sprite;
		Matrix33f space;
		Vector2<float> cameraPosition;
		for (unsigned short rc = 0; rc < myRenderCommands[i].Size(); rc++)
		{
			if (static_cast<eRenderLayer>(i) != eRenderLayer::GUI)
			{
				if (myCamera->GetScreenPosition(myRenderCommands[i][rc], cameraPosition) == true)
				{
					space = myRenderCommands[i][rc].mySpace;
					float rotation = atan2f(space.GetRow(1).x, space.GetRow(1).y);
					sprite = myRenderCommands[i][rc].mySprite;
					sprite->SetPosition({ cameraPosition.x,cameraPosition.y });
					sprite->SetRotation(rotation);
					sprite->Render();
				}
			}
			else
			{
				space = myRenderCommands[i][rc].mySpace;
				float rotation = atan2f(space.GetRow(1).x, space.GetRow(1).y);
				sprite = myRenderCommands[i][rc].mySprite;
				sprite->SetPosition({space.GetPosition().x, space.GetPosition().y});
				sprite->SetRotation(rotation);
				sprite->Render();
			}
		}
	}

	for (unsigned short i = 0; i < myRenderCommandTexts.Size(); i++)
	{
		myFont->myPosition = { myRenderCommandTexts[i].myPosition.x,myRenderCommandTexts[i].myPosition.y };
		myFont->myColor = { myRenderCommandTexts[i].myColor.x, myRenderCommandTexts[i].myColor.y, myRenderCommandTexts[i].myColor.z, myRenderCommandTexts[i].myColor.w };
		myFont->myText = myRenderCommandTexts[i].myText;
		myFont->mySize = myRenderCommandTexts[i].mySize;
		myFont->Render();
	}

	CleanUp();
}

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	myRenderCommandTexts.Init(128);
	for (unsigned short i = 0; i < static_cast<int>(eRenderLayer::MAX_SIZE); i++)
	{
		myRenderCommands[i].Init(RENDERCOMMAND_BUFFER_SIZE);
	}
	myScreenDimensions = CU::EventManager::GetInstance()->GetScreenDimensions();
	myCamera = Camera::GetInstance();

	myFont = new DX2D::CText("Text/8bit16.ttf_sdf");
}

void Renderer::CleanUp()
{
	for (unsigned short i = 0; i < static_cast<int>(eRenderLayer::MAX_SIZE); i++)
	{
		myRenderCommands[i].RemoveAll();
	}
	myRenderCommandTexts.RemoveAll();
}
