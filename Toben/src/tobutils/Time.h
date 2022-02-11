#pragma once
class Time
{
public:
	static float time();
	static float deltaTime();
	static int frameCount();
	static void Init();
	static void Tick();
private:
	static float _time;
	static float _deltaTime;
	static int _frameCount;
};

