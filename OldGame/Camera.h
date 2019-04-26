#pragma
#ifndef CAMERA_H
#define CAMERA_H

#include "D3D.h"
#include "Locator.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "ObjPosition.h"

using namespace DirectX;

#define FORWARD_INDEX 0
#define BACKWARDS_INDEX 1
#define RIGTH_INDEX 2
#define LEFT_INDEX 3

class Camera {
private:
	float			cameraMoveSpeed = 2000.0f;
	float			cameraTurnSpeed = 10.0f;
	float			cameraRotateSpeed = 0.02f;
	float			angle = 0.0f;
	float			nearPlane = 0.0f;
	float			farPlane = 0.0f;

	DirectX::XMFLOAT3 cameraStartPos;
	DirectX::XMFLOAT3 cameraStartFacingPos;
	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraFacingDir;
	DirectX::XMFLOAT3 cameraUpDir;
	DirectX::XMFLOAT3 cameraRightDir;

	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;


	DirectX::XMFLOAT3	upVecNormalized;
	DirectX::XMFLOAT3	moveVecNormalized;
	DirectX::XMFLOAT3	rightAxis;


	float				rotationAngle;
	DirectX::XMFLOAT3	rotationQuaternion;
	bool				isMouseMovingUp;
	DirectX::XMFLOAT3	newRotation_Float3;
	DirectX::XMFLOAT3	oldRotation_Float3;
	DirectX::XMFLOAT3	tempRotationDifference_Float3;


	bool updateRequired = false;

	void updateRightDir();


	ObjPos objPos;

public:
	Camera();
	void init();

	void updateCamera();

	void turnCameraLeft();
	void turnCameraRight();
	void moveCameraUp();
	void moveCameraDown();
	void moveCameraLeft();
	void moveCameraRight();
	void moveCameraForward();
	void moveCameraBackward();

	void resetCamera();

	void SETangle(float angleInput);


	DirectX::XMFLOAT3		GETcameraPos();
	DirectX::XMFLOAT3       GETfacingDir();
	DirectX::XMFLOAT4X4&	GETviewMatrix();
	DirectX::XMFLOAT4X4&	GETprojMatrix();

};

#endif
