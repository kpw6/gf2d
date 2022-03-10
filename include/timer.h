#ifndef __TIMER_H__
#define __TIMER_H__

#include <SDL.h>

float deltaTime;

/*
* @brief updates the deltatime
*/
void timer_update();

Uint8 timer_wait(float timeLimit);
#endif