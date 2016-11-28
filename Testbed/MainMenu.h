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
#include "SceneGraph.h"
class MainMenu : public Scene
{
public:
	MainMenu(OpenGLRenderer *_renderer);
	~MainMenu();

private:
	//ptr to renderer created in main.cpp
	OpenGLRenderer *renderer;
	//heap variables
	SimpleModel *square, *square2, *light;

	GameObject *cube, *cube2;
	//MAIN OR INITIAL SCENE CAMERA
	Camera mainCamera;
	Camera secondCamera;

	SceneGraph *sceneGraph;

public:
	// Inherited via Scene

	//**********PRE SCENE**************//
	virtual void onCreate()override;
	virtual void onStart()override;

	//***********SCENE STATES***********//
	virtual void onUpdate(float deltaTime) override;
	virtual void onPause() override;
	virtual void onComplete() override;
	virtual void onQuit() override;
	
	//***********RENDERING************//
	virtual void preRender() override;
	virtual void render() override;
	virtual void postRender() override;
	
	//***********INPUT**************//
	virtual void HandleInput(Uint32 event, SDL_Keycode key) override;
	void onMouse(int button, int state, int x, int y);
};



