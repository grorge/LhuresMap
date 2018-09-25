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


enum  class RENDERMODE {
	TEXTURE, NORMALS, LIGHTDIST, LIGHTNORMAL, // -1 = GUI - used for exceptiongs
	SIZE
};

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
	// Buffer to hold light-data
	ID3D11Buffer * lightBuffer = nullptr;
	// Struct of light-data
	lightBuff lightData;
	// Makes the square that will have D2D rendered to it
	RenderData* guiRndData;


	void drawD2D();

	float clearColor[4];
	//"fine-tune" the blending equation
	float blendFactor[4];


	void initShaders();
	void initBuffers();
	void bindTextureToRTVAndSRV(ID3D11Texture2D** gTexure, ID3D11RenderTargetView** gRTV, ID3D11ShaderResourceView** gSRV, int width, int height, DXGI_FORMAT format);
	void initSampler(ID3D11SamplerState** gSampler, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE texAdressModeU, D3D11_TEXTURE_ADDRESS_MODE texAdressModeV, D3D11_TEXTURE_ADDRESS_MODE texAdressModeW, D3D11_COMPARISON_FUNC compFunc);
	void initBlend();
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
