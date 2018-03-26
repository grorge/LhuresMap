#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>

#include "RenderData.h"
//class RenderData;

using namespace DirectX;

class Object
{
public:
	Object();
	~Object();

	void renderObj();

	ID3D11Buffer** GETvertexBuffer() {return &triVertBuff;};
	RenderData GETRenderData() { return this->rndData; };
private:
	ID3D11Buffer* triVertBuff;
	ID3D11InputLayout* vertLayout;
	size_t stride = 0;
	size_t offset = 0;
	size_t numIndices = 0;


	RenderData rndData;
};



#endif // !OBJECT_H
