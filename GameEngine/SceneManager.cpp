#include "SceneManager.h"

/// See the header file reguarding unique_ptr
std::unique_ptr<SceneManager> SceneManager::instance(nullptr);

SceneManager* SceneManager::getInstance() {
	if (instance.get() == nullptr) {
		/// I originally set the unique_ptr to be null in the constructor - 
		/// reset() sets the new address
		instance.reset(new SceneManager());
	}
	return instance.get();
}

void SceneManager::Initialize(SDL_Event *e, OpenGLRenderer *_renderer, Clock *_clock) {
	inputEvent = e;
	renderer = _renderer;
	clock = _clock;
	SceneNumber = 0;
}

void SceneManager::Run() {
		//Starts First scene in SceneList
		//SceneNumber defaults to 0;
		currentScene = SceneList.at(SceneNumber);
		currentScene->onStart();
}

void SceneManager::Update(const float deltaTime) {
	//prepCamera
	currentScene->preRender(deltaTime);
	//renderScene
	currentScene->render();
	//updateScene
	currentScene->update(clock->GetDeltaTime());
}

void SceneManager::AddScene(Scene *scene)
{
	SceneList.push_back(scene);
}

void SceneManager::SetScene(int sceneNumber) {
	//changes SceneNumber to desired scene number
	SceneNumber = sceneNumber;
	//sets current scene to desired scene number
	currentScene = SceneList.at(SceneNumber);
	if (!currentScene->IsStarted()) {
		//checks IsStarted in Base Scene.h onStart() only if the scene has not yet been started
		currentScene->onStart();
	}
}

void SceneManager::End() {

}

SceneManager::~SceneManager() {
	renderer->Destroy();
}

SceneManager::SceneManager() {

}