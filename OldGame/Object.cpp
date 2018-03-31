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
}

void Object::updateWorld()
{
	XMFLOAT3 left(1.0f, 0.0f, 0.0f);
	XMFLOAT3 forward(0.0f, 0.0f, 1.0f);
	
	XMMATRIX mRotationX = XMMatrixRotationAxis(XMLoadFloat3(&this->up), this->rotXYZ.x);
	XMMATRIX mRotationY = XMMatrixRotationAxis(XMLoadFloat3(&left), this->rotXYZ.y);
	XMMATRIX mRotationZ = XMMatrixRotationAxis(XMLoadFloat3(&forward), this->rotXYZ.z);
	XMMATRIX mRotation = mRotationX * mRotationY * mRotationZ;

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
