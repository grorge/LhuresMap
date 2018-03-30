#include "Camera.h"


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                              CAMERA                   /
/////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//


/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


void Camera::moveCameraUp() {
	DirectX::XMVECTOR upVecNormalized;
	DirectX::XMVECTOR cameraPos;

	upVecNormalized = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);

	// normalize 'UP-movement'
	DirectX::XMVector3Normalize(upVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	upVecNormalized = DirectX::XMVectorScale(
		upVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	cameraPos = DirectX::XMVectorAdd(cameraPos, upVecNormalized);
	
	// Storing the cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraPos);
}

void Camera::moveCameraDown()
{
	DirectX::XMVECTOR upVecNormalized;
	DirectX::XMVECTOR cameraPos;

	upVecNormalized = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);

	// normalize 'UP-movement'
	DirectX::XMVector3Normalize(upVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	upVecNormalized = DirectX::XMVectorScale(
		upVecNormalized,
		this->cameraMoveSpeed * -1.0f
	);

	// MOVE!!
	cameraPos = DirectX::XMVectorAdd(cameraPos, upVecNormalized);

	// Storing the cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraPos);
}

void Camera::moveCameraLeft() {
	DirectX::XMVECTOR moveVecNormalized;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraPos;

	cameraFacingDir = DirectX::XMLoadFloat3(&this->cameraFacingDir);
	cameraUpDir = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);

	// Creates the 'LEFT-movement' vector
	moveVecNormalized = DirectX::XMVector3Cross(
		cameraFacingDir,
		cameraUpDir
	);

	// Normalize the vector
	moveVecNormalized = DirectX::XMVector3Normalize(moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	moveVecNormalized = DirectX::XMVectorScale(
		moveVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	cameraPos = DirectX::XMVectorAdd(cameraPos, moveVecNormalized);

	// Store the new cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraPos);
}

void Camera::moveCameraRight() {
	DirectX::XMVECTOR moveVecNormalized;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraPos;

	cameraUpDir = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraFacingDir = DirectX::XMLoadFloat3(&this->cameraFacingDir);
	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);
	
	// Creates the 'RIGHT-movement' vector
	moveVecNormalized = DirectX::XMVector3Cross(
		cameraUpDir,
		cameraFacingDir
	);

	// Normalize the vector
	moveVecNormalized = DirectX::XMVector3Normalize(moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	moveVecNormalized = DirectX::XMVectorScale(
		moveVecNormalized,
		cameraMoveSpeed
	);

	// MOVE!!
	cameraPos = DirectX::XMVectorAdd(cameraPos, moveVecNormalized);
	
	// Store the new cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraPos);
}

void Camera::moveCameraForward() {
	DirectX::XMVECTOR moveVecNormalized;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraPos;

	cameraUpDir = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraFacingDir = DirectX::XMLoadFloat3(&this->cameraFacingDir);
	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);

	// 'FORWARD-movement' vector already exists, so we just copy + normalize it
	moveVecNormalized = cameraFacingDir;
	moveVecNormalized = DirectX::XMVector3Normalize(moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	moveVecNormalized = DirectX::XMVectorScale(
		moveVecNormalized,
		this->cameraMoveSpeed
	);

	// MOVE!!
	cameraPos = DirectX::XMVectorAdd(cameraPos, moveVecNormalized);

	// Store the new cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraPos);
}

void Camera::moveCameraBackward() {
	DirectX::XMVECTOR moveVecNormalized;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraPos;

	cameraUpDir = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraFacingDir = DirectX::XMLoadFloat3(&this->cameraFacingDir);
	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);

	// 'FORWARD-movement' vector already exists, so we just copy + normalize it
	moveVecNormalized = cameraFacingDir;
	moveVecNormalized = DirectX::XMVector3Normalize(moveVecNormalized);

	// Scale the vector based on the 'cameraMoveSpeed' variable
	// NOTE: We're scaling with NEGATIVE 'cameraMoveSpeed' to go backwards!!
	moveVecNormalized = DirectX::XMVectorScale(
		moveVecNormalized,
		(this->cameraMoveSpeed * -1)
	);

	// MOVE!!
	cameraPos = DirectX::XMVectorAdd(cameraPos, moveVecNormalized);

	// Store the new cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraPos);
}

void Camera::updateRightDir() {
	DirectX::XMVECTOR cameraRightDir;
	DirectX::XMVECTOR cameraUpDir;
	DirectX::XMVECTOR cameraFacingDir;

	cameraUpDir = DirectX::XMLoadFloat3(&this->cameraUpDir);
	cameraFacingDir = DirectX::XMLoadFloat3(&this->cameraFacingDir);

	// Create & set the new 'Right' vector
	cameraRightDir = DirectX::XMVector3Cross(
		cameraUpDir,
		cameraFacingDir
	);

	DirectX::XMStoreFloat3(&this->cameraRightDir, cameraRightDir);
}

//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/


void Camera::init()
{
	DirectX::XMVECTOR cameraStartPos;
	DirectX::XMVECTOR cameraStartFacingDir;

	//cameraStartPos = DirectX::XMVECTOR{ static_cast<float>(arenaWidth * 0.5f), static_cast<float>(sqrt((arenaWidth * arenaWidth + arenaDepth * arenaDepth) / 4)), static_cast<float>((arenaDepth * 0.5f) * 0.30f) };
	//cameraStartPos = DirectX::XMVECTOR{ arenaWidth * 0.5f, 1000.0f, arenaDepth * 0.5f };

	cameraStartPos = DirectX::XMVECTOR{ -2.0f, 100.0f, 1.0f};
	DirectX::XMVECTOR cameraLookAtPos = DirectX::XMVECTOR{ 0.0f, 100.0f, 100.0f };
	cameraStartFacingDir = DirectX::XMVectorSubtract(cameraLookAtPos, cameraStartPos);
	cameraStartFacingDir = DirectX::XMVector3Normalize(cameraStartFacingDir);

	//cameraStartFacingDir = DirectX::XMVECTOR{ arenaWidth * 0.5f, 0.0f, arenaDepth * 0.5f };
	//cameraStartFacingDir = DirectX::XMVECTOR{ 0.0f, -1.0f, 0.0f };

	this->updateRequired = false;

	// Storing cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraStartPos);

	// Storing cameraFacingDir
	DirectX::XMStoreFloat3(&this->cameraFacingDir, cameraStartFacingDir);
	//this->cameraUpDir = DirectX::XMVector3Cross(DirectX::XMVECTOR{ 1.0f, 0.0f, 0.0f }, cameraStartFacingDir);
	DirectX::XMVECTOR cameraUpDir = DirectX::XMVector3Cross(cameraStartFacingDir, DirectX::XMVECTOR{ 1.0f, 0.0f, 0.0f });
	cameraUpDir = DirectX::XMVector3Normalize(cameraUpDir);
	DirectX::XMStoreFloat3(&this->cameraUpDir, cameraUpDir);

	this->angle = 0.45f * DirectX::XM_PI;
	this->nearPlane = 0.5;
	this->farPlane = 10000.0; //200

	DirectX::XMMATRIX view = DirectX::XMMatrixLookToLH(
		cameraStartPos,
		cameraStartFacingDir,
		cameraUpDir
	);

	DirectX::XMStoreFloat4x4(&this->view, view);

	// Initiate the projection matrix
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		(this->angle),
		static_cast<float>(Locator::getD3D()->GETwWidth() / Locator::getD3D()->GETwHeight()),
		this->nearPlane,
		this->farPlane
	);

	DirectX::XMStoreFloat4x4(&this->projection, proj);
}

