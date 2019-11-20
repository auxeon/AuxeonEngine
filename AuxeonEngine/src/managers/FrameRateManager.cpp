#include "../inc/managers/FrameRateManager.h"

FrameRateManager* FrameRateManager::fpsInstance = NULL;
bool FrameRateManager::fpsInstantiated = false;
float FrameRateManager::fpsCap;
float FrameRateManager::fpsFrameTime;

FrameRateManager::FrameRateManager() : fpsTimeScale(1.0f) {
	fpsReset();
}

FrameRateManager::~FrameRateManager() {

}

FrameRateManager* FrameRateManager::fpsCreate() {
	if (!fpsInstantiated) {
		fpsInstance = new FrameRateManager;
		fpsInstantiated = true;
	}
	return fpsInstance;
}

void FrameRateManager::fpsDestroy() {
	fpsInstantiated = false;
	delete fpsInstance;
}

bool FrameRateManager::fpsGetInstantiated() {
	return fpsInstantiated;
}

void FrameRateManager::fpsReset() {
	fpsElapsedTicks = 0.0f;
	fpsDeltaTime = 0.0f;
	fpsStartTicks = SDL_GetTicks();
}

void FrameRateManager::fpsUpdate() {
	fpsElapsedTicks = SDL_GetTicks() - fpsStartTicks;

	// to get time in seconds, as ticks is in milliseconds 
	// all physics based systems are usually in the 
	// fpsTimeScale is useful in creating slow-mo effects
	fpsDeltaTime = fpsElapsedTicks / (1000.0f * fpsTimeScale);
}

float FrameRateManager::fpsGetDeltaTime() {
	return fpsDeltaTime;
}

float FrameRateManager::fpsGetTimeScale() {
	return fpsTimeScale;
}

void FrameRateManager::fpsSetTimeScale(float timescale) {
	fpsTimeScale = timescale;
}

void FrameRateManager::fpsDraw() {

}

void FrameRateManager::fpsHandleEvents() {

}

float FrameRateManager::fpsGetFPS() {
	return fpsCap;
}

float FrameRateManager::fpsGetFrameTimeCap() {
	return fpsFrameTime;
}

void FrameRateManager::fpsSetFPS(float fpscap) {
	fpsCap = fpscap;
	fpsFrameTime = 1 / fpsCap;
}