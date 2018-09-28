#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "ID3D.h"
#include "ID2D.h"
#include "ITime.h"

/* Service Locator pattern */

class Locator
{
private:
	static ID3D* sID3D;
	static ID2D* sID2D;
	static ITime* sITime;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Provides the address of 'gameTime'(obj) to the 'sGT'(ptr) Locator object.
	2. Passes the pointer to 'gameTime'(obj) as a parameter.
	*/
	static void provide(ID3D* d3d) { sID3D = d3d; }
	static void provide(ID2D* d2d) { sID2D = d2d; }
	static void provide(ITime* time) { sITime = time; }
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'sGT'(ptr).
	2. 'sGT'(ptr) points to the address of 'gameTime'(obj), thereby returning that address.
	*/
	static ID3D* getD3D() { return sID3D; }
	static ID2D* getD2D() { return sID2D; }
	static ITime* getTime() { return sITime; }
};

#endif
