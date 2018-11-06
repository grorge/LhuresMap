#pragma once
#ifndef RENDERDATA_H
#define RENDERDATA_H

#include <DirectXMath.h>

using namespace DirectX;
struct Vertex    //Overloaded Vertex Structure
{
	Vertex() {}
	Vertex(float x, float y, float z, 
		float u, float v)
		: pos(x, y, z), texCoord(u, v){}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
};

struct objectBuff
{
	objectBuff() {};
	objectBuff(XMFLOAT4X4 wvp) : WVP(wvp) {};

	XMFLOAT4X4 WVP;
	XMFLOAT4X4 world;
};

struct lightBuff
{
	lightBuff() {};
	lightBuff(XMFLOAT4 color) : color(color) {};

	XMFLOAT3 pos;
	XMFLOAT4 color;
	int fill0;
};

struct rndModeBuff
{
	rndModeBuff() {};

	int mode;
	int fill0;
	int fill1;
	int fill2;
};

struct RenderData
{
	ID3D11Buffer* vertBuffer;
	size_t stride;
	ID3D11Buffer* indexBuffer;
	size_t numbIndices;
	objectBuff objBuffData;
	ID3D11ShaderResourceView* texSRV;
	bool transparent;

	RenderData() {}
	RenderData(RenderData* rnd) 
	{
		this->indexBuffer = rnd->indexBuffer;
		this->vertBuffer = rnd->vertBuffer;
		this->objBuffData = rnd->objBuffData;
		this->texSRV = rnd->texSRV;
		this->transparent = rnd->transparent;
		this->stride = rnd->stride;
		this->numbIndices = rnd->numbIndices;
	}
	//RenderData(Vertex* v) : vertexes(v)  {}
	//RenderData(Vertex* v, DirectX::XMFLOAT4 c) : vertexes(v), color(c)  {}
	~RenderData()
	{
		vertBuffer->Release();
		indexBuffer->Release();
		texSRV->Release();
	}
};

#endif // !RENDERDATA_H



