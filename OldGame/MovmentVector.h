#pragma once
#ifndef MOVMENTVECTOR_H
#define MOVMENTVECTOR_H

#include <DirectXMath.h>

using namespace DirectX;

struct MoveVector
{
	float speed;
	DirectX::XMVECTOR dir;
	DirectX::XMFLOAT3 dirf;
	
	MoveVector() : speed(0.0f), dirf(XMFLOAT3(1.0f, 0.0f, 0.0f)), dir(DirectX::XMVECTOR(XMLoadFloat3(&dirf))) {};

	/// SPEEED FUNCTIONS
	float GETSpeed() { return this->speed; };

	// Adds the input to the current speed
	float addSpeed(float input) { this->speed += input;  return this->speed;
	};
	// Multiplies the input to the current speed
	float multSpeed(float input) { this->speed *= input;  return this->speed;
	};
	// Sets the input to the current speed
	float SETSpeed(float input) { this->speed = input;  return this->speed;
	};
	// Sets the input to the current speed
	float stop() { this->speed = 0; return this->speed; 
	};

	/// DIRECTION FUNCTIONS
	DirectX::XMVECTOR GETDir() { return this->dir; };
	DirectX::XMFLOAT3 GETDirF3() { XMStoreFloat3(&this->dirf, dir); return this->dirf; };
	//float GETup() { return this->dir.y; };

	// Rotates around y-axis
	DirectX::XMVECTOR rotate(float input) {
		XMVectorRotateLeft(this->dir, input); 
		return this->dir;
	};
	// Sets dirsction
	DirectX::XMVECTOR SETDir(DirectX::XMFLOAT3 input) { this->dir = DirectX::XMLoadFloat3(&input); return this->dir;
	};

	void update() {};
};


#endif // !MOVMENTVECTOR_H

