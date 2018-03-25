#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"


void RenderInputOrganizer::packageMatrices() {
	XMMATRIX worldMatrix = XMLoadFloat4x4(&this->rawMatrixData.world);
	XMMATRIX viewMatrix = XMLoadFloat4x4(this->rawMatrixData.view);
	XMMATRIX projMatrix = XMLoadFloat4x4(this->rawMatrixData.proj);

	worldMatrix = XMMatrixTranspose(worldMatrix);

	XMStoreFloat4x4(
		&this->packagedMatrixData.world,
		worldMatrix
	);

	worldMatrix = XMLoadFloat4x4(&this->rawMatrixData.world);

	XMMATRIX worldViewProj = worldMatrix * viewMatrix * projMatrix;
	worldViewProj = XMMatrixTranspose(worldViewProj);

	XMStoreFloat4x4(
		&this->packagedMatrixData.worldViewProj,
		worldViewProj
	);
}

void RenderInputOrganizer::drawGraphics(GraphicsComponent *& graphics)
{
	// Get world matrix
	this->rawMatrixData.world = graphics->getWorld();

	this->packageMatrices();

	// Map the matrix package to the buffer
	Locator::getD3D()->mapConstantBuffer(&this->cMatrixBuffer,	&this->packagedMatrixData, sizeof(this->packagedMatrixData));

	// Set the current constant buffer to the matrix package buffer
	Locator::getD3D()->setConstantBuffer(this->cMatrixBuffer, SHADER::VERTEX, 0, 1);

	Locator::getD3D()->setVertexBuffer(&graphics->GETvertexBuffer(), graphics->GETstride(), graphics->GEToffset());
	Locator::getD3D()->setIndexBuffer(graphics->GETindexBuffer(), 0);

	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Locator::getD3D()->GETgDevCon()->DrawIndexed(graphics->GETnumIndices(), 0, 0);
}

void RenderInputOrganizer::initialize(Camera& camera) {
	//this->lights = &lights;

	this->rawMatrixData.view = &camera.GETviewMatrix();
	this->rawMatrixData.proj = &camera.GETprojMatrix();

	this->lightPassData.screenDims = XMFLOAT2(static_cast<float>(Locator::getD3D()->GETwWidth()), static_cast<float>(Locator::getD3D()->GETwHeight()));
	this->lightPassData.camPos = camera.GETcameraPos();
	this->lightPassData.gridStartPos = XMFLOAT2(0.0f, 0.0f);

	Locator::getD3D()->createConstantBuffer(
		&this->cMatrixBuffer,
		sizeof(MatrixBufferPack)
	);

	Locator::getD3D()->createConstantBuffer(&this->cLightPassDataBuffer, sizeof(LightPassData));
	Locator::getD3D()->createConstantBuffer(&this->cLightBuffer, sizeof(Light) * MAX_NUM_POINTLIGHTS);
}

void RenderInputOrganizer::render(std::list<GraphicsComponent*>& graphics)
{
	for (auto &i : graphics) {
		if (i->GETstate() != OBJECTSTATE::TYPE::INVISIBLE) {
			this->drawGraphics(i);
		}
	}
}

void RenderInputOrganizer::injectResourcesIntoSecondPass(const std::vector<std::vector<tileData>>& grid, const std::vector<std::vector<XMFLOAT2>>& gridPulsePoints)
{
}

void RenderInputOrganizer::cleanUp()
{
	this->cLightBuffer->Release();
	this->cLightPassDataBuffer->Release();
	this->cMatrixBuffer->Release();
}