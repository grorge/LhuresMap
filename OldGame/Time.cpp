#include "Time.h"

Time::Time()
{
	this->factor = 0.001f;
}

Time::~Time()
{
}

void Time::cycle()
{
	this->frames++;

	this->newFrame = clock();

	// If the time is more than 1000ms
	if ((this->newFrame - this->lastDisplay) > 1000)
	{
		//Sets the amount of ms between frames
		this->frametime = this->coefficient;

		//Sets thet displayed FPS
		this->fps = this->frames;

		//Reset for next second
		this->frames = 0;
		this->lastDisplay = this->newFrame;
	}

	this->coefficient = this->newFrame - this->lastFrame;

	this->lastFrame = this->newFrame;
}

void Time::stop()
{
}

void Time::start()
{
}
