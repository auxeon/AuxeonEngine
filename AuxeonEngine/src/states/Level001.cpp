#include "../inc/states/Level001.h"

#include <iostream>

#define PBLOCKSIZE 50;
#define WBLOCKSIZE 50;

bool Level001::stateInstantiated = false;
Level001* Level001::stateInstance = nullptr;
GameStateManager* Level001::stateGameStateManager = NULL;

GameObject* player1 = NULL;
GameObject* player2 = NULL;
GameObject* cam01 = NULL;
GameObject* wall[256] = { NULL };
GameObject* tiles[16][16] = { { NULL } };
//ColliderComponent<Box>* p1Box = NULL;
ColliderComponent<Box>* p2Box = NULL;

bool Level001::stateGetExists() {
	return(stateGetInstantiated());
}

void Level001::stateInit() {

	float PLAYERBLOCKSIZE = PBLOCKSIZE;
	float WALLBLOCKSIZE = WBLOCKSIZE;

	std::cout << "Level001 : init\n";
	// setting the FPS 
	stateFrameRateManager->fpsSetFPS(60.0f);

	// adding the camera
	cam01 = &stateGameObjectFactory->gofCreateObject();
	cam01->gaxAddComponent<CameraComponent>();

	// create game objects and init them with values
	player1 = &stateGameObjectFactory->gofCreateObject();
	player1->gaxAddComponent<TransformComponent>(100, 700, 0.3f);
	player1->gaxAddComponent<ControllerComponent>(1);
	player1->gaxAddComponent<ModelComponent>("res/sprites/player1.bmp", PLAYERBLOCKSIZE);
	player1->gaxAddComponent<ColliderComponent<Box>>(vec3(0.0f, 0.0f, 0.0f), PLAYERBLOCKSIZE, PLAYERBLOCKSIZE, glm::mat4(1.0f));
	player1->gaxAddComponent<PhysicsComponent>();

	player2 = &stateGameObjectFactory->gofCreateObject();
	player2->gaxAddComponent<TransformComponent>(200, 700, 0.3f);
	player2->gaxAddComponent<ControllerComponent>(2);
	player2->gaxAddComponent<ModelComponent>("res/sprites/player2.bmp", PLAYERBLOCKSIZE);
	player2->gaxAddComponent<ColliderComponent<Box>>(vec3(0.0f, 0.0f, 0.0f), PLAYERBLOCKSIZE, PLAYERBLOCKSIZE, glm::mat4(1.0f));
	player2->gaxAddComponent<PhysicsComponent>();

	int rows = stateTileMapManager->tmmRows;
	int cols = stateTileMapManager->tmmCols;
	int s = stateTileMapManager->tmmBlockSize;

	for (int i = 0; i < rows;++i) {
		for (int j = 0; j < cols; ++j) {
			if (0 != stateTileMapManager->map[i][j]) {
				vec2 pos = stateTileMapManager->tmmGetWorldPos(TilePair(i, j));
				//true because iswall param is being set
				tiles[i][j] = &stateGameObjectFactory->gofCreateObject(true);
				tiles[i][j]->gaxAddComponent<TransformComponent>(pos.x,pos.y,0);
				tiles[i][j]->gaxAddComponent<ModelComponent>("res/textures/paper.bmp", WALLBLOCKSIZE);
			}
		}
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
		char fpsString[100];
		sprintf_s(fpsString, "%.2f FPS - P1 : %f, %f - P2 : %f, %f", 1 / stateFrameRateManager->fpsGetDeltaTime(), player1->gaxGetComponent<TransformComponent>().txfPosition.x, player1->gaxGetComponent<TransformComponent>().txfPosition.y, player2->gaxGetComponent<TransformComponent>().txfPosition.x, player2->gaxGetComponent<TransformComponent>().txfPosition.y);
		//sprintf_s(fpsString, "%.2f FPS - P1 : %f, %f", 1 / stateFrameRateManager->fpsGetDeltaTime(), player1->gaxGetComponent<TransformComponent>().txfPosition.x, player1->gaxGetComponent<TransformComponent>().txfPosition.y);
		//std::cout << "Frame Time : " << stateFrameRateManager->fpsGetDeltaTime() << std::endl;
		// all objects call draw 
		stateTileMapManager->tmmDraw();
		statePhysicsManager->physicsDraw();
		stateGameObjectFactory->gofDraw();
		// all managers call draw
		stateInputManager->inmDraw();
		stateGraphicsManager->gfxDraw();
		stateGraphicsManager->gfxSetWindowTitle(fpsString);
		stateFrameRateManager->fpsReset();
	}

}

void Level001::stateUpdate() {

	stateFrameRateManager->fpsUpdate();
	stateInputManager->inmUpdate();
	// for all objects call update 
	// all managers call update
	stateResourceManager->resUpdate();
	stateTileMapManager->tmmUpdate();
	stateGraphicsManager->gfxUpdate();
	stateGameObjectFactory->gofUpdate();
	statePhysicsManager->physicsUpdate(stateFrameRateManager->fpsGetFrameTimeCap());
	stateCollisionManager->colmanUpdate();
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
	stateCollisionManager = CollisionManager::colmanCreate();
	statePhysicsManager = PhysicsManager::physicsCreate();
	stateTileMapManager = TileMapManager::tmmCreate();

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

	if (!stateCollisionManager) {
		std::cout << "Level001 : stateCollisionManager instantiation error\n";
		stateGameStateManager->gsmQuit();
	}

	if (!stateTileMapManager) {
		std::cout << "Level001 : stateTileMapManager instantiation error\n";
		stateGameStateManager->gsmQuit();
	}

	if (!statePhysicsManager) {
		std::cout << "Level001 : statePhysicsManager instantiation error\n";
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
	stateCollisionManager->colmanDestroy();
	statePhysicsManager->physicsDestroy();
	stateTileMapManager->tmmDestroy();
	std::cout << "Level001 : default destructed\n";
}
