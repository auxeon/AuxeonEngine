#pragma once

#ifndef LEVEL001_H
#define LEVEL001_H

// external includes
#include "../libs/SDL2-2.0.10/include/SDL.h"

// manager includes
#include "../inc/managers/StateManager.h"
#include "../inc/managers/GraphicsManager.h"
#include "../inc/managers/InputManager.h"
#include "../inc/managers/FrameRateManager.h"
#include "../inc/managers/CollisionManager.h"
#include "../inc/managers/PhysicsManager.h"
#include "../inc/managers/TileMapManager.h"

// factory includes
#include "../inc/factories/GameObjectFactory.h"

// entity includes 
#include "../inc/entities/Component.h"
#include "../inc/entities/GameObject.h"

// component includes
#include "../inc/components/TransformComponent.h"
#include "../inc/components/ControllerComponent.h"
#include "../inc/components/SpriteComponent.h"
#include "../inc/components/ModelComponent.h"
#include "../inc/components/ColliderComponent.h"

// each state/level is going to be a singleton 
class Level001 : public State{

public:
	// init is responsible to initialize everything after the main state object is created. stuff like video, game objects etc
	void stateInit();
	// cleanup is responsible to be the one that deleted frees and closes down stuff before the state is destroyed.
	void stateCleanup();

	// pause and resume are responsible to make the state paused and not have any interactions happen
	// or resume from it's last state
	void statePause();
	void stateResume();

	// responsible to manage all the draw update and event handling calls in the current state.
	void stateHandleEvents();
	void stateUpdate();
	void stateDraw();

	// create the current state and then return the current state 
	static State* stateCreate(GameStateManager* gsmInst);
	static void stateDestroy();
	static bool stateGetInstantiated();
	// stateGetExists is a hack to call static ,ethod stateGetInstantiated from pure virtual base class pointer
	bool stateGetExists();
	
private:
	// data
	static bool stateInstantiated;
	static Level001* stateInstance;
	SDL_Event stateEvent;

	// Game
	static GameStateManager* stateGameStateManager;

	// Managers
	GraphicsManager* stateGraphicsManager;
	InputManager* stateInputManager;
	ResourceManager* stateResourceManager;
	FrameRateManager* stateFrameRateManager;
	CollisionManager* stateCollisionManager;
	PhysicsManager* statePhysicsManager;
	TileMapManager* stateTileMapManager;

	// GameObjects
	GameObjectFactory* stateGameObjectFactory;

private:
	// functions
	Level001();
	~Level001();
};

// do not instantiate the static members inside the .h file otherwise you get LNK2005 
// this is because each file that calls this header file redefines the static members
// instead put it in the .cpp file 
//bool Level001::stateInstantiated = false;
//Level001* Level001::stateInstance = nullptr;


#endif