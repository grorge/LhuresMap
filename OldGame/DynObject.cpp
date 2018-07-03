#include "DynObject.h"
#include <array>

DynObject::DynObject(Camera * cam, std::wstring meshFile, std::wstring texFile) : Object(cam, texFile)
{
	this->meshFile = meshFile;
	this->modLod = new ModelLoader();


	this->init();
}

DynObject::~DynObject()
{
	delete this->modLod;
}

void DynObject::update()
{
	//this->rotateX(-0.002f);
	this->rotateY(-0.001f);
}

void DynObject::createVertexData()
{
	if (!this->modLod->loadObjModel(L"Resources\\Meshes\\" + this->meshFile + L".obj", this->rndData, meshSubsetIndexStart, meshSubsetTexture, meshSubsets, true, false))
	{
		std::string errorMsg;
		this->okToRender = false;
	}

}