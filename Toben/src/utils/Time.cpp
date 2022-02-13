#include "Time.h"
#include <GLFW/glfw3.h>

float Time::time() { return _time; }
float Time::deltaTime() { return _deltaTime; }
int Time::frameCount() { return _frameCount; }

float Time::_time = 0;
float Time::_deltaTime = 0;
int Time::_frameCount = 0;

void Time::Tick()
{
	float newTime = glfwGetTime();
	_deltaTime = newTime - _time;
	_time = newTime;
	_frameCount++;
}