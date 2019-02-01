#pragma once
#ifndef MOVMENTVECTOR_H
#define MOVMENTVECTOR_H

#include <DirectXMath.h>
#include <list>
#include <array>

using namespace DirectX;

class MoveVector
{
public:
	
	MoveVector();
	~MoveVector();

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
	// Adds the input to the current dir in the dimension
	bool addDir(float x, float y, float z);

	void addVector(XMFLOAT4 newVec);
	void addPermVector(XMFLOAT4 newVec, unsigned int index);


	void update();

private:
	float speed = 0.0f;
	DirectX::XMVECTOR dir;
	DirectX::XMFLOAT3 dirf;

	std::list<DirectX::XMFLOAT4*> moveList;

	int nrOfPermMove = 0;
	std::array<DirectX::XMFLOAT4*, 3> moveListPerm;
};


#endif // !MOVMENTVECTOR_H
