#pragma once
#include "LogManager.h"
#include <Engine.h>
#include <Windows.h>
class DemoApp : public Engine
{
public:
	LogManager* logManager = LogManager::getInstance();
	virtual void onStart();
	virtual void onEnd();
	virtual void preRender(double timeSinceLastFrame);
	virtual void render();
	virtual void postRender();
	void onInput(WPARAM keyParam, int x, int y);
	void onMouse(int button, int state, int x, int y);
};