void Camera::init(float arenaWidth, float arenaDepth)
{
	DirectX::XMVECTOR cameraStartPos;
	DirectX::XMVECTOR cameraStartFacingDir;

	//cameraStartPos = DirectX::XMVECTOR{ static_cast<float>(arenaWidth * 0.5f), static_cast<float>(sqrt((arenaWidth * arenaWidth + arenaDepth * arenaDepth) / 4)), static_cast<float>((arenaDepth * 0.5f) * 0.30f) };
	//cameraStartPos = DirectX::XMVECTOR{ arenaWidth * 0.5f, 1000.0f, arenaDepth * 0.5f };
	
	cameraStartPos = DirectX::XMVECTOR{ arenaWidth * 0.5f, sqrt((arenaWidth * arenaWidth + arenaDepth * arenaDepth) * 0.30f), arenaDepth * 0.5f * 0.25f };
	DirectX::XMVECTOR cameraLookAtPos = DirectX::XMVECTOR{ arenaWidth * 0.5f, 0.0f, (arenaDepth * 0.5f) * 0.75f };
	cameraStartFacingDir = DirectX::XMVectorSubtract(cameraLookAtPos, cameraStartPos);
	cameraStartFacingDir = DirectX::XMVector3Normalize(cameraStartFacingDir);
	
	//cameraStartFacingDir = DirectX::XMVECTOR{ arenaWidth * 0.5f, 0.0f, arenaDepth * 0.5f };
	//cameraStartFacingDir = DirectX::XMVECTOR{ 0.0f, -1.0f, 0.0f };

	this->updateRequired = false;

	// Storing cameraPos
	DirectX::XMStoreFloat3(&this->cameraPos, cameraStartPos);

	// Storing cameraFacingDir
	DirectX::XMStoreFloat3(&this->cameraFacingDir, cameraStartFacingDir);
	//this->cameraUpDir = DirectX::XMVector3Cross(DirectX::XMVECTOR{ 1.0f, 0.0f, 0.0f }, cameraStartFacingDir);
	DirectX::XMVECTOR cameraUpDir = DirectX::XMVector3Cross(cameraStartFacingDir, DirectX::XMVECTOR{ 1.0f, 0.0f, 0.0f });
	cameraUpDir = DirectX::XMVector3Normalize(cameraUpDir);
	DirectX::XMStoreFloat3(&this->cameraUpDir, cameraUpDir);

	this->angle = 0.45f * DirectX::XM_PI;
	this->nearPlane = 0.5;
	this->farPlane = 10000.0; //200

	DirectX::XMMATRIX view = DirectX::XMMatrixLookToLH(
		cameraStartPos,
		cameraStartFacingDir,
		cameraUpDir
	);

	DirectX::XMStoreFloat4x4(&this->view, view);

	// Initiate the projection matrix
	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		(this->angle),
		static_cast<float>(Locator::getD3D()->GETwWidth() / Locator::getD3D()->GETwHeight()),
		this->nearPlane,
		this->farPlane
	);

	DirectX::XMStoreFloat4x4(&this->projection, proj);
}

