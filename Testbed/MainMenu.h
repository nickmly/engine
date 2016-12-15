#pragma once
///refactor with all scenes these includes into Scene.h
#include <GameScene.h>
#include "SDL.h"
#include "GL\glew.h"
#include <OpenGLRenderer.h>
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Model.h"
#include "SimpleModel.h"
#include "Vertex.h"
#include "GeometricShapes.h"
#include "glm.hpp"
#include "glut.h"
#include "SDL.h"
#include "FileReader.h"
#include "GameObject.h"
#include "SceneGraph.h"
#include "FPS_Camera.h"
#include "TargetCamera.h"
class MainMenu : public GameScene
{
public:
	MainMenu(OpenGLRenderer *_renderer);
	~MainMenu();

private:

	glm::vec3 camRotation;
	//ptr to renderer created in main.cpp
	OpenGLRenderer *renderer;
	//heap variables
	SimpleModel *square, *square2, *light;
	SpriteRenderer *space;

	Model* earthModel, *marsModel, *sunModel, *saturnModel, *neptuneModel, *mercuryModel, *uranusModel, *venusModel, *jupiterModel, *moonModel, *scope;
	Model *fake;
	GameObject *earthObject, *earthRotation;

	GameObject *marsObject, *marsRotation;
	GameObject *sunObject;
	GameObject *saturnObject, *saturnRotation;
	GameObject *neptuneObject, *neptuneRotation;
	GameObject *mercuryObject, *mercuryRotation;
	GameObject *uranusObject, *uranusRotation;
	GameObject *jupiterObject, *jupiterRotation;
	GameObject *venusObject, *venusRotation;

	GameObject *earthMoon, *earthMoonRotation;
	GameObject **marsMoons, **marsMoonRotations;
	GameObject **saturnMoons, **saturnMoonRotations;
	GameObject **jupiterMoons, **jupiterMoonRotations;
	GameObject **uranusMoons, **uranusMoonRotations;
	//MAIN OR INITIAL SCENE CAMERA
	Camera mainCamera;
	Camera secondCamera;
	AbstractCamera *fpsCamera;
	AbstractCamera *targetCamera;
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
	virtual void HandleMouse(Uint32 event, Uint8 button, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel) override;


};



