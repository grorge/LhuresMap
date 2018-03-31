#include "ControlCamera.h"

ControlCamera::ControlCamera(Camera * cam)
{
	this->pCam = cam;
}

ControlCamera::~ControlCamera()
{
}

void ControlCamera::updateCamera(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_UP:
		this->pCam->moveCameraUp();
		break;

	case VK_DOWN:
		this->pCam->moveCameraDown();
		break;

	case 0x57: //W
		this->pCam->moveCameraForward();
		break;

	case 0x53: //S
		this->pCam->moveCameraBackward();
		break;

	case 0x41: //A
		this->pCam->moveCameraLeft();
		break;

	case 0x44: //D
		this->pCam->moveCameraRight();
		break;

	case 0x51: //Q
		this->pCam->turnCameraLeft();
		break;
	case 0x45: //E
		this->pCam->turnCameraRight();
		break;

	default:
		break;
	}
}
