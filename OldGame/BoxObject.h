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
	ID3D11BlendState * Transparency;

	ID3D11Buffer* meshVertBuff;
	ID3D11Buffer* meshIndexBuff;
	XMMATRIX meshWorld;
	int meshSubsets = 0;
	std::vector<int> meshSubsetIndexStart;
	std::vector<int> meshSubsetTexture;

	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> textureNameArray;

	std::vector<SurfaceMaterial> material;

	virtual void createVertexData();
};



#endif // !BOXOBJECT_H
