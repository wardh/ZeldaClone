#include "stdafx.h"
#include "PollingStation.h"


PollingStation* PollingStation::ourInstance = nullptr;


PollingStation::PollingStation()
{
}


PollingStation::~PollingStation()
{
}

PollingStation* PollingStation::GetInstance()
{
	if (ourInstance == nullptr)
	{
		ourInstance = new PollingStation();
	}
	return ourInstance;
}
