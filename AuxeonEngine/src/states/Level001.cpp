#include "../inc/states/Level001.h"

#include <iostream>

bool Level001::stateInstantiated = false;
Level001* Level001::stateInstance = nullptr;
GameStateManager* Level001::stateGameStateManager = NULL;

GameObject* player1 = NULL;
GameObject* player2 = NULL;
GameObject* cam01 = NULL;
GameObject* wall[10] = { NULL };

bool Level001::stateGetExists() {
	return(stateGetInstantiated());
}

void Level001::stateInit() {
	std::cout << "Level001 : init\n";
	// setting the FPS 
	stateFrameRateManager->fpsSetFPS(60.0f);

	// adding the camera
	cam01 = &stateGameObjectFactory->gofCreateObject();
	cam01->gaxAddComponent<CameraComponent>();

	// create game objects and init them with values
	player1 = &stateGameObjectFactory->gofCreateObject();
	player1->gaxAddComponent<TransformComponent>(0.0f,0.0f,0.1f);
	player1->gaxAddComponent<ControllerComponent>(1);
	player1->gaxAddComponent<ModelComponent>("res/sprites/player1.bmp");

	player2 = &stateGameObjectFactory->gofCreateObject();
	player2->gaxAddComponent<TransformComponent>(0.0f,0.0f,0.1f);
	player2->gaxAddComponent<ControllerComponent>(2);
	player2->gaxAddComponent<ModelComponent>("res/sprites/player2.bmp");

	//creating the wall
	for (int i = 0; i < 10;++i) {
		wall[i] = &stateGameObjectFactory->gofCreateObject();
		wall[i]->gaxAddComponent<TransformComponent>(-1 + i*0.3f, -1.0f, 0.0f);
		wall[i]->gaxAddComponent<ModelComponent>("res/textures/wall.jpg");
	}
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
		char fpsString[72];
		sprintf_s(fpsString, "%.2f FPS - P1 : %f, %f - P2 : %f, %f", 1 / stateFrameRateManager->fpsGetDeltaTime(), player1->gaxGetComponent<TransformComponent>().txfPosition.x, player1->gaxGetComponent<TransformComponent>().txfPosition.y, player2->gaxGetComponent<TransformComponent>().txfPosition.x, player2->gaxGetComponent<TransformComponent>().txfPosition.y);
		//std::cout << "Frame Time : " << stateFrameRateManager->fpsGetDeltaTime() << std::endl;
		stateGraphicsManager->gfxSetWindowTitle(fpsString);
		
		// all objects call draw 
		stateGameObjectFactory->gofDraw();
		// all managers call draw
		stateInputManager->inmDraw();
		stateGraphicsManager->gfxDraw();
		stateFrameRateManager->fpsReset();
	}

}

void Level001::stateUpdate() {

	stateFrameRateManager->fpsUpdate();
	
	//if (player1->gaxIsActive() && player1->gaxComponentExists<TransformComponent>()) {
	//	std::cout << "player1 pos : " << player1->gaxGetComponent<TransformComponent>().txfPosition.x << ", " << player1->gaxGetComponent<TransformComponent>().txfPosition.y << std::endl;
	//}

	//if (player2->gaxIsActive() && player2->gaxComponentExists<TransformComponent>()) {
	//	std::cout << "player2 pos : " << player2->gaxGetComponent<TransformComponent>().txfPosition.x << ", " << player2->gaxGetComponent<TransformComponent>().txfPosition.y << std::endl;
	//}

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
	stateGameObjectFactory->gofDestroy();
	stateResourceManager->resDestroy();
	stateInputManager->inmDestroy();
	stateGraphicsManager->gfxDestroy();
	stateFrameRateManager->fpsDestroy();
	std::cout << "Level001 : default destructed\n";
}
