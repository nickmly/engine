#include <SDL.h>
#include "GL\glew.h"
#include <stdio.h>
#include <Windows.h>
#include <Clock.h>
#include <LogManager.h>
#include "MainMenu.h"
//#include <ResourceManager.h>
//#include <Material.h>
#include <sstream>
//#include "TestApp.h"
#include "SceneManager.h"

using namespace std;
const string LOG_THRESHOLD = "NONE"; // Set a threshold for the log file

const char* TITLE = "Window Title";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//TestApp app;
SceneManager *GSM = SceneManager::getInstance();
LogManager *logManager = LogManager::getInstance();

int main(int argc, char** argv) {
	
	logManager->Init(); // Initialize log manager to create a new log file
	logManager->threshold = LOG_THRESHOLD; // Apply the threshold for the logManager (remove this line for no threshold)

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_SetRelativeMouseMode(SDL_TRUE); // lock mouse to window

	SDL_Window* window = SDL_CreateWindow(TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = true;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// main loop variables that will exist throught the game loop
	Clock clock = Clock();
	SDL_Event windowEvent;
	
	//TODO:: next comment, maybe at least to learn what is most efficient by testing
	//renderer created on the heap, it may be more efficient to keep this on the stack if it exists throught the entire program... no clue if im right we should test this out
	OpenGLRenderer *renderer = new OpenGLRenderer();

	//Scene object pointers created in the project testbed all new scenes will inherit from Scene
	//polymorphically assign the created sceen to basetype Scene
	GameScene *mainMenu = new MainMenu(renderer);


	/************NOTE********************* 
	GSM is a SceneManager  is a singleton using unique_ptr
	only one object can reference it at a time, in this case main.cpp
	if multiple objects need to share the reference use shared_ptr instead
	**/
	//Add scenes to the SceneManager 
	GSM->AddScene(mainMenu);

	//Apply game loop variables to GSM
	GSM->Initialize(&windowEvent, renderer, &clock);
	//Start first scene
	GSM->Run();
	//app.onStart();	

	renderer->EnableOpenGL();
	while (true) {
		clock.Tick();
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
				break;
			if (windowEvent.type == SDL_KEYDOWN) {
				GSM->OnInput(windowEvent.type, windowEvent.key.keysym.sym);
				//app.onInput(windowEvent.type, windowEvent.key.keysym.sym, 0, 0);
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
					break;
				if (windowEvent.key.keysym.sym == SDLK_1)
				{
					//use key to test scene at index 0 
					GSM->SetScene(0);
				}
				if (windowEvent.key.keysym.sym == SDLK_2) {
					//use key to test scene at index 1
					GSM->SetScene(1);
				}
			}
			if (windowEvent.type == SDL_KEYUP) {
				GSM->OnInput(windowEvent.type, windowEvent.key.keysym.sym);
				//app.onInput(windowEvent.type, windowEvent.key.keysym.sym, 0, 0);
			}
			if (windowEvent.type == SDL_MOUSEBUTTONDOWN || windowEvent.type == SDL_MOUSEMOTION) {
				GSM->OnMouse(windowEvent.type, windowEvent.button.button, windowEvent.motion.x, windowEvent.motion.y, windowEvent.motion.xrel, windowEvent.motion.yrel);
			}
		}	

		switch (GSM->GetCurrentScene()->GetSceneState()) {
		case(GameScene::SCENE_STATE::PAUSED):
			GSM->GetCurrentScene()->onPause();
			break;
		case(GameScene::SCENE_STATE::RUNNING):
			//render
			GSM->GetCurrentScene()->preRender();
			GSM->GetCurrentScene()->render();
			//update
			GSM->GetCurrentScene()->onUpdate(clock.GetDeltaTime());
			//PostRender **in theory this should be drawing to next buffer ????? **
			GSM->GetCurrentScene()->postRender();
			break;
		case(GameScene::SCENE_STATE::COMPLETE):
			GSM->GetCurrentScene()->onComplete();
			break;
		case(GameScene::SCENE_STATE::QUIT):
			GSM->GetCurrentScene()->onQuit();
			break;
		default:
			break;
		}
		//update everything
		/*app.update(clock.GetDeltaTime());
		app.preRender(clock.GetDeltaTime());
		app.render();*/
		SDL_GL_SwapWindow(window);
		//app.postRender();
		//GSM->postRender();
	}


	//TODO::
	//End all scnes ***not implemented***
	GSM->End();
	//app.onEnd();
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

