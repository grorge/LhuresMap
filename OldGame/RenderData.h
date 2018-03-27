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
//D3D11_INPUT_ELEMENT_DESC shaderInputDesc[] =
//{
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};
//UINT numElements = ARRAYSIZE(shaderInputDesc);

struct RenderData
{
	ID3D11Buffer* vertBuffer;
	Vertex* vertexes;
	//DirectX::XMFLOAT4 color;

	RenderData() {}
	RenderData(Vertex* v) : vertexes(v)  {}
	//RenderData(Vertex* v, DirectX::XMFLOAT4 c) : vertexes(v), color(c)  {}
};

#endif // !RENDERDATA_H



