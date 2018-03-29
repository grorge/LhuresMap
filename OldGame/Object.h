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
	Object(Camera* cam, std::wstring texFile);
	~Object();

	//void renderObj();
	virtual void update() = 0;
	void updateWorld();

	virtual RenderData* GETRenderData() { return this->rndData; };

	void SETPosition(XMFLOAT3 input) { this->pos = input; };
	void SETUp(XMFLOAT3 input) { this->up = input; };
	void SETDir(XMFLOAT3 input) { this->dir = input; };
	void addRotation(float rot);
protected:
	XMFLOAT3 pos = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float size = 0.0f;
	XMFLOAT3 up = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 dir = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 rotXYZ = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float rotation = 0.0f;

	virtual void init();
	RenderData* rndData = nullptr;
	void createTextureSRV();
	Camera* cam = nullptr;
private:
	virtual void createVertexData() = 0;
	std::wstring textureFilename;
};



#endif // !OBJECT_H
