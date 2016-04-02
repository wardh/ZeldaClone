#include "StackWalker.h"

#pragma once
class MemoryStackWalker : public BaseStackWalker
{
public:
	MemoryStackWalker();
	~MemoryStackWalker();
	MemoryStackWalker(unsigned int aProcessId, HANDLE aProcess);
	virtual void OnOutput(char* aString) override;
};


