#include "BasicRenderState.h"
#include "GameManager.h"
//#include "Object.h"
#include "DynObject.h"
#include "StaticObject.h"

BasicRenderState BasicRenderState::sBasicRenderState;

void BasicRenderState::initScene()
{

	Object* newObject;

	//Gound
	newObject = new StaticObject(this->cam, L"dirt");
	newObject->SETSizeFloat(3000.0f);
	newObject->SETPositionY(-101.0f);
	this->objHandler->addObject(newObject, OBJECTLIST::STATIC);

	////MODLES
	//PreLoad modles, texture dosnt matter
	DynObject(this->cam, L"LP_tree", L"planks");
	DynObject(this->cam, L"LP_male", L"planks");
	DynObject(this->cam, L"bottle", L"planks");
	DynObject(this->cam, L"HP_Glock", L"planks");

	//Add modles
	// (Old way to show more options)
	newObject = new DynObject(this->cam, L"LP_tree", L"planks");
	newObject->rotateX(3.14f/2.0f);
	newObject->SETSizeFloat(10.0f);
	newObject->SETPosition(XMFLOAT3(700.0f, -100.0f, 1300.0f));
	this->objHandler->addObject(newObject, OBJECTLIST::STATIC);


	this->objHandler->addObject(
		this->createDynObject(
			L"LP_male", L"bricks",
			50.0f, 
			XMFLOAT3(-100.0f, -100.0f, 1000.0f))
		, OBJECTLIST::MOVING);

	this->objHandler->addObject(
		this->createDynObject(
			L"LP_male", L"bricks",
			10.0f, 
			XMFLOAT3(-100.0f, -100.0f, 1000.0f))
		, OBJECTLIST::MOVING);

	//Test for preformance
	{
		float tempXaxis = -3000.0f;
		for (int i = 0; i < 200; i++)
		{
			this->objHandler->addObject(
				this->createDynObject(
					L"LP_male", L"gravel", 
					50.0f, 
					XMFLOAT3(tempXaxis, -100.0f, 2000.0f))
				, OBJECTLIST::MOVING);

			tempXaxis += 200.0f;
		}
	}

	//newObject = new DynObject(this->cam, L"bottle", L"gravel");
	//newObject->SETSizeFloat3(XMFLOAT3(100.0f, 150.0f, 50.0f));
	//newObject->SETPosition(XMFLOAT3(-100.0f, 250.0f, 200.0f));
	//this->objHandler->addObject(newObject, OBJECTLIST::MOVING);
	this->objHandler->addObject(
		this->createDynObject(
			L"bottle", L"gravel",
			100.0f,
			XMFLOAT3(-100.0f, 250.0f, 200.0f))
		, OBJECTLIST::MOVING);

	this->objHandler->addObject(
		this->createDynObject(
			L"bottle", L"gravel",
			100.0f,
			XMFLOAT3(-50.0f, 250.0f, 200.0f))
		, OBJECTLIST::MOVING);

	this->objHandler->addObject(
		this->createDynObject(
			L"bottle", L"gravel",
			100.0f,
			XMFLOAT3(-200.0f, 250.0f, 200.0f))
		, OBJECTLIST::TRANS);

	this->objHandler->addObject(
		this->createDynObject(
			L"HP_Glock", L"gravel",
			12.0f,
			XMFLOAT3(200.0f, 100.0f, 250.0f))
		, OBJECTLIST::MOVING);
}

Object * BasicRenderState::createDynObject(std::wstring meshFile, std::wstring texFile, float size, XMFLOAT3 pos)
{
	Object* newObject;
	newObject = new DynObject(this->cam, meshFile, texFile);
	newObject->SETSizeFloat(size);
	newObject->SETPosition(pos);

	return newObject;
}

BasicRenderState* BasicRenderState::getInstance() {
	return &sBasicRenderState;
};

void BasicRenderState::init()
{
	this->renderer.init();
	this->rndMode = int(RENDERMODE::LIGHTDIST);
	this->renderer.switchRendermode(this->rndMode);

	this->cam = new Camera();
	this->cam->init();
	this->controlCamera = new ControlCamera(this->cam);

	this->objHandler = new ObjectHandler;

	this->initScene();
}

void BasicRenderState::cleanUp()
{
	for (int i = 0; i < sizeof(OBJECTLIST); i++)
	{
		for (auto k : this->objHandler->getObjList((OBJECTLIST)i))
		{
			delete k;
		}
	}
		
	this->renderer.cleanUp();
	delete this->cam;
	delete this->controlCamera;
}

void BasicRenderState::pause()
{
}

void BasicRenderState::resume()
{
}

void BasicRenderState::handleEvents(GameManager * gm)
{
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT || msg.wParam == VK_ESCAPE) {
			gm->quit();
		}
		else if ( msg.message == WM_KEYDOWN) {
			this->controlCamera->updateCamera(msg.wParam);
			if (msg.wParam == 0x52) // R
			{
				//this->objHandler->getObjList(OBJECTLIST::MOVING).at(0)->GETmovement()->addVector(XMFLOAT4(0.0f, 1.0f, 0.0f, 3.5f));

				this->rndMode++;
				this->rndMode %= int(RENDERMODE::SIZE);
				this->renderer.switchRendermode(this->rndMode);
			}
		}
		else if ( msg.message == WM_KEYUP) {
			this->controlCamera->stopCamera(msg.wParam);
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BasicRenderState::update(GameManager * gm)
{
	Locator::getD2D()->SETTextFormat(std::to_wstring(Locator::getTime()->GETCoeff()));

	this->cam->updateCamera();

	for (auto obj : this->objHandler->getObjList(OBJECTLIST::MOVING))
	{
		obj->rotateY(0.01f);

		//obj->GETmovement()->update();

		obj->update();
		obj->updateWorld();
	}
	for (auto obj : this->objHandler->getObjList(OBJECTLIST::STATIC))
	{
		obj->update();
		obj->updateWorld();
	}
	for (auto obj : this->objHandler->getObjList(OBJECTLIST::TRANS))
	{
		obj->update();
		obj->updateWorld();
	}
}

void BasicRenderState::render(GameManager * gm)
{
	this->renderer.startRender();
	
	this->renderer.render(this->objHandler->getObjList(OBJECTLIST::STATIC));
	this->renderer.render(this->objHandler->getObjList(OBJECTLIST::MOVING));

	//Switch to transparent blendstate
	this->renderer.startTrans();
	this->renderer.render(this->objHandler->getObjList(OBJECTLIST::TRANS));
	
	this->renderer.stopRender();
}
