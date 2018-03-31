#include "BasicRenderState.h"
#include "GameManager.h"
//#include "Object.h"
#include "BoxObject.h"
#include "StaticObject.h"

BasicRenderState BasicRenderState::sBasicRenderState;

void BasicRenderState::initScene()
{
	Object* newObject;

	//Gound
	newObject = new StaticObject(this->cam, L"dirt");
	newObject->SETSizeFloat(3000.0f);
	newObject->SETPositionY(-1.0f);
	this->object.push_back(newObject);

	//Boxes
	newObject = new BoxObject(this->cam, L"planks");
	newObject->SETSizeFloat(100.0f);
	newObject->SETPosition(XMFLOAT3(100.0f, 0.0f, 300.0f));
	this->object.push_back(newObject);

	newObject = new BoxObject(this->cam, L"bricks");
	newObject->SETSizeFloat3(XMFLOAT3(500.0f, 50.0f, 50.0f));
	newObject->SETPosition(XMFLOAT3(-100.0f, 50.0f, 1000.0f));
	this->object.push_back(newObject);

	newObject = new BoxObject(this->cam, L"bricks");
	newObject->SETSizeFloat3(XMFLOAT3(50.0f, 500.0f, 50.0f));
	newObject->SETPosition(XMFLOAT3(-100.0f, 250.0f, 600.0f));
	this->object.push_back(newObject);
}

BasicRenderState* BasicRenderState::getInstance() {
	return &sBasicRenderState;
};

void BasicRenderState::init()
{
	this->renderer.init();

	this->cam = new Camera();
	this->cam->init();
	this->controlCamera = new ControlCamera(this->cam);


	this->initScene();
}

void BasicRenderState::cleanUp()
{
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
			if (msg.wParam == 0x51)
			{
				this->object.at(2)->rotateZ(0.1f);
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BasicRenderState::update(GameManager * gm)
{
	this->cam->updateCamera();

	for (auto obj : this->object)
	{
		obj->update();
		obj->updateWorld();
	}
}

void BasicRenderState::render(GameManager * gm)
{
	this->renderer.render(this->object);
}
