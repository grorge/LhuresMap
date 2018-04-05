#pragma once
#ifndef MODELLOADER_H
#define MODELLOADER_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>

#include "Locator.h"
#include "RenderData.h"

#include <sstream>
#include <dwrite.h>
#include <dinput.h>
#include <vector>
#include <fstream>
#include <istream>


using namespace DirectX;


struct SurfaceMaterial
{
	std::wstring matName;
	XMFLOAT4 difColor;
	int texArrayIndex;
	bool hasTexture;
	bool transparent;
};


class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	//Define LoadObjModel function after we create surfaceMaterial structure
	bool loadObjModel(std::wstring filename,        //.obj filename
		ID3D11Buffer** vertBuff,            //mesh vertex buffer
		ID3D11Buffer** indexBuff,            //mesh index buffer
		std::vector<int>& subsetIndexStart,        //start index of each subset
		std::vector<int>& subsetMaterialArray,        //index value of material for each subset
		std::vector<SurfaceMaterial>& material,        //vector of material structures
		int& subsetCount,                //Number of subsets in mesh
		bool isRHCoordSys,                //true if model was created in right hand coord system
		bool computeNormals);                //true to compute the normals, false to use the files normals

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
};


#endif // !MODELLOADER_H

