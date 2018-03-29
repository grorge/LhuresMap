#include "BasicRenderState.h"
#include "GameManager.h"
//#include "Object.h"
#include "BoxObject.h"
#include "StaticObject.h"

BasicRenderState BasicRenderState::sBasicRenderState;

BasicRenderState* BasicRenderState::getInstance() {
	return &sBasicRenderState;
};

void BasicRenderState::init()
{
	this->renderer.init();

	this->cam = new Camera();
	this->cam->init();
	this->object.push_back(new BoxObject(this->cam, L"planks"));
	this->object.push_back(new BoxObject(this->cam, L"bricks"));
	this->object.push_back(new StaticObject(this->cam, L"dirt"));


	this->object.at(1)->SETPosition({ 0.001f,0.0001f, 2.0f });
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
		else if ( msg.wParam == VK_UP) {
			this->cam->moveCameraUp();
		}
		else if (msg.wParam == VK_DOWN) {
			this->cam->moveCameraDown();
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
	//this->obj->renderObj();

}
