#include "Common Utilities_Precompiled.h"
#include "SceneRenderCommands.h"


namespace CommonUtilities
{
	SceneRenderCommands::SceneRenderCommands()
	{
		myFontRenderCommands.Init(4);
		myLineRenderCommands.Init(4);
		myRenderCommandInstances.Init(4);
		mySceneData = nullptr;
	}

	SceneRenderCommands::~SceneRenderCommands()
	{
	}

	void SceneRenderCommands::AddSceneRenderCommands(const SceneRenderCommands& someCommands)
	{
		myFontRenderCommands.Add(someCommands.myFontRenderCommands);
		myLineRenderCommands.Add(someCommands.myLineRenderCommands);
		myRenderCommandInstances.Add(someCommands.myRenderCommandInstances);
	}

}