#include "Object.h"
#include "Locator.h"
#include <array>

Object::Object(Camera* cam)
{
	this->cam = cam;

	this->createVertexData();
	//this->createconstBuffData();

}

Object::~Object()
{
}

void Object::renderObj()
{
	//Locator::getD3D()->mapConstantBuffer(&this->constBuff, &this->objBuffer, sizeof(objBuffer));

	//Locator::getD3D()->setVertexBuffer(&this->vertBuff, this->stride, this->offset);
	//Locator::getD3D()->setIndexBuffer(this->indiceBuff, this->offset);
}

void Object::update()
{

	XMMATRIX WVP = XMMatrixIdentity() * XMLoadFloat4x4(&cam->GETviewMatrix()) * XMLoadFloat4x4(&cam->GETprojMatrix());
	WVP = XMMatrixTranspose(WVP);

	XMStoreFloat4x4(&this->rndData->objBuffData.WVP, WVP);
	//this->rndData.objBuffData
}

void Object::createVertexData()
{
	std::array<Vertex, 4> v;

	XMFLOAT4 color = {1.0f, 1.0f, 0.0f, 1.0f};

	/*
	1 - 2
	|	|
	0 - 3
	*/

	v[0] = Vertex(-0.5f, -0.5f, 0.5f, color);
	v[1] = Vertex(-0.5f, 0.5f, 0.5f, color);
	v[2] = Vertex(0.5f, 0.5f, 0.5f, color);
	v[3] = Vertex(0.5f, -0.5f, 0.5f, color);

	this->rndData = new RenderData(v.data());
	this->offset = 0;
	this->stride = sizeof(Vertex);
	this->rndData->stride = this->stride;
	Locator::getD3D()->createVertexBuffer(&this->vertBuff, v.data(), this->stride, this->offset, v.size());
	this->rndData->vertBuffer = this->vertBuff;

	DWORD indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	this->numIndices = sizeof(indices);
	Locator::getD3D()->createIndexBuffer(&this->indiceBuff, indices, this->numIndices);
	this->rndData->indexBuffer = this->indiceBuff;
}

void Object::createconstBuffData()
{
	//Locator::getD3D()->createConstantBuffer(&this->constBuff, sizeof(objectBuff));
}
