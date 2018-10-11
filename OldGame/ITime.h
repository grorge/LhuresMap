#pragma once
#ifndef ITIME_H
#define ITIME_H

#include <time.h>

class ITime
{
public:
	virtual void cycle() = 0; // counts one itteration
	virtual void stop() = 0; // Stops the time
	virtual void start() = 0; // Starts the time

	virtual clock_t GETTime() = 0;

	virtual float GETCoeff() = 0;
	virtual float GETFrameTime() = 0;
	virtual void SETMulti(float factor) = 0;
	virtual int GETfps() = 0;

};

#endif // !ITIME_H
