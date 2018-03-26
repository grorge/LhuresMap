#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;


class Object
{
public:
	Object();
	~Object();

	ID3D11Buffer** GETvertexBuffer() {return &triVertBuff;};


private:
	ID3D11Buffer* triVertBuff;
	ID3D11InputLayout* vertLayout;
};

Object::Object()
{
	
}

Object::~Object()
{
}

#endif // !OBJECT_H
