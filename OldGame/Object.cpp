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

	XMMATRIX mPosition = XMMatrixTranslationFromVector(XMLoadFloat3(&this->pos));
	XMMATRIX mRotation = XMMatrixRotationAxis(XMLoadFloat3(&this->up), this->rotation);
	XMMATRIX mSclaing = XMMatrixScalingFromVector(XMLoadFloat3(&this->size));

	XMMATRIX WVP = XMLoadFloat4x4(&cam->GETviewMatrix()) * XMLoadFloat4x4(&cam->GETprojMatrix());
	WVP = XMMatrixTranspose(WVP);

	XMMATRIX world = mRotation * mSclaing * mPosition;
	world = XMMatrixTranspose(world);

	XMStoreFloat4x4(&this->rndData->objBuffData.WVP, WVP);
	XMStoreFloat4x4(&this->rndData->objBuffData.world, world);
}

void Object::addRotation(float rot)
{
	this->rotation += rot;
	if (fabs(this->rotation) > 6.28f)
	{
		this->rotation = 0.0f;
	}
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
