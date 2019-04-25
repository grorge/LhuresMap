#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include "Renderer.h"
#include <Windows.h>
#include "Locator.h"


void Renderer::initShaders()
{
	D3D11_INPUT_ELEMENT_DESC shaderInputDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(shaderInputDesc);
	
	this->geoColorShaders.CreateShaders(Locator::getD3D()->GETgDevice(), this->fileNameGeoColorVertex, this->fileNameGeoColorPixel, shaderInputDesc, numElements);

	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Renderer::initBuffers()
{
	// Sends the world and WVP to VS
	Locator::getD3D()->createConstantBuffer(&this->constBuff, sizeof(objectBuff));

	// Sends the rndMode to the PS
	Locator::getD3D()->createConstantBuffer(&this->renderModeBuff, sizeof(rndModeBuff));
	this->switchRendermode(2);

	// Sends lighting pos to PS
	Locator::getD3D()->createConstantBuffer(&this->lightBuffer, sizeof(lightBuff));
	// Position of "the sun" in the program
	this->lightData.pos = {2000.0f, 2000.0f, 0.0f}; 
	this->lightData.color = { 1.0f, 1.0f, 1.0f, 1.0f};
	Locator::getD3D()->mapConstantBuffer(&this->lightBuffer, &this->lightData, sizeof(this->lightData));
	Locator::getD3D()->setConstantBuffer(this->lightBuffer, SHADER::PIXEL, 1, 1);
}

void Renderer::bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT format)
{
	HRESULT hr;

	// Describe the texture
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	texDesc.Format = format;
	texDesc.CPUAccessFlags = 0;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	//texDesc.Width = width;
	//texDesc.Height = height;
	texDesc.MipLevels = 1;
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	// Create one texture per rendertarget
	hr = Locator::getD3D()->GETgDevice()->CreateTexture2D(&texDesc, nullptr, gTexure);
	if (FAILED(hr)) {
		MessageBox(0, "Create texture (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Rendertargetview
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	rtvDesc.Format = format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;

	// Create one rtv per output from the pixel shader
	hr = Locator::getD3D()->GETgDevice()->CreateRenderTargetView(*gTexure, &rtvDesc, gRTV);
	if (FAILED(hr)) {
		MessageBox(0, "Create RTV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Describe the Shaderresourceview
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	// Create one srv per texture to be loaded into the next pixel shader
	hr = Locator::getD3D()->GETgDevice()->CreateShaderResourceView(*gTexure, &srvDesc, gSRV);
	if (FAILED(hr)) {
		MessageBox(0, "Create SRV (RTV and SRV) - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void Renderer::initSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc)
{
	HRESULT hr;

	D3D11_SAMPLER_DESC sampDesc;
	memset(&sampDesc, 0, sizeof(D3D11_SAMPLER_DESC));
	sampDesc.Filter = filter;
	sampDesc.AddressU = texAdressModeU;
	sampDesc.AddressV = texAdressModeV;
	sampDesc.AddressW = texAdressModeW;
	sampDesc.ComparisonFunc = compFunc;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = Locator::getD3D()->GETgDevice()->CreateSamplerState(&sampDesc, gSampler);
	if (FAILED(hr)) {
		MessageBox(0, "Create Samplerstate - Failed", "Error", MB_OK);
		_exit(0);
	}


}

void Renderer::initBlend()
{
	HRESULT hr;

	float initialBlendFactor[4] = { 0.75f, 0.75f, 0.75f, 1.0f };

	this->blendFactor[0] = initialBlendFactor[0];
	this->blendFactor[1] = initialBlendFactor[1];
	this->blendFactor[2] = initialBlendFactor[2];
	this->blendFactor[3] = initialBlendFactor[3];

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	hr = Locator::getD3D()->GETgDevice()->CreateBlendState(&blendDesc, &Locator::getD3D()->GETTransp());


}

void Renderer::createQuad()
{
	HRESULT hr;

	this->guiRndData = new RenderData();

	//Create the vertex buffer
	Vertex2 v[] =
	{
		// Front Face
		Vertex2(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
		Vertex2(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
		Vertex2(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
		Vertex2(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
	};

	DWORD indices[] = {
		// Front Face
		0,  1,  2,
		0,  2,  3,
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = indices;
	Locator::getD3D()->GETgDevice()->CreateBuffer(&indexBufferDesc, &iinitData, &this->guiRndData->indexBuffer);


	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex2) * 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
	hr = Locator::getD3D()->GETgDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &this->guiRndData->vertBuffer);

	//Create A shader resource view from the texture D2D will render to,
	//So we can use it to texture a square which overlays our scene
	Locator::getD3D()->GETgDevice()->CreateShaderResourceView(Locator::getD3D()->GETTexture11(), NULL, &this->guiRndData->texSRV);

	this->guiRndData->stride = sizeof(Vertex2);
}

void Renderer::createViewportAndRasterizer()
{
	// ViewPort
	memset(&this->viewport, 0, sizeof(D3D11_VIEWPORT));

	this->viewport.TopLeftX = 0;
	this->viewport.TopLeftY = 0;
	this->viewport.Width = static_cast<FLOAT>(Locator::getD3D()->GETwWidth());
	this->viewport.Height = static_cast<FLOAT>(Locator::getD3D()->GETwHeight());
	this->viewport.MinDepth = 0.0f;
	this->viewport.MaxDepth = 1.0f;

	// RasterizerState
	D3D11_RASTERIZER_DESC rasterStateDesc;
	memset(&rasterStateDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
	
	rasterStateDesc.FillMode = D3D11_FILL_SOLID;
	rasterStateDesc.CullMode = D3D11_CULL_NONE;

	Locator::getD3D()->setRasterizerDesc(rasterStateDesc);
}

void Renderer::createBackBufferRTV()
{
	HRESULT hr;

	// Describe the Buffer
	DXGI_MODE_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = (UINT)Locator::getD3D()->GETwWidth();
	bufferDesc.Height = (UINT)Locator::getD3D()->GETwHeight();
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Create the BackBuffer
	ID3D11Texture2D* BackBuffer;
	hr = Locator::getD3D()->GETswapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	if (FAILED(hr)) {
		MessageBox(0, "Swapchain backbuffer - Failed", "Error", MB_OK);
		_exit(0);
	}

	// Create the Render Target
	hr = Locator::getD3D()->GETgDevice()->CreateRenderTargetView(BackBuffer, nullptr, &this->gFinalRTV);
	if (FAILED(hr)) {
		MessageBox(0, "Create Render Target View - Failed", "Error", MB_OK);
		_exit(0);
	}
	//BackBuffer->Release();
}

void Renderer::createDepthStencilView(/*size_t width, size_t height, ID3D11DepthStencilView ** gDSV, ID3D11Texture2D ** gDSB*/)
{
	HRESULT hr;

	// Describe the Depth/Stencil Buffer
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	memset(&depthStencilDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));


	// somethign is wrong here but hardcoding the value after changing ti works
	depthStencilDesc.Width = 1184;//(UINT)Locator::getD3D()->GETwWidth();
	depthStencilDesc.Height = 761; //(UINT)Locator::getD3D()->GETwHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	// Creates the Depth/Stencil View
	hr = Locator::getD3D()->GETgDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &this->gDSB);
	if (FAILED(hr)) {
		MessageBox(0, "Create Depth Texture - Failed", "Error", MB_OK);
		_exit(0);
	}

	hr = Locator::getD3D()->GETgDevice()->CreateDepthStencilView(this->gDSB, nullptr, &this->gDSV);
	if (FAILED(hr)) {
		MessageBox(0, "Create Depth Stencil - Failed", "Error", MB_OK);
		_exit(0);
	}
}

void Renderer::init()
{
	// Set the clear color
	this->clearColor[0] = 0.3f;
	this->clearColor[1] = 0.0f;
	this->clearColor[2] = 0.3f;
	this->clearColor[3] = 255.0f;

	this->createBackBufferRTV();
	this->createDepthStencilView();
	Locator::getD3D()->GETgDevCon()->OMSetRenderTargets(1, &this->gFinalRTV, this->gDSV);
		
	this->initShaders();
	this->geoColorShaders.SetShaders(Locator::getD3D()->GETgDevCon());
	
	this->initBuffers();

	this->initSampler(&this->gSampler, D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_COMPARISON_NEVER);

	this->initBlend();

	this->createViewportAndRasterizer();

	Locator::getD3D()->GETgDevCon()->RSSetViewports(1, &this->viewport);

	this->createQuad();
}

void Renderer::render(std::vector<Object*> objects)
{


	size_t offset = 0;
	for (auto i : objects)
	{		
		// Checks if the object will be rendered then it renders.
		if (i->okToRender)
		{
			RenderData* rndData = i->GETRenderData();

			Locator::getD3D()->mapConstantBuffer(&this->constBuff, &rndData->objBuffData, sizeof(rndData->objBuffData));
			Locator::getD3D()->setConstantBuffer(this->constBuff, SHADER::VERTEX, 0, 1);

			Locator::getD3D()->setIndexBuffer(rndData->indexBuffer, 0);
			Locator::getD3D()->setVertexBuffer(&rndData->vertBuffer, rndData->stride, offset);
		
			Locator::getD3D()->GETgDevCon()->PSSetShaderResources(0, 1, &rndData->texSRV);
			Locator::getD3D()->GETgDevCon()->PSSetSamplers(0, 1, &this->gSampler);

			Locator::getD3D()->blendedDraw(rndData->numbIndices); 
		}
	}

}

void Renderer::startRender()
{
	// Clear everything and will be the background that everything will be renderd on
	Locator::getD3D()->GETgDevCon()->ClearRenderTargetView(this->gFinalRTV, this->clearColor);
	Locator::getD3D()->GETgDevCon()->ClearDepthStencilView(this->gDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Set the default blend state (no blending) for opaque objects
	Locator::getD3D()->GETgDevCon()->OMSetBlendState(0, 0, 0xffffffff);

}

void Renderer::startTrans()
{
	//Sets all nextcomming objects for a transparent
	Locator::getD3D()->GETgDevCon()->OMSetBlendState(Locator::getD3D()->GETTransp(), blendFactor, 0xffffffff);
}

void Renderer::stopRender()
{
	this->drawD2D();

	Locator::getD3D()->GETswapChain()->Present(0, 0);
}

void Renderer::switchRendermode(int mode)
{
	this->rndModeData.mode = mode;
	Locator::getD3D()->mapConstantBuffer(&this->renderModeBuff, &this->rndModeData, sizeof(this->rndModeData));
	Locator::getD3D()->setConstantBuffer(this->renderModeBuff, SHADER::PIXEL, 0, 1);
}

void Renderer::drawD2D()
{
	// Sets up for D2D rendering
	Locator::getD3D()->prepD2D();
	// All the rendering in D2D
	Locator::getD2D()->OnRender();
	Locator::getD3D()->deprepD2D();

	// Sets the rendermode so it will not change the color
	int savedMode = this->rndModeData.mode;
	this->switchRendermode(-1);

	//Draw the quad over the screen with the D2D as a texture
	Locator::getD3D()->mapConstantBuffer(&this->constBuff, &this->guiRndData->objBuffData, sizeof(this->guiRndData->objBuffData));
	Locator::getD3D()->setConstantBuffer(this->constBuff, SHADER::VERTEX, 0, 1);

	size_t offset = 0;

	Locator::getD3D()->setIndexBuffer(this->guiRndData->indexBuffer, 0);
	Locator::getD3D()->setVertexBuffer(&this->guiRndData->vertBuffer, this->guiRndData->stride, offset);
	
	XMMATRIX WVP = XMMatrixIdentity();
	WVP = XMMatrixTranspose(WVP);
	XMStoreFloat4x4(&this->guiRndData->objBuffData.WVP, WVP);
	XMStoreFloat4x4(&this->guiRndData->objBuffData.world, WVP);
	//Locator::getD3D()->GETgDevCon()->UpdateSubresource(this->constBuff, 0, NULL, &this->guiRndData->objBuffData, 0, 0);
	Locator::getD3D()->GETgDevCon()->VSSetConstantBuffers(0, 1, &this->constBuff);

	Locator::getD3D()->GETgDevCon()->PSSetShaderResources(0, 1, &this->guiRndData->texSRV);
	Locator::getD3D()->GETgDevCon()->PSSetSamplers(0, 1, &this->gSampler);
	Locator::getD3D()->clockDraw(6);

	this->switchRendermode(savedMode);

}

void Renderer::firstPass()
{

}

void Renderer::setShaderType(SHADERTYPE type)
{
	this->currentGeoShaders = &this->geoColorShaders;
}

void Renderer::cleanUp()
{	
	this->gFinalRTV->Release();
	this->gDSV->Release();
	this->gDSB->Release();
	this->gSampler->Release();
	this->geoColorShaders.Release();

	this->constBuff->Release();
	SafeRelease(&this->renderModeBuff);
}