#include "ObjPosition.h"

#define GROUD_LEVEL -100.0f

ObjPos::ObjPos()
{
	this->movement = new MoveVector(this);
}

ObjPos::~ObjPos()
{
	delete this->movement;
}

void ObjPos::SETpos(XMFLOAT3 * pos)
{
	this->pos = *pos;
}

void ObjPos::SETheight(float input)
{
	this->height = input;
}

void ObjPos::update()
{
	this->pos.x += movement->GETSpeed() * movement->GETDirF3().x;
	this->pos.z += movement->GETSpeed() * movement->GETDirF3().z;

	float yPos = this->pos.y + movement->GETSpeed() * movement->GETDirF3().y;

	// hardcoded ground level, should be improved with a heigthmap
	if (yPos - height >= GROUD_LEVEL)
		this->pos.y = yPos;
	else
		this->pos.y = GROUD_LEVEL + height;

	// This was copied out to only use on moving objects
	//this->movment->update();
}

void ObjPos::updatePos(XMFLOAT3* pos)
{
	*pos = this->pos;
}
