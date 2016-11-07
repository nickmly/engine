#include <SDL.h>
#include "GL\glew.h"
#include <stdio.h>
#include <Windows.h>
#include <Clock.h>
#include <LogManager.h>
//#include <ResourceManager.h>
//#include <Material.h>
#include <sstream>
#include "TestApp.h"

using namespace std;
const string LOG_THRESHOLD = "NONE"; // Set a threshold for the log file

const char* TITLE = "Window Title";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

TestApp app;
LogManager *logManager = LogManager::getInstance();

int main(int argc, char** argv) {

	logManager->Init(); // Initialize log manager to create a new log file
	logManager->threshold = LOG_THRESHOLD; // Apply the threshold for the logManager (remove this line for no threshold)

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


	SDL_Window* window = SDL_CreateWindow(TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = true;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Clock clock;
	//ResourceManager<Material> manager;
	//Material mat = Material();
	//manager.Put(string("MAT_01"), &mat);
	//
	//Material* getMat = manager.Get(string("MAT_01"));
	
	app.onStart();	

	SDL_Event windowEvent;
	while (true) {
		clock.Tick();
		
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
				break;
			if (windowEvent.type == SDL_KEYDOWN) {
				app.onInput(windowEvent.type, windowEvent.key.keysym.sym, 0, 0);
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
					break;
			}
			if (windowEvent.type == SDL_KEYUP) {
				app.onInput(windowEvent.type, windowEvent.key.keysym.sym, 0, 0);
			}
		}	
		app.update(clock.GetDeltaTime());
		app.preRender(clock.GetDeltaTime());
		app.render();
		SDL_GL_SwapWindow(window);
		app.postRender();
	}

	app.onEnd();
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}

