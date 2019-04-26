#pragma once
#ifndef BASICRENDERSTATE_H
#define BASICRENDERSTATE_H

#include "State.h"
#include "ObjectHandler.h"
#include "Camera.h"
#include "ControlCamera.h"
#include "Renderer.h"


class BasicRenderState : public State
{
private:
	static BasicRenderState sBasicRenderState;
	Renderer renderer;
	int rndMode = 0;

	Camera* cam = nullptr;
	ControlCamera* controlCamera = nullptr;
	void initScene();

	//Holds the objects in different lists
	ObjectHandler* objHandler = nullptr;

	Object* createDynObject(std::wstring meshFile, std::wstring texFile, float size, XMFLOAT3 pos);
public:
	static BasicRenderState* getInstance();


	virtual void init();


	virtual void cleanUp();


	virtual void pause();


	virtual void resume();


	virtual void handleEvents(GameManager* gm);


	virtual void update(GameManager* gm);


	virtual void render(GameManager* gm);


};

#endif
