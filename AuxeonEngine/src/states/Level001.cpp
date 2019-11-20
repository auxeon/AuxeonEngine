#include "../inc/states/Level001.h"

#include <iostream>

bool Level001::stateInstantiated = false;
Level001* Level001::stateInstance = nullptr;
GameStateManager* Level001::stateGameStateManager = NULL;

GameObject* player = NULL;

bool Level001::stateGetExists() {
	return(stateGetInstantiated());
}

void Level001::stateInit() {
	std::cout << "Level001 : init\n";
	// setting the FPS 
	stateFrameRateManager->fpsSetFPS(60.0f);

	// create game objects and init them with values
	player = &stateGameObjectFactory->gofCreateObject();
	player->gaxAddComponent<TransformComponent>();
	player->gaxAddComponent<ControllerComponent>(2);
	player->gaxAddComponent<SpriteComponent>("res/sprites/player1.bmp");
}

void Level001::stateCleanup() {
	std::cout << "Level001 : cleanup\n";
	stateDestroy();
}

void Level001::statePause() {
	std::cout << "Level001 : pause\n";
}

void Level001::stateResume() {
	std::cout << "Level001 : resume\n";
}

void Level001::stateHandleEvents() {

	if (SDL_PollEvent(&stateEvent)) {
		// handling state level input
		if (SDL_QUIT == stateEvent.type) {
			std::cout << "sdl quit\n";
			stateGameStateManager->gsmQuit();	
		}
	}

	// all managers call handle events
	stateGraphicsManager->gfxHandleEvents();
	stateInputManager->inmHandleEvents();
	// all objects call handleevents 
	stateGameObjectFactory->gofHandleEvents();
}

void Level001::stateDraw() {
	// show changes on the screen by calls the draw functions 
	if (stateFrameRateManager->fpsGetDeltaTime() > stateFrameRateManager->fpsGetFrameTimeCap()) {
		char fpsString[15];
		sprintf_s(fpsString, "%.2f FPS", 1/stateFrameRateManager->fpsGetDeltaTime());
		stateGraphicsManager->gfxSetWindowTitle(fpsString);
		stateGraphicsManager->gfxDraw();
		// all managers call draw
		stateInputManager->inmDraw();
		// all objects call draw 
		stateGameObjectFactory->gofDraw();
		stateFrameRateManager->fpsReset();
	}
}

void Level001::stateUpdate() {

	stateFrameRateManager->fpsUpdate();

	/*if (player->gaxIsActive() && player->gaxComponentExists<TransformComponent>()) {
		std::cout << "player pos : " << player->gaxGetComponent<TransformComponent>().txfPosition.x << ", " << player->gaxGetComponent<TransformComponent>().txfPosition.y << std::endl;
	}*/

	// all managers call update
	stateResourceManager->resUpdate();
	stateGraphicsManager->gfxUpdate();
	stateInputManager->inmUpdate();
	// for all objects call update 
	stateGameObjectFactory->gofUpdate();

}

// To create the gamestatemanagerinstance
State* Level001::stateCreate(GameStateManager* gameInst) {

	stateGameStateManager = gameInst;
	if (!stateInstantiated) {
		stateInstance = new Level001();
		if (NULL != stateInstance) {
			stateInstantiated = true;
		}
	}
	return(stateInstance);
}

// To destroy the game state manager
void Level001::stateDestroy() {
	if (stateInstantiated) {
		delete stateInstance;
		stateInstance = NULL;
		stateInstantiated = false;
	}
}

// To get the current DOA status of the class
bool Level001::stateGetInstantiated() {
	return stateInstantiated;
}

// Default constructor
Level001::Level001() : stateEvent({NULL}) {

	// calling the fps manager the first thing 
	stateFrameRateManager = FrameRateManager::fpsCreate();
	stateGraphicsManager = GraphicsManager::gfxCreate();
	stateInputManager = InputManager::inmCreate();
	stateResourceManager = ResourceManager::resCreate();
	stateGameObjectFactory = GameObjectFactory::gofCreate();

	std::cout << "Level001 : default constructed\n";

	if (!stateFrameRateManager) {
		std::cout << "Level001 : stateFrameRateManager instantiation error\n";
		stateGameStateManager->gsmQuit();
	}

	// I was doing something stupid inside gamestatemanager destructor i was popping and then setting the last to current state. but at last-1 this would fail
	if (!stateGraphicsManager) {
		std::cout << "Level001 : stateGraphicsManager instantiation error\n";
		stateGameStateManager->gsmQuit();
	}

	if (!stateInputManager) {
		std::cout << "Level001 : stateInputManager instantiation error\n";
		stateGameStateManager->gsmQuit();
	}

	if (!stateResourceManager) {
		std::cout << "Level001 : stateResourceManager insantiation error\n";
		stateGameStateManager->gsmQuit();
	}

	if (!stateGameObjectFactory) {
		std::cout << "Level001 : stateGameObjectFactory instantiation error\n";
		stateGameStateManager->gsmQuit();
	}
}

// Default destructor
Level001::~Level001() {
	std::cout << "Level001 : default destructed\n";

	stateGraphicsManager->gfxDestroy();
	stateInputManager->inmDestroy();
	stateResourceManager->resDestroy();
	stateGameObjectFactory->gofDestroy();
}
