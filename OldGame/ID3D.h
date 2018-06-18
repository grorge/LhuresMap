#pragma once
#ifndef ID3D_H
#define ID3D_H

#include <d3d11.h>
#include <D3D10_1.h>
#include <DirectXMath.h>
#include <DXGI.h>
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D3D10_1.lib")

enum class SHADER { VERTEX, PIXEL };

class ID3D
{
public:
	virtual void initializeWindow(HINSTANCE hInstance, int ShowWnd, int width, int height, bool windowed) = 0;
	virtual void createSwapChain() = 0;
	virtual void createVertexBuffer(ID3D11Buffer** gVertexBuffer, void* v, size_t& stride, size_t& offset, size_t numVertices) = 0;
	virtual void createIndexBuffer(ID3D11Buffer** gIndexBuffer, DWORD* data, size_t& numIndices) = 0;
	virtual void setVertexBuffer(ID3D11Buffer** gVertexBuffer, size_t& stride, size_t& offset) = 0;
	virtual void setIndexBuffer(ID3D11Buffer* gIndexBuffer, size_t offset) = 0;
	virtual void createConstantBuffer(ID3D11Buffer ** gBuffer, int bufferSize) = 0;
	virtual void mapConstantBuffer(ID3D11Buffer** gBuffer, void* cbPtr, int structSize) = 0;
	virtual void setConstantBuffer(ID3D11Buffer *& cBuffer, SHADER shader, size_t slot, size_t numBuffers) = 0;
	virtual void setRasterizerDesc(D3D11_RASTERIZER_DESC restDesc) = 0;
	virtual void cleanup() = 0;

	virtual size_t& GETwWidth() = 0;
	virtual size_t& GETwHeight() = 0;
	virtual HWND& GEThwnd() = 0;
	virtual ID3D11Device*& GETgDevice() = 0;
	virtual ID3D11DeviceContext*& GETgDevCon() = 0;
	virtual IDXGISwapChain*& GETswapChain() = 0;
	virtual ID3D11BlendState*& GETTransp() = 0;

	//Blending
	virtual void blendedDraw(size_t numbInd) = 0;
	virtual void clockDraw(size_t numbInd) = 0;


	// D2D interactions
	virtual IDXGISurface1*& GETsurface10() = 0;
	virtual ID3D11Texture2D*& GETTexture11() = 0;
	virtual void prepD2D() = 0;
	virtual void deprepD2D() = 0;
};


#endif // !D3D_H
