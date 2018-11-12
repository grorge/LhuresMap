#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include "Camera.h"	

#include "RenderData.h"
#include "ModelLoader.h"


using namespace DirectX;

class Object
{
public:
	Object(Camera* cam, std::wstring texFile);
	void setID(int id) { this->id = id; };
	int getID() { return this->id; };
	~Object();

	virtual void update() = 0;
	void updateWorld();
	bool okToRender = 0;

	//Change render data
	virtual RenderData* GETRenderData() { return this->rndData; };

	//Morph
	void SETSizeFloat(float input) { this->size = XMFLOAT3(input, input, input);	};
	void SETSizeFloat3(XMFLOAT3 input) { this->size = input; };

	//Move
	void SETPosition(XMFLOAT3 input) { this->pos = input; };
	void SETPositionY(float input) { this->pos.y = input; };

	//Rotatoion
	void SETUp(XMFLOAT3 input) { this->up = input; };
	void SETDir(XMFLOAT3 input) { this->dir = input; };
	void rotateX(float rot);
	void rotateY(float rot);
	void rotateZ(float rot);
protected:
	XMFLOAT3 pos = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 size = XMFLOAT3(1.000001f, 1.000001f, 1.000001f);
	XMFLOAT3 up = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 dir = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 rotXYZ = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float rotation = 0.0f;

	virtual void init();
	RenderData* rndData = nullptr;
	void createTextureSRV();
	Camera* cam = nullptr;
private:
	int id;
	virtual void createVertexData() = 0;
	std::wstring textureFilename;
};



#endif // !OBJECT_H
