#pragma once
#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include "Camera.h"	

#include "Object.h"



using namespace DirectX;

class StaticObject : public Object
{
public:
	StaticObject(Camera* cam, std::wstring texFile);
	~StaticObject();

	void update();

private:

	virtual void createVertexData();
};



#endif // !STATICOBJECT_H