void Camera::updateCamera() {

	/*
	// POSITIONAL MOVEMENT
	if (characterMessage == 'W') {
		this->updateRequired = true;
		this->moveCameraForward();
	}
	else if (characterMessage == 'A') {
		this->updateRequired = true;
		this->moveCameraLeft();
	}
	else if (characterMessage == 'S') {
		this->updateRequired = true;
		this->moveCameraBackward();
	}
	else if (characterMessage == 'D') {
		this->updateRequired = true;
		this->moveCameraRight();
	}
	else if (characterMessage == 32) {	// 32 == Spacebar
		this->updateRequired = true;
		this->moveCameraUp();
	}
	else if (characterMessage == 'H')	// By-product of merging WindowsProcedure's handling of input and
		this->updateRequired = true;	// the attempt here.
										// -DanneBigD (November, 2016)

	// CAMERA ROTATION
	if (mouseCoordinates.y != 0) {
		this->updateRequired = true;
		this->rotateCameraVertically(mouseCoordinates);
	}

	if (mouseCoordinates.x != 0) {
		this->updateRequired = true;
		this->rotateCameraHorizontally(mouseCoordinates);
	}


	// MISC COMMANDS - Needs to be called after movement and rotation
	if (characterMessage == 'R') {
		updateRequired = true;
		this->resetCamera();
	}
*/
	// IF 'updateRequired' = TRUE --> UPDATE
	DirectX::XMMATRIX view;

	DirectX::XMVECTOR cameraPos;
	DirectX::XMVECTOR cameraFacingDir;
	DirectX::XMVECTOR cameraUpDir;

	cameraPos = DirectX::XMLoadFloat3(&this->cameraPos);
	cameraFacingDir = DirectX::XMLoadFloat3(&this->cameraFacingDir);
	cameraUpDir = DirectX::XMLoadFloat3(&this->cameraUpDir);

	if (true) {
		//Create new VIEW Matrix
		view = DirectX::XMMatrixLookToLH(
			cameraPos,
			cameraFacingDir,
			cameraUpDir
		);

		this->updateRightDir();

		// Updates the View Matrix in the PACKAGED Matrix Data
		//DirectX::XMStoreFloat4x4(&packagedStructData->view, this->view);

		// Edit the constant buffers, updating VIEW data
		//editConstantBuffers(*GSconstantBuffer, *packagedStructData);
	}

	DirectX::XMStoreFloat4x4(&this->view, view);
}

void Camera::resetCamera() {
	this->cameraPos = this->cameraStartPos;
	this->cameraFacingDir = { 0, 0, 1 };
	this->cameraUpDir = { 0, 1, 0 };
}

void Camera::SETangle(float angleInput) {
	this->angle = angleInput;
}

//DirectX::XMFLOAT3 Camera::GETcameraPosFloat3() {
//	
//
//	DirectX::XMStoreFloat3(&this->cameraPos_Float3, this->cameraPos);
//	return this->cameraPos_Float3;
//}
//
//DirectX::XMVECTOR Camera::GETcameraStartPos() {
//	return this->cameraStartPos;
//}

DirectX::XMFLOAT3 Camera::GETcameraPos() {
	return this->cameraPos;
}

DirectX::XMFLOAT3 Camera::GETfacingDir()
{
	return this->cameraFacingDir;
}

DirectX::XMFLOAT4X4 &Camera::GETviewMatrix()
{
	return this->view;
}

DirectX::XMFLOAT4X4 &Camera::GETprojMatrix()
{
	return this->projection;
}

//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                             END OF CAMERA               \
////////////////////////////////////////////////////////////
