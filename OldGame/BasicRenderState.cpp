#include "BasicRenderState.h"
#include "GameManager.h"
//#include "Object.h"

BasicRenderState BasicRenderState::sBasicRenderState;

BasicRenderState* BasicRenderState::getInstance() {
	return &sBasicRenderState;
};

void BasicRenderState::init()
{
	this->renderer.init();

	this->cam = new Camera();
	this->cam->init();
	this->object.push_back(new Object(this->cam, { 0.0f, 1.0f, 0.0f, 1.0f }));
	this->object.push_back(new Object(this->cam, { 0.0f, 0.1f, 1.0f, 1.0f }));
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
		if (msg.message == WM_QUIT) {
			gm->quit();
		}
		else if ( msg.wParam == VK_ESCAPE) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BasicRenderState::update(GameManager * gm)
{
	this->object.at(0)->addRotation(0.001f);
	this->object.at(1)->addRotation(-0.002f);

	for (auto obj : this->object)
	{
		obj->update();
	}
}

void BasicRenderState::render(GameManager * gm)
{
	this->renderer.render(this->object);
	//this->obj->renderObj();

}
