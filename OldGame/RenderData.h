#pragma once
#ifndef RENDERDATA_H
#define RENDERDATA_H

#include <DirectXMath.h>

using namespace DirectX;
struct Vertex    //Overloaded Vertex Structure
{
	Vertex() {}
	Vertex(float x, float y, float z, 
		XMFLOAT4 c)
		: pos(x, y, z), color(c){}

	XMFLOAT3 pos;
	XMFLOAT4 color;
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


	RenderData() {}
	//RenderData(Vertex* v) : vertexes(v)  {}
	//RenderData(Vertex* v, DirectX::XMFLOAT4 c) : vertexes(v), color(c)  {}
};

#endif // !RENDERDATA_H



