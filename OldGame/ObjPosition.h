#pragma once
#ifndef OBJPOSITION_H
#define OBJPOSITION

#include "MovmentVector.h"

class ObjPos
{
public:
	ObjPos();
	~ObjPos();

	void SETpos(XMFLOAT3* pos);

	MoveVector *movment;

	void update();
	void updatePos(XMFLOAT3* pos);
private:

	XMFLOAT3 pos = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 size = XMFLOAT3(1.000001f, 1.000001f, 1.000001f);
	XMFLOAT3 up = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 dir = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 rotXYZ = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float rotation = 0.0f;
};


#endif // !OBJPOSITION_H



