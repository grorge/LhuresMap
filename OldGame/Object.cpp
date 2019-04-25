#include "Object.h"
#include "Locator.h"
#include <array>
#include "WICTextureLoader.h"

Object::Object(Camera* cam, std::wstring texFile)
{
	this->cam = cam;
//	this->color = color;

	this->textureFilename = texFile;

	this->up = {0.0f, 1.0f, 0.0f};
}

Object::~Object()
{
	if (this->okToRender)
	{
		this->rndData->~RenderData();
	}
	//delete this->rndData;
}

void Object::updateWorld()
{
	//XMMATRIX mRotationX = XMMatrixRotationX(this->rotXYZ.x);
	//XMMATRIX mRotationY = XMMatrixRotationY(this->rotXYZ.y);
	//XMMATRIX mRotationZ = XMMatrixRotationZ(this->rotXYZ.z);
	//XMMATRIX mRotation = mRotationX * mRotationY * mRotationZ;
	XMMATRIX mRotation = XMMatrixRotationX(this->rotXYZ.x) * XMMatrixRotationY(this->rotXYZ.y) * XMMatrixRotationZ(this->rotXYZ.z);
	//XMMATRIX mRotation = XMMatrixRotationAxis(this->position.movment->GETDir(), 0.00001f);

	

	XMMATRIX mSclaing = XMMatrixScalingFromVector(XMLoadFloat3(&this->size));

	XMMATRIX mPosition = XMMatrixTranslationFromVector(XMLoadFloat3(&this->pos));

	XMMATRIX world = mSclaing * mRotation * mPosition;
    XMMATRIX worldToObject = XMMatrixTranspose(world);
	XMStoreFloat4x4(&this->rndData->objBuffData.world, worldToObject);
	

	XMMATRIX WVP = XMLoadFloat4x4(&cam->GETviewMatrix()) * XMLoadFloat4x4(&cam->GETprojMatrix());
	WVP = XMMatrixTranspose(WVP);
	XMStoreFloat4x4(&this->rndData->objBuffData.WVP, WVP);
}

void Object::rotateX(float rot)
{
	this->rotXYZ.x += rot;
}

void Object::rotateY(float rot)
{
	this->rotXYZ.y += rot;
}

void Object::rotateZ(float rot)
{
	this->rotXYZ.z += rot;
}

void Object::init()
{
	this->okToRender = true;

	this->rndData = new RenderData();

	//this->rndData->transparent = false;

	this->createVertexData();

	this->createTextureSRV();
}

void Object::createTextureSRV()
{
	std::wstring filenameWithLocation(L"Resources\\Textures\\" + this->textureFilename + L".png");
	if (CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), filenameWithLocation.c_str(), nullptr, &this->rndData->texSRV) != S_OK)
	{
		CreateWICTextureFromFile(Locator::getD3D()->GETgDevice(), std::wstring(L"Resources\\Textures\\error.png").c_str(), nullptr, &this->rndData->texSRV);
	}
}
