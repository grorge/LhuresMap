#include "GameManager.h"
#include "D3D.h"
#include "StateManager.h"
#include "State.h"
#include "BasicRenderState.h"
#include "Locator.h"
#include "Renderer.h"
void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;

	this->renderer.init();
	// Set the first state of the game
	StateManager::pushState(BasicRenderState::getInstance());
}

void GameManager::cleanUp()
{
	StateManager::cleanUp();
	//if (this->gameTime != nullptr) {
	//	delete this->gameTime;
	//	this->gameTime = nullptr;
	//}
	
	this->renderer.cleanUp();
}

void GameManager::changeState(State* state)
{
	StateManager::changeState(state);
}

void GameManager::handleEvents()
{
	StateManager::handleEvents(this);
}

bool GameManager::pollEvent(MSG &msg)
{
	return PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
}
 
void GameManager::update()
{
	StateManager::update(this);
}

void GameManager::render()
{
	this->renderer.firstPass();
	StateManager::render(this);
}

void GameManager::display(State* state)
{
	this->renderer.secondPass();
}

void GameManager::setupSecondRenderPass()
{
	this->renderer.secondPassSetup();
}

bool GameManager::getIsRunning()
{
	return this->isRunning;
}

void GameManager::quit()
{
	this->isRunning = false;
}
