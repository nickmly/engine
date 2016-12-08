#pragma once
#include <memory>
#include "OpenGLRenderer.h"
#include "GameScene.h"
#include "SDL.h"
#include <iostream>
#include "Clock.h"

class SceneManager
{
	private:

		SceneManager();
		~SceneManager();

	public:
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;

	private:
		//creates points to addresses of main.cpp game loop variables
		OpenGLRenderer *renderer;
		GameScene *currentScene;
		SDL_Event *inputEvent;

		///std::unique_ptr is a smart pointer that destroys the object it point to when the unique_ptr goes out of scope.
		static std::unique_ptr<SceneManager> instance;

		/// Since my destructor is private the template std::unique_ptr needs access so I made it a friend.
		/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
		/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
		friend std::default_delete<SceneManager>;

	private:
		bool isRunning;
		unsigned int fps; /// Frames / second
		vector<GameScene*> SceneList;
		Clock *clock;

	public:

		static SceneManager* getInstance();
		
		//TODO:: optimize reference gathering
		void Initialize(SDL_Event *e, OpenGLRenderer *_renderer, Clock *clock);
		void Run();

		void PreUpdate();
		void Update(const float deltaTime);
		void PostUpdate();

		void OnInput(Uint32 event, SDL_Keycode key);

		void OnMouse(Uint32 event, Uint8 button, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel);

		void End();

		void AddScene(GameScene *scene);
		
		bool sceneChange = false;
		
		unsigned int SceneNumber;
		void SetScene(unsigned int sceneNumber);

		GameScene* GetCurrentScene();

};