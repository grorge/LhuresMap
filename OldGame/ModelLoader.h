#pragma once
#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "IModelLoader.h"

struct savedMeshData
{
	std::wstring meshName;
	D3D11_BUFFER_DESC indexBufferDesc;
	std::vector<DWORD> indices;
	std::vector<Vertex> vertices;

	savedMeshData() :
		meshName(std::wstring())
	{};

	savedMeshData(
		std::wstring filename, 
		RenderData* rndData) :
			meshName(filename) {};
};


struct SurfaceMaterial
{
	std::wstring matName;
	XMFLOAT4 difColor;
	int texArrayIndex;
	bool hasTexture;
	bool transparent;
};

//Handles loading of meshes, call .loadObjModel()
class ModelLoader : public IModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	   
	//Define LoadObjModel function after we create surfaceMaterial structure
	virtual bool loadObjModel(std::wstring filename,        //.obj filename
		RenderData* rndData,            //mesh index buffer
		std::vector<int>& subsetIndexStart,        //start index of each subset
		std::vector<int>& subsetMaterialArray,        //index value of material for each subset
		int& subsetCount,                //Number of subsets in mesh
		bool isRHCoordSys,                //true if model was created in right hand coord system
		bool computeNormals);                //true to compute the normals, false to use the files normals

private:
	//int meshSubsets = 0;
	std::vector<int> meshSubsetTexture;

	// Saves meshes s oit can be used again faster
	std::vector<savedMeshData *> savedData;

	std::vector<ID3D11ShaderResourceView*> meshSRV;
	std::vector<std::wstring> textureNameArray;
	
	std::vector<Vertex> vertices;
};


#endif // !MODELLOADER_H

