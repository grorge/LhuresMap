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

	this->obj = new Object();
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

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void BasicRenderState::update(GameManager * gm)
{
}

void BasicRenderState::render(GameManager * gm)
{
	//this->renderer.render(this->obj->GETRenderData());
	this->obj->renderObj();

	Locator::getD3D()->GETgDevCon()->Draw(3, 0);

	Locator::getD3D()->GETswapChain()->Present(0, 0);
}
