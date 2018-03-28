#include "Object.h"
#include "Locator.h"
#include <array>

Object::Object(Camera* cam, XMFLOAT4 color)
{
	this->cam = cam;
	this->color = color;

	this->createVertexData();

	this->up = {0.0f, 1.0f, 0.0f};

	this->pos.y = color.y;
	this->size = 1.0f;

}

Object::~Object()
{
}

void Object::renderObj()
{
	
}

void Object::update()
{
	XMMATRIX WVP = XMMatrixIdentity() * XMLoadFloat4x4(&cam->GETviewMatrix()) * XMLoadFloat4x4(&cam->GETprojMatrix());
	WVP = XMMatrixTranspose(WVP);

	XMMATRIX mPosition = XMMatrixTranslationFromVector(XMLoadFloat3(&this->pos));
	XMMATRIX mRotation = XMMatrixRotationAxis(XMLoadFloat3(&this->up), this->rotation);
	XMMATRIX mSclaing = XMMatrixScaling(this->size, this->size, this->size);

	XMMATRIX world = mPosition * mRotation * mSclaing;
	world = XMMatrixTranspose(world);

	XMStoreFloat4x4(&this->rndData->objBuffData.WVP, WVP);
	XMStoreFloat4x4(&this->rndData->objBuffData.world, world);
}

void Object::addRotation(float rot)
{
	this->rotation += rot;
	if (fabs(this->rotation) > 6.28f)
	{
		this->rotation = 0.0f;
	}
}

void Object::createVertexData()
{
	std::array<Vertex, 8> v;

	//XMFLOAT4 color = {1.0f, 1.0f, 0.0f, 1.0f};

	/*
	1 - 2
	|	|
	0 - 3
	*/

	v[0] = Vertex(-0.5f, -0.5f, 0.0f, this->color);
	v[1] = Vertex(-0.5f, 0.5f, 0.0f, this->color);
	v[2] = Vertex(0.5f, 0.5f, 0.0f, this->color);
	v[3] = Vertex(0.5f, -0.5f, 0.0f, this->color);
	v[4] = Vertex(-0.5f, -0.5f, 0.5f, this->color);
	v[5] = Vertex(-0.5f, 0.5f, 0.5f, this->color);
	v[6] = Vertex(0.5f, 0.5f, 0.5f, this->color);
	v[7] = Vertex(0.5f, -0.5f, 0.5f, this->color);

	this->rndData = new RenderData();
	this->offset = 0;
	this->stride = sizeof(Vertex);
	this->rndData->stride = this->stride;
	Locator::getD3D()->createVertexBuffer(&this->vertBuff, v.data(), this->stride, this->offset, v.size());
	this->rndData->vertBuffer = this->vertBuff;

	DWORD indices[] = {
		0, 1, 2,
		0, 2, 3,
		2 + 4, 1 + 4, 0 + 4,
		3 + 4, 2 + 4, 0 + 4
	};
	this->numIndices = sizeof(indices);
	this->rndData->numbIndices = this->numIndices;
	Locator::getD3D()->createIndexBuffer(&this->indiceBuff, indices, this->numIndices);
	this->rndData->indexBuffer = this->indiceBuff;
}

void Object::createconstBuffData()
{
	//Locator::getD3D()->createConstantBuffer(&this->constBuff, sizeof(objectBuff));
}
