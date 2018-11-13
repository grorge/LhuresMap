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

	//Modles
	newObject = new DynObject(this->cam, L"LP_tree", L"planks");
	newObject->rotateX(3.14f/2.0f);
	newObject->SETSizeFloat(10.0f);
	newObject->SETPosition(XMFLOAT3(700.0f, -100.0f, 1300.0f));
	this->objHandler->addObject(newObject, OBJECTLIST::STATIC);

	newObject = new DynObject(this->cam, L"LP_male", L"bricks");
	newObject->SETSizeFloat(50.0f);
	newObject->SETPosition(XMFLOAT3(-100.0f, -100.0f, 1000.0f));
	this->objHandler->addObject(newObject, OBJECTLIST::MOVING);

	//Test for preststandard
	//for (int i = 0; i < 200; i++)
	//{
	//	newObject = new DynObject(this->cam, L"LP_male", L"bricks");
	//	newObject->SETSizeFloat(50.0f);
	//	newObject->SETPosition(XMFLOAT3(3.0f * (rand() % 300), -100.0f, 1000.0f));
	//	this->object.push_back(newObject);
	//}

	newObject = new DynObject(this->cam, L"bottle", L"gravel");
	newObject->SETSizeFloat3(XMFLOAT3(100.0f, 150.0f, 50.0f));
	newObject->SETPosition(XMFLOAT3(-100.0f, 250.0f, 200.0f));
	this->objHandler->addObject(newObject, OBJECTLIST::MOVING);

	newObject = new DynObject(this->cam, L"bottle", L"gravel");
	newObject->SETSizeFloat3(XMFLOAT3(100.0f, 150.0f, 50.0f));
	newObject->SETPosition(XMFLOAT3(-200.0f, 250.0f, 200.0f));
	this->objHandler->addObject(newObject, OBJECTLIST::TRANS);

	newObject = new DynObject(this->cam, L"HP_Glock", L"gravel");
	newObject->SETSizeFloat3(XMFLOAT3(12.0f, 12.0f, 12.0f));
	newObject->SETPosition(XMFLOAT3(200.0f, 100.0f, 250.0f));
	this->objHandler->addObject(newObject, OBJECTLIST::MOVING);
}

BasicRenderState* BasicRenderState::getInstance() {
	return &sBasicRenderState;
};

void BasicRenderState::init()
{
	this->renderer.init();
	this->rndMode = int(RENDERMODE::LIGHTNORMAL);
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
				this->rndMode++;
				this->rndMode %= int(RENDERMODE::SIZE);
				this->renderer.switchRendermode(this->rndMode);
			}
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

	this->renderer.startTrans();
	this->renderer.render(this->objHandler->getObjList(OBJECTLIST::TRANS));
	


	this->renderer.stopRender();

}
