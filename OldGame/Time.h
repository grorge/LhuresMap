#pragma once
#ifndef TIME_H
#define TIME_H

#include "ITime.h"

class Time : public ITime
{
public:
	Time();
	~Time();

	virtual void cycle(); // counts one itteration
	virtual void stop(); // Stops the time
	virtual void start(); // Starts the time

	virtual clock_t GETTime() { return clock(); };

	virtual float GETCoeff() { return this->coefficient * this->factor; };
	virtual float GETFrameTime() { return this->frametime; };
	virtual void SETMulti(float factor) { this->factor = factor; };
	virtual int GETfps() { return this->fps; };

private:
	float coefficient = 0.0f;
	float factor = 0.0f;
	
	// FPS counter
	int frames = 0;
	int fps = 0;
	clock_t lastFrame = clock_t();
	clock_t newFrame = clock_t();
	clock_t frametime = clock_t();
	clock_t lastDisplay = clock_t();
};

#endif // !TIME_H
