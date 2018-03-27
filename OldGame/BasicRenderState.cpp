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

	this->object.push_back(new Object());
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
		else if ( msg.message == VK_ESCAPE) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BasicRenderState::update(GameManager * gm)
{
}

void BasicRenderState::render(GameManager * gm)
{
	this->renderer.render(this->object);
	//this->obj->renderObj();

}
