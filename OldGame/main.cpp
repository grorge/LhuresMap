#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include "GameManager.h"
#include "Locator.h"
#include "D3D.h"
#include "D2D.h"
#include "Time.h"
#include "ModelLoader.h"
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
	ITime* time = new Time();
	IModelLoader* mod = new ModelLoader();

	Locator::provide(d3d);
	Locator::provide(d2d);
	Locator::provide(time);
	Locator::provide(mod);

	Locator::getD3D()->initializeWindow(hInstance, true, 1200, 800, true);
	Locator::getD3D()->createSwapChain();

	Locator::getD2D()->Initialize(Locator::getD3D()->GETsurface10());
	
	GameManager gm;
	// Initialize the game
	gm.init(hInstance, nCmdShow);
		
	// Sets screen to fullscreen, Also lowers FPS by 60%
	//Locator::getD3D()->GETswapChain()->SetFullscreenState(true, nullptr);

	// Game loop
	while (gm.getIsRunning()) {

		// Update the timer
		Locator::getTime()->cycle();

		// Handle events & update & render
		gm.handleEvents();
		gm.update();
		gm.render();
	}

	//d2d->cleanUp();
	gm.cleanUp();
	d3d->cleanup();
	d2d->cleanUp();
	delete d3d;
	delete d2d;
	delete time;

#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	_CrtMemDumpAllObjectsSince(&s1);
#endif
	return 0;
}
