#pragma once
#include "SimpleModel.h"
#include "GameObject.h"
#include "GeometricShapes.h"
#include "glm.hpp"
#include "glut.h"
#include "SDL.h"
#include "FileReader.h"

class GameScene {

public:
	enum SCENE_STATE {
		RUNNING,
		PAUSED,
		COMPLETE,
		QUIT
	};
protected:
	SCENE_STATE sceneState;
	bool started = false;
public:
	//STORE SCENE IN MEMORY
	virtual void onCreate() = 0;

	//INITIALIZE SCENE FOR FIRST USE // includes updating: info from previous scene, object positions, camera pos/proj, checkpoints etc...
	virtual void onStart() = 0;

	//UPDATE SCENE // u
	virtual void onUpdate(float deltaTime) = 0;
	
	//PAUSE MENU 
	virtual void onPause() = 0;
	
	//SCENE COMPLETION// SAVE AND TRANSFER GAME INFORMATION TO NEXT SCENE
	virtual void onComplete() = 0;
	
	//INCASE OF RAGE QUIT// MID SCENE APP EXIT
	virtual void onQuit() = 0;

	//Rendering
	
	//setup renderer settings for frame In OpenGL this includes depth test/blend/ glEnable(functions)
	//unecessary expense now, but we may want to manipulate these settings later
	virtual void preRender() = 0;
	
	//render frame
	virtual void render() = 0;
	
	//disable render settings for new frame settings
	virtual void postRender() = 0;
	
	//Manage Scene Input
	//TODO:: creat input manager class and place it into SceneManager to delegate scene recieving input
	virtual void HandleInput(Uint32 event, SDL_Keycode key) = 0;
	virtual void HandleMouse(Uint32 event, Uint8 button, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel) = 0;

	//Maniupulate SceneState
	void SetSceneState(SCENE_STATE type) {
		sceneState = type;
	}
	SCENE_STATE GetSceneState() {
		return sceneState;
	}

	//for checking if the scene has been started once already// if not then initialize onStart();
	bool IsStarted() {
		return started;
	}

};