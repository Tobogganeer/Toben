#pragma once

#include "Graphics.h"
#include <string>

class Display
{
public:
	Display(const Display&) = delete;

	inline static int GetWidth() { return width; }
	inline static int GetHeight() { return height; }
	static GLFWwindow* GetWindow();
	static void Resize(int width, int height);

	bool Create(int width, int height, const char* title, bool vsync = false);
	Display();
	~Display();
private:
	static Display instance;
	static GLFWwindow* window;
	static int width, height;
	static void glErrorCallback(int error, const char* description);
};

