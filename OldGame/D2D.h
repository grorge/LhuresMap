#pragma once
#ifndef D2D_H
#define D2D_H

#include "ID2D.h"
#include <time.h>

#include "Locator.h"
#include "CleanupTools.h"

class D2D : public ID2D
{
public:
	// Register the window class and call methods for instantiating drawing resources
	virtual HRESULT Initialize(IDXGISurface1 *sSurface10);

	// Draw content.
	virtual HRESULT OnRender();

	virtual ID2D1RenderTarget* GETRenderTarget() { return this->m_pRenderTarget; }
	virtual IDWriteTextFormat* GETTextFormat() { return this->m_pTextFormat; }
	virtual void SETTextFormat(std::wstring input) { this->msgText = input; }
	virtual void closeMenu();
	virtual void cleanUp();
	virtual void setBackbuffer(ID3D11Texture2D* pBB);
private:
	// D3D backbuffer
	ID3D11Texture2D * r_pBackBuffer;

	// D2D device
	ID2D1Factory* m_pDirect2dFactory = nullptr;
	// Render target, dose all calls to render
	ID2D1RenderTarget* m_pRenderTarget = nullptr;
	// D2D device for text
	IDWriteFactory* m_pDirectWriteFactory = nullptr;
	// Holds formating for text, ea Font
	IDWriteTextFormat* m_pTextFormat = nullptr;

	// Initialize device-independent resources. Like factory
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources(IDXGISurface1 *sSurface10);
	
	// Release device-dependent resource.
	void DiscardDeviceResources();

	//Brushes
	ID2D1SolidColorBrush * pTextColor = nullptr;
	ID2D1SolidColorBrush * pMsgBoxColor = nullptr;

	//Geometries
	ID2D1RectangleGeometry* g_pMsgBoxBackground = nullptr;

	IWICImagingFactory *pIWICFactory = nullptr;
	//PCWSTR uri = nullptr;
	UINT destinationWidth;
	UINT destinationHeight;
	ID2D1Bitmap* pBitmap = nullptr;

	// Holds the text that will be printed on the screen
	std::wstring printText;

	// Mesage to be changed during runtime
	std::wstring msgText = L"NaN";

	// FPS counter
	void checkFPS();
	int frames = 0;
	int fps = 0;
	clock_t lastFrame = clock_t();
	clock_t newFrame = clock_t();
	clock_t frametime = clock_t();
	clock_t lastDisplay = clock_t();

};


#endif // !D2D_H