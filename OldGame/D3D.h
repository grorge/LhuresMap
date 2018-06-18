#pragma once
#ifndef D3D_H
#define D3D_H

#include "ID3D.h"

struct Vertex2
{
	float x, y, z, w;
};

class D3D : public ID3D
{
private:
	IDXGISwapChain* gSwapChain = nullptr;
	ID3D11Device* gDevice = nullptr;
	ID3D11DeviceContext* gDevCon = nullptr;
	HWND hwnd;
	size_t wWidth = 0;
	size_t wHeight = 0;

	ID3D11RasterizerState* gRastState = nullptr;

	//Blending
	ID3D11BlendState* Transparency;
	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;

	// For D2D rendering
	void createD2Drendering(IDXGIAdapter1 *Adapter);
	ID3D10Device1 *d3d101Device;
	IDXGIKeyedMutex *keyedMutex11;
	IDXGIKeyedMutex *keyedMutex10;
	ID3D11Texture2D *BackBuffer11;
	ID3D11Texture2D *sharedTex11;

	// -to be sent to D2D
	IDXGISurface1 *sharedSurface;
public:
	virtual void initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed);
	virtual void createSwapChain();
	virtual void createVertexBuffer(ID3D11Buffer** gVertexBuffer, void* v, size_t& stride, size_t& offset, size_t numVertices);
	virtual void createIndexBuffer(ID3D11Buffer** gIndexBuffer, DWORD* data, size_t& numIndices);
	virtual void setVertexBuffer(ID3D11Buffer** gVertexBuffer, size_t& stride, size_t& offset);
	virtual void setIndexBuffer(ID3D11Buffer* gIndexBuffer, size_t offset);
	virtual void createConstantBuffer(ID3D11Buffer ** gBuffer, int bufferSize);
	virtual void mapConstantBuffer(ID3D11Buffer** gBuffer, void* cbPtr, int structSize);
	virtual void setConstantBuffer(ID3D11Buffer *& cBuffer, SHADER shader, size_t slot, size_t numBuffers);
	virtual void setRasterizerDesc(D3D11_RASTERIZER_DESC restDesc);
	virtual void cleanup();

	virtual size_t& GETwWidth();
	virtual size_t& GETwHeight();
	virtual HWND& GEThwnd();
	virtual ID3D11Device*& GETgDevice();
	virtual ID3D11DeviceContext*& GETgDevCon();
	virtual IDXGISwapChain*& GETswapChain();
	virtual ID3D11BlendState*& GETTransp();

	virtual void blendedDraw(size_t numbInd);
	virtual void clockDraw(size_t numbInd);

	virtual IDXGISurface1*& GETsurface10();
	virtual ID3D11Texture2D*& GETTexture11();
	virtual void prepD2D();
	virtual void deprepD2D();
};


#endif // !D3D_H
