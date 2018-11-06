#pragma once

#ifndef IMODELLOADER_H
#define IMODELLOADER_H

#pragma comment(lib, "d3d11.lib")

#include <d3d11.h>
#include <DirectXMath.h>

#include "RenderData.h"

#include <sstream>
#include <dwrite.h>
#include <dinput.h>
#include <vector>
#include <array>
#include <fstream>
#include <istream>


using namespace DirectX;


//Handles loading of meshes, call .loadObjModel()
class IModelLoader
{
public:
	//Define LoadObjModel function after we create surfaceMaterial structure

	//Takes model from filename and loads info into the rndData
	virtual bool loadObjModel(std::wstring filename,        //.obj filename
		RenderData* rndData,            //mesh index buffer
		std::vector<int>& subsetIndexStart,        //start index of each subset
		std::vector<int>& subsetMaterialArray,        //index value of material for each subset
		int& subsetCount,                //Number of subsets in mesh
		bool isRHCoordSys,                //true if model was created in right hand coord system
		bool computeNormals) = 0;                //true to compute the normals, false to use the files normals

};


#endif // !IMODELLOADER_H