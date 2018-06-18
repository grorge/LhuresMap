#include "D2D.h"

HRESULT D2D::Initialize(IDXGISurface1 *sSurface10)
{
	HRESULT hr;

	this->closeMenu();

	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	//if (true)
	{
		this->CreateDeviceIndependentResources();

		this->CreateDeviceResources(sSurface10);
	}


	return E_NOTIMPL;
}

HRESULT D2D::CreateDeviceIndependentResources()
{
	// Will load a default font if the font is not installed on the PC
	static const WCHAR msc_fontName[] = L"Verdana"; // Verdana, Rockwell, Agency FB
	static const FLOAT msc_fontSize = 20;
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	//hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->m_pDirect2dFactory);
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void**)&this->m_pDirect2dFactory);

	//Setup text
	if (SUCCEEDED(hr))
	{

		// Create a DirectWrite factory.
		//hr = DWriteCreateFactory(
		//	DWRITE_FACTORY_TYPE_SHARED,
		//	__uuidof(this->m_pDirectWriteFactory),
		//	reinterpret_cast<IUnknown **>(&this->m_pDirectWriteFactory)
		//);
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown **>(&this->m_pDirectWriteFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = this->m_pDirectWriteFactory->CreateTextFormat(
			L"Script", //msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"en-us", //L"", //locale
			&this->m_pTextFormat
		);

	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		this->m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

		this->m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	if (SUCCEEDED(hr))
	{
		// Create the WICFactory for image proccesing.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			(LPVOID*)&this->pIWICFactory
		);
	}

	return hr;
}

HRESULT D2D::CreateDeviceResources(IDXGISurface1 *sSurface10)
{
	HRESULT hr = S_OK;

	if (!this->m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(Locator::getD3D()->GEThwnd(), &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		this->m_pDirect2dFactory->CreateDxgiSurfaceRenderTarget(
			sSurface10,
			D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_HARDWARE,
				D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
			&this->m_pRenderTarget
		);


		// Old
		//hr = this->m_pDirect2dFactory->CreateHwndRenderTarget(
		//	D2D1::RenderTargetProperties(
		//		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		//		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_IGNORE)),
		//	D2D1::HwndRenderTargetProperties(Locator::getD3D()->GEThwnd(), size),
		//	&this->m_pRenderTarget
		//);

		//Create the colorBrush for the grid in the background
		this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->pGridColor);
	}

	return hr;
}

void D2D::DiscardDeviceResources()
{
	SafeRelease(&this->m_pRenderTarget);;
	SafeRelease(&this->m_pTextFormat);
	SafeRelease(&this->pGridColor);
}

HRESULT D2D::OnRender()
{
	HRESULT hr = S_OK;

	//hr = CreateDeviceResources();
	
	if (SUCCEEDED(hr))
	{
		this->m_pRenderTarget->BeginDraw();

		//this->m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		this->m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkRed));

		
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		FLOAT width = static_cast<FLOAT>(rtSize.width);
		FLOAT height = static_cast<FLOAT>(rtSize.height);

		D2D1_RECT_F targetSq = D2D1::RectF(0, 0, width, height);
		////Background picture
		//if (this->pBitmap)
		//{
		//	this->m_pRenderTarget->DrawBitmap(this->pBitmap,
		//		D2D1::RectF(
		//			0,
		//			0,
		//			width,
		//			height
		//		)
		//	);
		//}

		// Draw a grid background.

		//for (int x = 0; x < width; x += 5)
		//{
		//	m_pRenderTarget->DrawLine(
		//		D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
		//		D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
		//		this->pGridColor,
		//		2.5f
		//	);
		//}

		//for (int y = 0; y < height; y += 5)
		//{
		//	m_pRenderTarget->DrawLine(
		//		D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
		//		D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
		//		this->pGridColor,
		//		2.5f
		//	);
		//}

		std::wstring text = L"hej";

		//Create our string
		std::wostringstream printString;
		printString << text;
		printText = printString.str();

		//Draw the Text
		this->m_pRenderTarget->DrawText(
			printText.c_str(),
			wcslen(printText.c_str()),
			this->m_pTextFormat,
			targetSq,
			this->pGridColor
		);







		hr = m_pRenderTarget->EndDraw();
	}

	// If something went wrong in EndDraw() it will discard it and redraw
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
}

void D2D::closeMenu()
{
		//SafeRelease(&this->pIWICFactory);
		SafeRelease(&this->pBitmap);
	
		//Removes the screenshot from the directory
		DeleteFile("include/screenSaved.bmp");
}

void D2D::cleanUp()
{
	// D2D device
	SafeRelease(&this->m_pDirect2dFactory);
	// Render target, dose all calls to render
	SafeRelease(&this->m_pRenderTarget);
	// D2D device for text
	SafeRelease(&this->m_pDirectWriteFactory);
	// Holds formating for text, ea Font
	SafeRelease(&this->m_pTextFormat);
	//Background
	SafeRelease(&this->pGridColor);
	// Image factory
	SafeRelease(&this->pIWICFactory);
	// Background-screenshot
	this->closeMenu();
}

void D2D::setBackbuffer(ID3D11Texture2D * pBB)
{
	this->r_pBackBuffer = pBB;
}
