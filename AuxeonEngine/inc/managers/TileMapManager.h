#pragma once

#ifndef TILEMAPMANAGER_H
#define TILEMAPMANAGER_H

// entities
#include "../inc/entities/GameObject.h"
#include "../inc/entities/Component.h"
// managers
#include "../inc/managers/GraphicsManager.h"
// helpers
#define GLM_SWIZZLE_XYZW
#include "../libs/GLM-0.9.9.6/glm/glm.hpp"
#include "../libs/GLM-0.9.9.6/glm/gtx/transform.hpp"

enum TileTex {
	TWALL,
	TAIR,
	TPLAYER1,
	TPLAYER2,
	TBACKGROUND,
	TTOTAL
};

using TilePair = std::pair<int, int>;

#define MAPSIZE_ROWS 16
#define MAPSIZE_COLS 16
#define TILESIZE 50

class TileMapManager{

public:
	static TileMapManager* tmmCreate();
	static void tmmDestroy();
	static bool tmmGetInstantiated();
	int tmmBlockSize;
	int tmmRows;
	int tmmCols;
	int map[MAPSIZE_ROWS][MAPSIZE_COLS];

public:
	void tmmUpdate();
	void tmmLoadMap(int	a[MAPSIZE_ROWS][MAPSIZE_COLS]);
	void tmmDraw();
	void tmmHandleEvents();

	vec2 tmmGetWorldPos(TilePair);
	TilePair tmmGetMapLoc(vec2 wpos);

private:

	static TileMapManager* tmmInstance;
	static bool tmmInstantiated;
	
	//managers
	GraphicsManager* tmmGraphicsManager;

private:
	
	TileMapManager();
	~TileMapManager();
	bool tmmInit();
};

#endif