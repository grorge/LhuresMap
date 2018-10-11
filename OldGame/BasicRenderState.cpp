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
	this->object.push_back(newObject);

	//Boxes
	newObject = new DynObject(this->cam, L"LP_tree", L"planks");
	newObject->rotateX(3.14f/2.0f);
	newObject->SETSizeFloat(10.0f);
	newObject->SETPosition(XMFLOAT3(700.0f, -100.0f, 1300.0f));
	this->object.push_back(newObject);

	newObject = new DynObject(this->cam, L"LP_male", L"bricks");
	newObject->SETSizeFloat(50.0f);
	newObject->SETPosition(XMFLOAT3(-100.0f, -100.0f, 1000.0f));
	this->object.push_back(newObject);

	newObject = new DynObject(this->cam, L"bottle", L"gravel");
	newObject->SETSizeFloat3(XMFLOAT3(100.0f, 150.0f, 50.0f));
	newObject->SETPosition(XMFLOAT3(-100.0f, 250.0f, 200.0f));
	this->object.push_back(newObject);

	newObject = new DynObject(this->cam, L"bottle", L"gravel");
	newObject->SETSizeFloat3(XMFLOAT3(100.0f, 150.0f, 50.0f));
	newObject->SETPosition(XMFLOAT3(-200.0f, 250.0f, 200.0f));
	this->object.push_back(newObject);
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

	this->initScene();
}

void BasicRenderState::cleanUp()
{
	for (auto i : this->object)
	{
		delete i;
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
