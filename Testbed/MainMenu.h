#pragma once
///refactor with all scenes these includes into Scene.h
#include <Scene.h>
#include "SDL.h"
#include "GL\glew.h"
#include <OpenGLRenderer.h>
#include "ResourceManager.h"
#include "SimpleModel.h"
#include "Vertex.h"
#include "GeometricShapes.h"
#include "glm.hpp"
#include "glut.h"
#include "SDL.h"
#include "FileReader.h"
#include "GameObject.h"

class MainMenu : public Scene
{
public:
	virtual void onCreate();
	virtual void onStart();
	virtual void onEnd();
	virtual void preRender(float timeSinceLastFrame);
	virtual void render();
	virtual void postRender();
	virtual void update(float deltaTime);
	virtual void onInput(Uint32 event, SDL_Keycode key);

public:
	MainMenu(OpenGLRenderer *_renderer);
	~MainMenu();
	void onMouse(int button, int state, int x, int y);

private:
	//ptr to renderer created in main.cpp
	OpenGLRenderer *renderer;

	//heap variables
	SimpleModel *square, *square2, *light;
	GameObject *player, *ball;
	BoundingBox *playerBox;
	BoundingBox *ballBox;
};



