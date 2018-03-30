#include "StaticObject.h"
#include <array>

StaticObject::StaticObject(Camera * cam, std::wstring texFile) : Object(cam, texFile)
{
	this->init();

}

StaticObject::~StaticObject()
{
}

void StaticObject::update()
{
}

void StaticObject::createVertexData()
{
	std::array<Vertex, 4> v;

	/*
	5 - 6
	1 - 2 |
	| 4	| 7
	0 - 3
	*/

	int i = 0;

	// Top Face
	v[0] = Vertex(-1.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[2] = Vertex(1.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	v[3] = Vertex(1.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	this->rndData = new RenderData();
	size_t offset = 0;
	this->rndData->stride = sizeof(Vertex);
	Locator::getD3D()->createVertexBuffer(&this->rndData->vertBuffer, v.data(), this->rndData->stride, offset, v.size());
	//this->rndData->vertBuffer = this->vertBuff;

	DWORD indices[] = {
		// Top Face
		0,  1, 2,
		0, 2, 3,
	};
	this->rndData->numbIndices = sizeof(indices);
	//this->rndData->numbIndices = this->numIndices;
	Locator::getD3D()->createIndexBuffer(&this->rndData->indexBuffer, indices, this->rndData->numbIndices);
	//this->rndData->indexBuffer = this->indiceBuff;

}