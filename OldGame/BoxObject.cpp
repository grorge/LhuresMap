#include "BoxObject.h"
#include <array>

BoxObject::BoxObject(Camera * cam, std::wstring texFile) : Object(cam, texFile)
{
	this->init();

	//this->pos.y += 2.0f;
	this->modLod->loadObjModel(L"Resources\\LP_tree.obj", this->rndData, meshSubsetIndexStart, meshSubsetTexture, material, meshSubsets, true, false);

}

BoxObject::~BoxObject()
{
}

void BoxObject::update()
{
	this->rotateX(-0.002f);
	this->rotateY(-0.001f);
}

void BoxObject::createVertexData()
{
	std::array<Vertex, 24> v;

	/*
	5 - 6
	1 - 2 |
	| 4	| 7
	0 - 3
	*/

	int i = 0;
	XMFLOAT3 normal;
	 // Front Face
	normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	v[0] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	v[0].normal = normal;
	v[1] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	v[1].normal = normal;
	v[2] = Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f);
	v[2].normal = normal;
	v[3] = Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f);
	v[3].normal = normal;

		// Back Face
	normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
	v[4] = Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
	v[4].normal = normal;
	v[5] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
	v[5].normal = normal;
	v[6] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	v[6].normal = normal;
	v[7] = Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	v[7].normal = normal;

		// Top Face
	normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	v[8] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f);
	v[8].normal = normal;
	v[9] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	v[9].normal = normal;
	v[10] = Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	v[10].normal = normal;
	v[11] = Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f);
	v[11].normal = normal;

		// Bottom Face
	normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	v[12] = Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f);
	v[12].normal = normal;
	v[13] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	v[13].normal = normal;
	v[14] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f);
	v[14].normal = normal;
	v[15] = Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f);
	v[15].normal = normal;

		// Left Face
	normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	v[16] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
	v[16].normal = normal;
	v[17] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	v[17].normal = normal;
	v[18] = Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f);
	v[18].normal = normal;
	v[19] = Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f);
	v[19].normal = normal;

		// Right Face
	normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
	v[20] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	v[20].normal = normal;
	v[21] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
	v[21].normal = normal;
	v[22] = Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	v[22].normal = normal;
	v[23] = Vertex(1.0f, -1.0f, 1.0f, 1.0f, 1.0f);
	v[23].normal = normal;

	size_t offset = 0;
	this->rndData->stride = sizeof(Vertex);
	Locator::getD3D()->createVertexBuffer(&this->rndData->vertBuffer, v.data(), this->rndData->stride, offset, v.size());
	//this->rndData->vertBuffer = this->vertBuff;

	DWORD indices[] = {
        // Front Face
        0,  1,  2,
        0,  2,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        // Top Face
        8,  9, 10,
        8, 10, 11,

        // Bottom Face
        12, 13, 14,
        12, 14, 15,

        // Left Face
        16, 17, 18,
        16, 18, 19,

        // Right Face
        20, 21, 22,
        20, 22, 23
    };
	this->rndData->numbIndices = sizeof(indices);
	//this->rndData->numbIndices = this->numIndices;
	Locator::getD3D()->createIndexBuffer(&this->rndData->indexBuffer, indices, this->rndData->numbIndices);
	//this->rndData->indexBuffer = this->indiceBuff;

}
