#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#include <d3d11.h>
#include <array>
#include <vector>
#include "Shader.h"
#include "RenderData.h"
#include "Object.h"
#include "CleanupTools.h"

using namespace DirectX;

const int NUM_BACKGROUND_IMAGES = 39;
const int NUM_DEFERRED_OUTPUTS = 3;
const int GEOCOLOR_INPUT_DESC_SIZE = 3;
const int GEOTEX_INPUT_DESC_SIZE = 3;
const int LIGHT_INPUT_DESC_SIZE = 1;

const int NUM_TEXTURES = 1;



enum class SHADERTYPE { COLOR, TEXTURE };

class Renderer
{
private:
	ID3D11RenderTargetView* gFinalRTV = nullptr;
	ID3D11Texture2D* gDSB = nullptr;
	ID3D11DepthStencilView* gDSV = nullptr;
	ID3D11SamplerState* gSampler = nullptr;
	ID3D11Buffer* gQuadVertexBuffer = nullptr;
	D3D11_VIEWPORT viewport;

	size_t vertBufferStride = 0;
	size_t vertBufferOffset = 0;

	//-----SHADERS
	Shader geoColorShaders;
	Shader* currentGeoShaders = nullptr;

	//-----BUFFERS
	ID3D11Buffer * constBuff = nullptr;
	ID3D11Buffer * renderModeBuff = nullptr;
	rndModeBuff rndModeData;
	ID3D11Buffer * lightBuffer = nullptr;
	lightBuff lightData;

	float clearColor[4];

	void initShaders();
	void initBuffers();
	void bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT format);
	void initSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	void createQuad();
	void createViewportAndRasterizer();
	void createBackBufferRTV();
	void createDepthStencilView(/*size_t width, size_t height, ID3D11DepthStencilView** gDSV, ID3D11Texture2D** gDSB*/);
public:
	Renderer() /*: /*gRTVs(), gSRVs()/*, gTextures()*/ {}
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Intializes the clear color
	2. Sets the current shadertype
	3. Creates the backbuffer rendertargetview aka the final rendertargetview
	4. Intializes the shaders
	5. Binds the deferred rendertargetviews with the deferred shaderresourceviews
	6. Creates the Quad data
	7. Initializes the sampler
	8. Creates the viewport
	*/
	void init();
	
	void render(std::vector<Object*> objects);
	void switchRendermode(int mode);

	void firstPass();
	void setShaderType(SHADERTYPE type);
	void cleanUp();
private:
	const wchar_t* fileNameGeoColorVertex = L"geoPassVertColor.hlsl";
	const wchar_t* fileNameGeoColorPixel = L"geoPassPixelColor.hlsl";
};


#endif // !RENDERER_H
