#pragma once
#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include "Camera.h"	

#include "Object.h"

using namespace DirectX;

class BoxObject : public Object
{
public:
	BoxObject(Camera* cam, std::wstring texFile);
	~BoxObject();

	void update();

private:

	virtual void createVertexData();
};



#endif // !BOXOBJECT_H
