#include "Object.h"
#include "Locator.h"
#include <array>

Object::Object()
{
	std::array<Vertex, 3> v;

	v[0] = Vertex (0.0f, 0.5f, 0.5f);
	v[1] = Vertex(0.5f, -0.5f, 0.5f);
	v[2] = Vertex(-0.5f, -0.5f, 0.5f);

	rndData = RenderData(v.data());
	Locator::getD3D();
	this->offset = 0;
	this->stride = sizeof(Vertex);
	Locator::getD3D()->createVertexBuffer(&this->triVertBuff, v.data(), this->stride, this->offset, v.size());

	//Locator::getD3D()->createIndexBuffer()
}

Object::~Object()
{
}

void Object::renderObj()
{
	Locator::getD3D()->setVertexBuffer(&this->triVertBuff, this->stride, this->offset);
}
