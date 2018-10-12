#pragma once
#ifndef DYNOBJECT_H
#define DYNOBJECT_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>
#include "Camera.h"	
#include "CleanupTools.h"

#include "Object.h"

using namespace DirectX;

class DynObject : public Object
{
public:
	DynObject(Camera* cam, std::wstring meshFile, std::wstring texFile);
	DynObject(Camera* cam, std::wstring meshFile, std::wstring texFile, bool calcNorm);
	~DynObject();

	void update();

private:
	std::wstring meshFile = std::wstring();
	bool calcNorm;

	int meshSubsets = 0;
	std::vector<int> meshSubsetIndexStart;
	std::vector<int> meshSubsetTexture;

	virtual void createVertexData();
};



#endif // !DYNOBJECT_H
