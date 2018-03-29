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
};

struct objectBuff
{
	objectBuff() {};
	objectBuff(XMFLOAT4X4 wvp) : WVP(wvp) {};

	XMFLOAT4X4 WVP;
	XMFLOAT4X4 world;

	//XMFLOAT4X4 cam;
};


struct RenderData
{
	ID3D11Buffer* vertBuffer;
	size_t stride;
	ID3D11Buffer* indexBuffer;
	size_t numbIndices;
	objectBuff objBuffData;
	//Vertex* vertexes;
	//DirectX::XMFLOAT4 color;
	ID3D11ShaderResourceView* texSRV;

	RenderData() {}
	//RenderData(Vertex* v) : vertexes(v)  {}
	//RenderData(Vertex* v, DirectX::XMFLOAT4 c) : vertexes(v), color(c)  {}
};

#endif // !RENDERDATA_H



