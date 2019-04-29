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

	this->openMenu(DirectX::XMFLOAT2(350.0f, 100.0f));

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
			DWRITE_FONT_WEIGHT_REGULAR,
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
	if (SUCCEEDED(hr))
	{
		//Create Geometries
		this->g_MsgBox.pos = DirectX::XMFLOAT2(50.0f, 50.0f);
		this->g_MsgBox.size = DirectX::XMFLOAT2(200.0f, 150.0f);
		this->g_MsgBox.padding = 5.0f;
		this->g_MsgBox.setRect();

		hr = m_pDirect2dFactory->CreateRectangleGeometry(
			this->g_MsgBox.getRect(),//D2D1::RectF(this->g_MsgBox.pos.x, this->g_MsgBox.pos.y, this->g_MsgBox.pos.x + this->g_MsgBox.size.x, this->g_MsgBox.pos.y + this->g_MsgBox.size.y),
			&this->g_MsgBox.p_rectGeom
		);

		// Create Menu default box
		this->g_Menu.boxStyle.pos = DirectX::XMFLOAT2(0.0f, 0.0f);
		this->g_Menu.boxStyle.size = DirectX::XMFLOAT2(200.0f, 150.0f);
		this->g_Menu.boxStyle.padding = 5.0f;
		this->g_Menu.boxStyle.setRect();
		

		// Set the default position for the menu, can be changed later 
		this->g_Menu.pos = DirectX::XMFLOAT2(200.0f, 200.0f);
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
		
		//Create the colorBrushes
		this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &this->pTextColor);
		this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::BlueViolet), &this->g_MsgBox.p_colorBrush);

		this->m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &this->g_Menu.boxStyle.p_colorBrush);
	}

	return hr;
}

void D2D::DiscardDeviceResources()
{
	SafeRelease(&this->m_pRenderTarget);;
	SafeRelease(&this->m_pTextFormat);
	SafeRelease(&this->pTextColor);
}

void D2D::openMenu(DirectX::XMFLOAT2 centerPos)
{
	this->g_Menu.v_Box.clear();
	this->g_Menu.v_renderBox.clear();


	for (size_t i = 0; i < 3; i++)
	{
		this->g_Menu.boxStyle.pos = DirectX::XMFLOAT2(centerPos.x  + (i * this->g_Menu.boxStyle.size.x), centerPos.y);
		this->g_Menu.boxStyle.setRect();

		m_pDirect2dFactory->CreateRectangleGeometry(
			this->g_Menu.boxStyle.getRect(),
			&this->g_Menu.boxStyle.p_rectGeom
		);

		this->g_Menu.v_Box.push_back(this->g_Menu.boxStyle);
		this->g_Menu.v_renderBox.push_back(true);
	}




}

void D2D::checkFPS()
{
	this->frames++;

	this->newFrame = clock();
	
	// If the time is more than 1000ms
	if ((this->newFrame - this->lastDisplay) > 1000)
	{
		//Sets the amount of ms between frames
		this->frametime = this->newFrame - this->lastFrame;
		//Sets thet displayed FPS
		this->fps = this->frames;

		//Reset for next second
		this->frames = 0;
		this->lastDisplay = this->newFrame;
	}

	this->lastFrame = this->newFrame;
}

HRESULT D2D::OnRender()
{
	HRESULT hr = S_OK;

	//hr = CreateDeviceResources();
	
	if (SUCCEEDED(hr))
	{
		this->m_pRenderTarget->BeginDraw();
		
		// Background, will be a overlay of the screen if not alpha = 0.0f
		this->m_pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));

		//this->checkFPS();

		std::wstring text = L"FPS: ";

		//Create our string
		std::wostringstream printString;
		printString << text << Locator::getTime()->GETfps() << L"\nFrametime: " << Locator::getTime()->GETFrameTime() << L"\n" << this->msgText;
		printText = printString.str();
		
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

		FLOAT width = static_cast<FLOAT>(rtSize.width);
		FLOAT height = static_cast<FLOAT>(rtSize.height);

		D2D1_RECT_F targetSq = D2D1::RectF(0, 0, width, height);

		this->m_pRenderTarget->DrawGeometry(this->g_MsgBox.p_rectGeom, this->g_MsgBox.p_colorBrush);
		this->m_pRenderTarget->FillGeometry(this->g_MsgBox.p_rectGeom, this->g_MsgBox.p_colorBrush);



		for (size_t i = 0; i < this->g_Menu.v_Box.size(); i++)
		{
			if (this->g_Menu.v_renderBox.at(i))
			{
				this->m_pRenderTarget->DrawGeometry(this->g_Menu.v_Box.at(i).p_rectGeom, this->g_Menu.v_Box.at(i).p_colorBrush);
				this->m_pRenderTarget->FillGeometry(this->g_Menu.v_Box.at(i).p_rectGeom, this->g_Menu.v_Box.at(i).p_colorBrush);
			}
		}

		//Draw the Text
		this->m_pRenderTarget->DrawText(
			printText.c_str(),
			wcslen(printText.c_str()),
			this->m_pTextFormat,
			this->g_MsgBox.getRect(),
			this->pTextColor
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
	SafeRelease(&this->pTextColor);
	// Image factory
	//SafeRelease(&this->pIWICFactory);
	// Background-screenshot
	this->closeMenu();
}

void D2D::setBackbuffer(ID3D11Texture2D * pBB)
{
	this->r_pBackBuffer = pBB;
}
