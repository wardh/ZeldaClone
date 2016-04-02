#pragma once
#include "../Common Utilities/Stack.h"
#include "RenderCommand.h"

class Synchronizer
{
public:
	Synchronizer();
	~Synchronizer();

	void WaitForRenderer(volatile bool& aIsRunning);
	void WaitForLogic(volatile bool& aIsRunning);

	inline void SwapRenderBuffer();

	inline CU::Stack<RenderCommand>& GetCurrentRenderBuffer();
	__forceinline void AddRenderCommand(const RenderCommand& aRenderCommand);

	inline void ResetBuffers();

private:
	volatile bool myRenderDone;
	volatile bool myLogicDone;
	
	CU::Stack<RenderCommand> myFirstBuffer;
	CU::Stack<RenderCommand> mySecondBuffer;

	bool myUsingFirstBuffer;
};

void Synchronizer::SwapRenderBuffer()
{
	myUsingFirstBuffer = !myUsingFirstBuffer;
}

CU::Stack<RenderCommand>& Synchronizer::GetCurrentRenderBuffer()
{
	if (myUsingFirstBuffer == true)
	{
		return myFirstBuffer;
	}

	return mySecondBuffer;
}

void Synchronizer::AddRenderCommand(const RenderCommand& aRenderCommand)
{
	if (myUsingFirstBuffer == true)
	{
		mySecondBuffer.Push(aRenderCommand);
	}
	else
	{
		myFirstBuffer.Push(aRenderCommand);
	}
}

void Synchronizer::ResetBuffers()
{
	myFirstBuffer.Clear();
	mySecondBuffer.Clear();
}
