#include "Object.h"
#include "Locator.h"
#include <array>

Object::Object()
{
	this->createVertexData();
	this->createconstBuffData();

	//rndData.vertBuffer = this->triVertBuff;
	//Locator::getD3D()->createIndexBuffer()
}

Object::~Object()
{
}

void Object::renderObj()
{
	Locator::getD3D()->setVertexBuffer(&this->vertBuff, this->stride, this->offset);
	Locator::getD3D()->setIndexBuffer(this->indiceBuff, this->offset);
}

void Object::createVertexData()
{
	std::array<Vertex, 4> v;

	XMFLOAT4 color = {1.0f, 1.0f, 0.0f, 1.0f};

	/*
	1  2

	0  3
	*/

	v[0] = Vertex(-0.5f, -0.5f, 0.5f, color);
	v[1] = Vertex(-0.5f, 0.5f, 0.5f, color);
	v[2] = Vertex(0.5f, 0.5f, 0.5f, color);
	v[3] = Vertex(0.5f, -0.5f, 0.5f, color);

	rndData = RenderData(v.data());
	this->offset = 0;
	this->stride = sizeof(Vertex);
	Locator::getD3D()->createVertexBuffer(&this->vertBuff, v.data(), this->stride, this->offset, v.size());


	DWORD indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	//size_t numbIndices = 6;
	size_t numbIndices = sizeof(indices);
	Locator::getD3D()->createIndexBuffer(&this->indiceBuff, indices, numbIndices);
}

void Object::createconstBuffData()
{
	Locator::getD3D()->createConstantBuffer(&this->constBuff, sizeof(objectBuff));
	int hej = 0; //https://github.com/feliciasp/LitetSpel_TA_GPR3.git
}
