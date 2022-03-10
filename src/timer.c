#include "timer.h"

#include "simple_logger.h"

static Uint32 lastTime = 0;
static Uint32 startTime;

void timer_update() {
	startTime = SDL_GetTicks();
	deltaTime = (double)(startTime - lastTime)*60/1000;
	lastTime = startTime;
}

Uint8 timer_wait(float timeLimit) {
	Uint32 time = SDL_GetTicks64();
}
