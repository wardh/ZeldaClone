#include "stdafx.h"

#include "Game.h"

#include <tga2d/error/error_manager.h>

#include <functional>
#include <time.h>
#include "../Common Utilities/EventManager.h"
#include "../Common Utilities/IDFactory.h"
#include "../Common Utilities/TimerManager.h"
#include "tga2d\light\light_manager.h"
#include "Camera.h"
#include "Renderer.h"
using namespace std::placeholders;


#ifdef _DEBUG
#pragma comment(lib,"DX2DEngine_Debug.lib")

#endif // DEBUG
#ifdef NDEBUG
#pragma comment(lib,"DX2DEngine_Release.lib")
#endif // DEBUG


CGame::CGame()
{
}


CGame::~CGame()
{
}


void CGame::Init(const std::wstring& aVersion)
{
	unsigned short windowWidth = 1280;
	unsigned short windowHeight = 720;

	CU::IDFactory::Create();
	CU::TimerManager::Create();
	CU::TimerManager::GetInstance()->Update();
	CU::EventManager::Create();
	CU::EventManager::GetInstance()->SetScreenDimensions({ 1280,720 });
	Camera::Create(windowHeight, windowWidth, { 0,0 });
	Renderer::Create();
    DX2D::SEngineCreateParameters createParameters;
	createParameters.myActivateDebugSystems = eDebugFeature_Fps | eDebugFeature_Mem | eDebugFeature_Filewatcher | eDebugFeature_Cpu | eDebugFeature_Drawcalls;
    createParameters.myInitFunctionToCall = std::bind( &CGame::InitCallBack, this );
    createParameters.myUpdateFunctionToCall = std::bind( &CGame::UpdateCallBack, this );
    createParameters.myLogFunction = std::bind( &CGame::LogCallback, this, _1 );
    createParameters.myWindowHeight = windowHeight;
    createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = 1280;
	createParameters.myTargetHeight = 720;
	createParameters.myAutoUpdateViewportWithWindow = false;
    createParameters.myClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );
	
	std::wstring appname = L"TGA 2D RELEASE [" + aVersion + L"]";
#ifdef _DEBUG
	appname = L"TGA 2D DEBUG  [" + aVersion + L"]";
#endif

    createParameters.myApplicationName = appname;
    createParameters.myEnableVSync = false;

    DX2D::CEngine::CreateInstance( createParameters );

    if( !DX2D::CEngine::GetInstance()->Start() )
    {
        ERROR_AUTO_PRINT( "Fatal error! Engine could not start!" );
		system("pause");
    }


}


void CGame::InitCallBack()
{
	myInputWrapper = new CU::InputWrapper();
	myInputWrapper->Init();

    myGameWorld.Init();
}


void CGame::UpdateCallBack()
{
	CU::TimerManager::GetInstance()->Update();
	CU::TimerManager::GetInstance()->UpdateNewFrame();
	const float deltaTime = CU::TimerManager::GetInstance()->GetFrameDeltaTime();
	CU::EventManager::GetInstance()->Update(deltaTime);
	Camera::GetInstance()->Update();
	UpdateInput();
	myGameWorld.Update(deltaTime);
	Renderer::GetInstance()->RenderFrame();
}


void CGame::LogCallback( std::string aText )
{
}


void CGame::UpdateInput()
{
	myInputWrapper->Update();
	HandleInput();
}
void CGame::HandleInput()
{
	HandleMouse();
	HandleKeyboard();
}
void CGame::HandleKeyboard()
{
	CU::GrowingArray<CU::KeyboardEvent> keyboardEvents = myInputWrapper->GetKeyBoardEventLog();

	for (unsigned short i = 0; i < keyboardEvents.Size(); i++)
	{
		CU::KeyboardInputEvent keyEvent;
		keyEvent.SetMyType(CU::eEvent::KEYBOARD_INPUT_EVENT);
		keyEvent.myKeyboardKey = keyboardEvents[i].myKey;
		keyEvent.myKeyState = keyboardEvents[i].myState;

		CU::EventManager::GetInstance()->AddEvent(keyEvent);
	}
}
void CGame::HandleMouse()
{
	CU::GrowingArray<CU::MouseEvent> eventLog = myInputWrapper->GetMouseEventLog();
	CU::GrowingArray<CU::MouseAxisLog> axisLog = myInputWrapper->GetMouseAxisLog();

	CU::MousePosition mousePosition = myInputWrapper->GetAbsoluteMousePosition();

	for (unsigned short i = 0; i < eventLog.Size(); i++)
	{
		CU::MouseInputEvent inputEvent;
		inputEvent.SetMyType(CU::eEvent::MOUSE_INPUT_EVENT);
		inputEvent.myMousePosition = { mousePosition.myX, mousePosition.myY };
		inputEvent.myMouseButton = eventLog[i].myButton;
		inputEvent.myKeyState = eventLog[i].myState;

		CU::EventManager::GetInstance()->AddEvent(inputEvent);
	}

	if (axisLog.Size() > 0)
	{
		float scrollWheel = 0;
		float x = 0;
		float y = 0;
		for (unsigned short i = 0; i < axisLog.Size(); i++)
		{
			switch (axisLog[i].myAxis)
			{
			case X:
				x = static_cast<float>(axisLog[i].myValue);
				break;

			case Y:
				y = static_cast<float>(axisLog[i].myValue);
				break;

			case SCROLL_WHEEL:
				scrollWheel = static_cast<float>(axisLog[i].myValue);
				break;

			default:
				break;
			}
		}

		CU::MouseMoveEvent moveEvent;
		moveEvent.SetMyType(CU::eEvent::MOUSE_MOVE_EVENT);
		moveEvent.myMovement = Vector2f{ x, y };

		CU::EventManager::GetInstance()->AddEvent(moveEvent);


		if (scrollWheel != 0)
		{
			CU::MouseScrollEvent scrollEvent;
			scrollEvent.SetMyType(CU::eEvent::MOUSE_SCROLL_EVENT);

			CU::EventManager::GetInstance()->AddEvent(scrollEvent);
		}
	}

	CU::MouseInputEvent inputEvent;
	inputEvent.SetMyType(CU::eEvent::MOUSE_INPUT_EVENT);
	inputEvent.myMousePosition = { mousePosition.myX, mousePosition.myY };
	inputEvent.myMouseButton = eMouseButtons::NONE;
	inputEvent.myKeyState = eKeyState::NONE;

	CU::EventManager::GetInstance()->AddEvent(inputEvent);
}