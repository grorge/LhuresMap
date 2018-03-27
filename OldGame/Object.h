#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>

#include "RenderData.h"

struct objectBuff
{
	objectBuff() {};
	objectBuff(XMFLOAT4X4 wvp) : WVP(wvp) {};

	XMFLOAT4X4 WVP;
	
	//XMFLOAT4X4 cam;
};

using namespace DirectX;

class Object
{
public:
	Object();
	~Object();

	void renderObj();

	RenderData GETRenderData() { return this->rndData; };
private:
	ID3D11Buffer * vertBuff;
	ID3D11Buffer * indiceBuff;
	ID3D11Buffer * constBuff;

	size_t stride = 0;
	size_t offset = 0;
	size_t numIndices = 0;

	void createVertexData();
	void createconstBuffData();
	RenderData rndData;
};



#endif // !OBJECT_H
