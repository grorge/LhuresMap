#pragma once
#ifndef ID2D_H
#define ID2D_H

#include <vector>
#include <d2d1.h>
#include <d2d1helper.h>
#include <Dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite")
#pragma comment(lib, "Windowscodecs")

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class ID2D
{
public:
	// Register the window class and call methods for instantiating drawing resources
	virtual HRESULT Initialize() = 0;

	// Draw content.
	//virtual HRESULT OnRender(std::vector<MenuObject*> objects) = 0;

	virtual ID2D1HwndRenderTarget* GETRenderTarget() = 0;
	virtual IDWriteTextFormat* GETTextFormat() = 0;
	
	// Takes a screenshot of the screen to be used as background
	virtual void saveScreen() = 0;
	// Clears the screenshot
	virtual void closeMenu() = 0;
	// Cleans memory
	virtual void cleanUp() = 0;
};


#endif // !ID2D_H