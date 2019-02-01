#include "ObjPosition.h"



ObjPos::ObjPos()
{
	this->movment = new MoveVector();
}

ObjPos::~ObjPos()
{
	delete this->movment;
}

void ObjPos::SETpos(XMFLOAT3 * pos)
{
	this->pos = *pos;
}

void ObjPos::update()
{
	this->pos.x += movment->GETSpeed() * movment->GETDirF3().x;
	this->pos.y += movment->GETSpeed() * movment->GETDirF3().y;
	this->pos.z += movment->GETSpeed() * movment->GETDirF3().z;

	//this->movment->update();
}

void ObjPos::updatePos(XMFLOAT3* pos)
{
	*pos = this->pos;
}
