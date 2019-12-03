#pragma once

#ifndef FRAMERATEMANAGER_H
#define FRAMERATEMANAGER_H

#include "../libs/SDL2-2.0.10/include/SDL.h"

class FrameRateManager
{
public:
	static FrameRateManager* fpsCreate();
	static void fpsDestroy();
	static bool fpsGetInstantiated();
	static float fpsGetFrameTimeCap();
	static float fpsGetFPS();
	static void fpsSetFPS(float fpscap);
	
	void fpsReset();
	float fpsGetDeltaTime();
	void fpsSetTimeScale(float scaletime);
	float fpsGetTimeScale();

	void fpsUpdate();
	void fpsDraw();
	void fpsHandleEvents();
	
private:

	
	static FrameRateManager* fpsInstance;
	static bool fpsInstantiated;
	static float fpsCap;
	static float fpsFrameTime;

	unsigned int fpsStartTicks;
	unsigned int fpsElapsedTicks;

	float fpsDeltaTime;
	float fpsTimeScale;


private:
	FrameRateManager();
	~FrameRateManager();
	bool fpsInit();
};

#endif

