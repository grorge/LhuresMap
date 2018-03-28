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
	Object(Camera* cam, XMFLOAT4 color);
	~Object();

	void renderObj();
	void update();

	RenderData* GETRenderData() { return this->rndData; };

	void SETPosition(XMFLOAT3 input);
	void SETUp(XMFLOAT3 input);
	void SETDir(XMFLOAT3 input);
	void addRotation(float rot);
protected:
	XMFLOAT3 pos = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float size = 0.0f;
	XMFLOAT3 up = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 dir = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 rotXYZ = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float rotation = 0.0f;
private:
	ID3D11Buffer * vertBuff = nullptr;
	ID3D11Buffer * indiceBuff = nullptr;

	ID3D11ShaderResourceView* texture;
	//objectBuff objBuffer;

	size_t stride = 0;
	size_t offset = 0;
	size_t numIndices = 0;

	void createVertexData();
	void createTextureSRV();
	RenderData* rndData = nullptr;
	Camera* cam = nullptr;
	XMFLOAT4 color = XMFLOAT4();
};



#endif // !OBJECT_H
