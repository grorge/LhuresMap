#include "DynObject.h"
#include <array>

DynObject::DynObject(Camera * cam, std::wstring meshFile, std::wstring texFile) : Object(cam, texFile)
{
	this->meshFile = meshFile;
	//this->modLod = new ModelLoader();
	this->calcNorm = false;

	this->init();
}

DynObject::DynObject(Camera * cam, std::wstring meshFile, std::wstring texFile, bool calcNorm) : Object(cam, texFile)
{
	this->meshFile = meshFile;
	//this->modLod = new ModelLoader();
	this->calcNorm = calcNorm;


	this->init();
}

DynObject::~DynObject()
{
	//delete this->modLod;
}

void DynObject::update()
{
	//HERE VECTOR MOVMENT SHOULD GO
	this->position.SETpos(&this->pos);
	this->position.update();

	this->position.updatePos(&this->pos);


	
}

void DynObject::createVertexData()
{
	
	if (!Locator::getModLoad()->loadObjModel(L"Resources\\Meshes\\" + this->meshFile + L".obj", this->rndData, meshSubsetIndexStart, meshSubsetTexture, meshSubsets, true, this->calcNorm))
	{
		std::string errorMsg;
		this->okToRender = false;
	}

}