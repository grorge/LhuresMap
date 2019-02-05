#include "ObjPosition.h"

#define GROUD_LEVEL -100.0f

ObjPos::ObjPos()
{
	this->movement = new MoveVector();
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

	if (yPos - height >= GROUD_LEVEL)
		this->pos.y = yPos;
	else
		this->pos.y = GROUD_LEVEL + height;

	//this->movment->update();
}

void ObjPos::updatePos(XMFLOAT3* pos)
{
	*pos = this->pos;
}
