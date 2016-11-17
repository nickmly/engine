#pragma once
#include "SimpleModel.h"
#include "GameObject.h"
#include "GeometricShapes.h"
#include "glm.hpp"
#include "glut.h"
#include "SDL.h"
#include "FileReader.h"

class Scene {
public:
	virtual void onCreate() = 0;
	virtual void onStart()=0;
	virtual void onEnd()=0;
	virtual void preRender(float timeSinceLastFrame)=0;
	virtual void render()=0;
	virtual void postRender()=0;
	virtual void update(float deltaTime)=0;
	
	bool started = false;
	bool IsStarted() {
		return started;
	}
};