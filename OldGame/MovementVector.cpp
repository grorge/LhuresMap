#include "MovmentVector.h"
#include "Locator.h"
#include "ObjPosition.h"

MoveVector::MoveVector()
{
	speed = (0.0f);
	dirf = (XMFLOAT3(1.0f, 0.0f, 0.0f));
	dir = (DirectX::XMVECTOR(XMLoadFloat3(&dirf)));
	//this->parent = nullptr

	for (auto vec : this->moveListPerm)
	{
		vec = nullptr;
	}
	for (auto vec : this->moveListSingle)
	{
		vec = nullptr;
	}

}

MoveVector::MoveVector(ObjPos* parent)
{
	this->parent = parent;

	speed = (0.0f);
	dirf = (XMFLOAT3(1.0f, 0.0f, 0.0f));
	dir = (DirectX::XMVECTOR(XMLoadFloat3(&dirf)));
	//this->parent = nullptr

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
	this->moveList.clear();
	
	for (auto vec : this->moveListPerm)
	{
		if (vec != nullptr)
		{
			delete vec;
		}
	}
	for (auto vec : this->moveListSingle)
	{
		if (vec != nullptr)
		{
			delete vec;
		}
	}
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

	// reset the direction
	this->dirf = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// Loop over all vectors and add them together to get a resulting vector
	for (auto vec : this->moveList)
	{
		// .w is the speed of the vector
		this->dirf.x += vec->x * vec->w;
		this->dirf.y += vec->y * vec->w;
		this->dirf.z += vec->z * vec->w;

		// decrease the speed so mimic a breaking animation
		vec->w *= 0.99f;// *Locator::getTime()->GETCoeff();

		// set the vectir to 0.0f so it can be removed from the list
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

	// Update pravate varibles
	this->dir = XMLoadFloat3(&this->dirf);
	XMStoreFloat(&this->speed, XMVector3LengthEst(this->dir));
	this->dir = XMVector3Normalize(this->dir);
	XMStoreFloat3(&this->dirf, this->dir);


	// apply the change to the parents position
	parent->pos.x += dirf.x * speed;
	parent->pos.y += dirf.y * speed;
	parent->pos.z += dirf.z * speed;
}