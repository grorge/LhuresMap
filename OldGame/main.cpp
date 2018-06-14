#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include "D3D.h"
#include "D2D.h"
#include <DirectXMath.h>

using namespace DirectX;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtMemState s1;
	_CrtMemCheckpoint(&s1);
	//	_CrtSetBreakAlloc(6114);
#endif

	ID3D* d3d = new D3D();
	ID2D* d2d = new D2D();

	Locator::provide(d3d);
	Locator::provide(d2d);

	Locator::getD3D()->initializeWindow(hInstance, true, 1200, 800, true);
	Locator::getD3D()->createSwapChain();

	Locator::getD2D()->Initialize(Locator::getD3D()->GETsurface10());
	
	GameManager gm;
	// Initialize the game
	gm.init(hInstance, nCmdShow);
	double deltaTime = 0.0;
	double timeLastFrame = 0.0;
	int frames = 0;
	char msgbuf[20];
	
	// Game loop
	while (gm.getIsRunning()) {
		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();

		//if (timeLastFrame > 1000.0) {
		//	sprintf_s(msgbuf, "FPS: %d\n", frames);
		//	
		//	OutputDebugStringA(msgbuf);
		//}

	}

	//d2d->cleanUp();
	gm.cleanUp();
	d3d->cleanup();
	delete d3d;

#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	_CrtMemDumpAllObjectsSince(&s1);
#endif
	return 0;
}
