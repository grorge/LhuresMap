#pragma once
#ifndef OBJPOSITION_H
#define OBJPOSITION

#include "MovmentVector.h"

class ObjPos
{
	friend MoveVector;
public:
	ObjPos();
	~ObjPos();

	// Gets the position from its parent
	void SETpos(XMFLOAT3* pos);
	// Sets the heigth to determin heigth over the ground
	void SETheight(float input);

	// Handels the diferent vectors affecting the position
	MoveVector *movement;

	void update();
	// applies the objPos.position to the input
	void updatePos(XMFLOAT3* pos);
private:

	XMFLOAT3 pos = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 size = XMFLOAT3(1.000001f, 1.000001f, 1.000001f);
	XMFLOAT3 up = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 dir = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	XMFLOAT3 rotXYZ = XMFLOAT3(0.000001f, 0.000001f, 0.000001f);
	float rotation = 0.0f;

	float height = 0.0f;
};


#endif // !OBJPOSITION_H



