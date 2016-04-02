#pragma once
#include <tga2d/Engine.h>
#include "GameWorld.h"

#include "../Common Utilities/InputWrapper.h"

class CGame
{
public:
	CGame();
	~CGame();
	void Init(const std::wstring& aVersion = L"");
private:
	void InitCallBack();
	void UpdateCallBack();
	void LogCallback(std::string aText);

	void UpdateInput();
	void HandleInput();
	void HandleKeyboard();
	void HandleMouse();

	CGameWorld myGameWorld;

	CU::InputWrapper* myInputWrapper;
};
