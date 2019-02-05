#include "MovmentVector.h"
#include "Locator.h"

MoveVector::MoveVector()
{
	speed = (0.0f);
	dirf = (XMFLOAT3(1.0f, 0.0f, 0.0f));
	dir = (DirectX::XMVECTOR(XMLoadFloat3(&dirf)));

	for (auto vec : this->moveListPerm)
	{
		vec = nullptr;
	}
	for (auto vec : this->moveListSingle)
	{
		vec = nullptr;
	}

}

MoveVector::~MoveVector()
{
}

bool MoveVector::addDir(float x, float y, float z)
{

	this->dirf.x += x;
	this->dirf.y += y;
	this->dirf.z += z;

	this->dir = XMVector3Normalize(XMLoadFloat3(&this->dirf));
	XMStoreFloat3(&this->dirf, this->dir);

	return true;
}

void MoveVector::addVector(XMFLOAT4 newVec)
{
	XMFLOAT4* temp = new XMFLOAT4(newVec);

	this->moveList.push_back(temp); 

}
void MoveVector::addPermVector(XMFLOAT4 newVec, unsigned int index)
{
	XMFLOAT4* temp = new XMFLOAT4(newVec);

	this->nrOfPermMove++;

	//if (this->moveListPerm.at(index) != nullptr)
	//	delete this->moveListPerm.at(index);

	this->moveListPerm.at(index) = temp;

}
void MoveVector::addSingleVector(XMFLOAT4 newVec, unsigned int index)
{
	XMFLOAT4* temp = new XMFLOAT4(newVec);

	//this->nrOfPermMove++;
	//if (this->moveListSingle.at(index) != nullptr)
	//	delete this->moveListSingle.at(index);

	this->moveListSingle.at(index) = temp;

}

void MoveVector::update() {

	this->dirf = XMFLOAT3(0.0f, 0.0f, 0.0f);
	for (auto vec : this->moveList)
	{

		this->dirf.x += vec->x * vec->w;
		this->dirf.y += vec->y * vec->w;
		this->dirf.z += vec->z * vec->w;

		vec->w *= 0.99f;// *Locator::getTime()->GETCoeff();
		if (vec->w < 0.01f)
		{
			vec->w = 0.0f;
		}
	}
	for (auto vec : this->moveListPerm)
	{
		if (vec != nullptr)
		{
			this->dirf.x += vec->x * vec->w;
			this->dirf.y += vec->y * vec->w;
			this->dirf.z += vec->z * vec->w;
		}
	}
	for (auto vec : this->moveListSingle)
	{
		if (vec != nullptr)
		{
			this->dirf.x += vec->x * vec->w;
			this->dirf.y += vec->y * vec->w;
			this->dirf.z += vec->z * vec->w;

			vec->w *= 0.99f;// *Locator::getTime()->GETCoeff();
			if (vec->w < 0.01f)
			{
				vec->w = 0.0f;
			}
		}
	}
	// TODO: Remove low movment from the list

	this->dir = XMLoadFloat3(&this->dirf);
	XMStoreFloat(&this->speed, XMVector3LengthEst(this->dir));

	this->dir = XMVector3Normalize(this->dir);
	XMStoreFloat3(&this->dirf, this->dir);
}

void MoveVector::update(XMFLOAT3* parentPos)
{
	this->update();

	parentPos->x += dirf.x * speed;
	parentPos->y += dirf.y * speed;
	parentPos->z += dirf.z * speed;
}