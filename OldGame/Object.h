#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include "Camera.h"	

#include "RenderData.h"



using namespace DirectX;

class Object
{
public:
	Object(Camera* cam);
	~Object();

	void renderObj();
	void update();

	RenderData* GETRenderData() { return this->rndData; };
protected:
	XMFLOAT3 pos;
	float size;
	XMFLOAT3 up;
	XMFLOAT3 dir;
	float rotation;
private:
	ID3D11Buffer * vertBuff;
	ID3D11Buffer * indiceBuff;

	//objectBuff objBuffer;

	size_t stride = 0;
	size_t offset = 0;
	size_t numIndices = 0;

	void createVertexData();
	void createconstBuffData();
	RenderData* rndData;
	Camera* cam;
};



#endif // !OBJECT_H
