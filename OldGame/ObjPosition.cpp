#include "ObjPosition.h"



ObjPos::ObjPos()
{

}

ObjPos::~ObjPos()
{
}

void ObjPos::SETpos(XMFLOAT3 * pos)
{
	this->pos = *pos;
}

void ObjPos::update()
{


	this->pos.x += movment.speed * movment.dirf.x;
	this->pos.z += movment.speed * movment.dirf.y;
	this->pos.z += movment.speed * movment.dirf.z;


	this->movment.update();
}

void ObjPos::updatePos(XMFLOAT3* pos)
{
	*pos = this->pos;
}
