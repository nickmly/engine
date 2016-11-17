#pragma once
#include <Scene.h>
#include "SDL.h"

class Scene1 : public Scene
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
	Scene1(OpenGLRenderer *_renderer);
	~Scene1();
	void onMouse(int button, int state, int x, int y);

private:
	//ptr to renderer created in main.cpp
	OpenGLRenderer *renderer;

	//heap variables
	SimpleModel *square, *light;
	GameObject *player;
	BoundingBox *playerBox;
};
