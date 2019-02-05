#pragma once
#ifndef CONTROLCAMERA_H
#define CONTROLCAMERA_H

#include "Camera.h"

class ControlCamera
{
public:
	ControlCamera(Camera* cam);
	~ControlCamera();

	void updateCamera(WPARAM wParam);
	void stopCamera(WPARAM wParam);

private:
	Camera* pCam;
};

#endif // !CONTROLCAMERA_H
