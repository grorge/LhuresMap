#include "Object.h"
#include "Locator.h"
#include <array>

Object::Object()
{
	this->createVertexData();

	//rndData.vertBuffer = this->triVertBuff;
	//Locator::getD3D()->createIndexBuffer()
}

Object::~Object()
{
}

void Object::renderObj()
{
	Locator::getD3D()->setVertexBuffer(&this->triVertBuff, this->stride, this->offset);
}

void Object::createVertexData()
{
	std::array<Vertex, 3> v;

	XMFLOAT4 color = {1.0f, 1.0f, 0.0f, 1.0f};

	v[0] = Vertex(0.0f, 0.5f, 0.5f, color);
	v[1] = Vertex(0.5f, -0.5f, 0.5f, color);
	v[2] = Vertex(-0.5f, -0.5f, 0.5f, color);

	rndData = RenderData(v.data());
	this->offset = 0;
	this->stride = sizeof(Vertex);
	Locator::getD3D()->createVertexBuffer(&this->triVertBuff, v.data(), this->stride, this->offset, v.size());
}
