#include "../inc/managers/TileMapManager.h"
#include <iostream>

TileMapManager* TileMapManager::tmmInstance = NULL;
bool TileMapManager::tmmInstantiated = false;

int l1[16][16] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

bool TileMapManager::tmmInit() {
	tmmLoadMap(l1);
	std::cout << "TileMapManager : init" << std::endl;
	return true;
}

TileMapManager::TileMapManager():tmmBlockSize(TILESIZE),tmmRows(MAPSIZE_ROWS),tmmCols(MAPSIZE_COLS){
	tmmInstantiated = tmmInit();
	std::cout << "TileMapManager : default constructed" << std::endl;
}

TileMapManager::~TileMapManager() {
	std::cout << "TileMapManager : default destructed" << std::endl;
}

TileMapManager* TileMapManager::tmmCreate() {
	if (!tmmInstantiated) {
		tmmInstance = new TileMapManager;
	}
	return tmmInstance;
}

void TileMapManager::tmmDestroy() {
	tmmInstantiated = false;
	delete tmmInstance;
}

bool TileMapManager::tmmGetInstantiated() {
	return tmmInstantiated;
}


vec2 TileMapManager::tmmGetWorldPos(TilePair xyloc) {
	int r = xyloc.first;
	int c = xyloc.second;
	int s = tmmBlockSize;
	return vec2((float)c * s + (float)s / 2, SCREEN_HEIGHT - ((float)r * s + (float)s / 2));
}
TilePair TileMapManager::tmmGetMapLoc(vec2 wpos) {
	int x = (int)wpos.x;
	int y = (int)(SCREEN_HEIGHT - wpos.y);
	int s = tmmBlockSize;
	return TilePair(x/s,y/s);
}


void TileMapManager::tmmLoadMap(int a[MAPSIZE_ROWS][MAPSIZE_COLS]) {
	for (int row = 0; row < MAPSIZE_ROWS;++row) {
		for (int col = 0; col < MAPSIZE_COLS;++col) {
			map[row][col] = a[row][col];
		}
	}
}

void TileMapManager::tmmUpdate() {
}

void TileMapManager::tmmDraw() {

}

void TileMapManager::tmmHandleEvents() {

}

