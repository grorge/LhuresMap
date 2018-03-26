#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <list>
#include <d3d11.h>
#include <DirectXMath.h>

class Component;
struct Message
{
};

using namespace DirectX;

class GameObject
{
private:
	XMFLOAT4X4 world;
	XMFLOAT4X4 translationMatrix;
	XMFLOAT4X4 scaleMatrix;
	XMFLOAT4X4 rotationMatrix;

protected:
	std::list<Component*> components;
	const size_t ID;
	XMFLOAT3 pos;



public:
	GameObject(const size_t ID) : ID(ID), pos(XMFLOAT3(0.0f, 0.0f, 0.0f)) {}
	GameObject(const size_t ID, XMFLOAT3 pos) : ID(ID), pos(pos) {}
	virtual ~GameObject() {}

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Send the parameter ' msg '(obj) to all components that have been added to the object.
	*/
	void send(Message msg);
	virtual void update();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleans up the GameObject and all the attached components.
	*/
	virtual void cleanUp();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Adds a component using the 'components.push_back()' function.
	*/
	void addComponent(Component* component);
	const size_t getID() const { return this->ID; }

	void setPosition(XMFLOAT3 pos) { this->pos = pos; }
	void setPositionY(float value) { this->pos.y = value; }
	XMFLOAT3 GETPosition() const { return this->pos; }
	virtual XMFLOAT3 getDirection() { return this->pos; }
	XMFLOAT4X4& getWorld();
	void SETworldMatrix(XMMATRIX& wMatrix);
	void SETtranslationMatrix(XMMATRIX& translationM);
	void SETscaleMatrix(XMMATRIX& scaleM);
	void SETrotationMatrix(XMMATRIX& rotationM);
	void updateWorldMatrix();
	XMFLOAT4X4& getRotationMatrix();
};

#endif // !GAMEOBJECT_H
