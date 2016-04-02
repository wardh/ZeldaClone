#include "stdafx.h"
#include "Synchronizer.h"


#define BUFFERSIZE 8192

Synchronizer::Synchronizer() : myFirstBuffer(BUFFERSIZE), mySecondBuffer(BUFFERSIZE)
{
	myUsingFirstBuffer = true;
	myRenderDone = false;
	myLogicDone = false;
}

Synchronizer::~Synchronizer()
{
}

void Synchronizer::WaitForRenderer(volatile bool& aIsRunning)
{
	myLogicDone = true;

	while (myRenderDone == false && aIsRunning == true)
	{
	}

	myRenderDone = false;

	while (myLogicDone == true && aIsRunning == true)
	{
	}
}

void Synchronizer::WaitForLogic(volatile bool& aIsRunning)
{
	myRenderDone = true;

	while (myLogicDone == false && aIsRunning == true)
	{
	}

	SwapRenderBuffer();

	myLogicDone = false;
}