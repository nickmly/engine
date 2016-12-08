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
		//Starts First scene in SceneList //default SceneNumber is 0
		currentScene = SceneList.at(SceneNumber);
		currentScene->onStart();
}

void SceneManager::PreUpdate()
{
		currentScene->preRender();
}

void SceneManager::Update(const float deltaTime) {
	//renderScene
	currentScene->render();
	//updateScene
	currentScene->onUpdate(clock->GetDeltaTime());
}

void SceneManager::PostUpdate()
{
}

void SceneManager::OnInput(Uint32 event, SDL_Keycode key)
{
	currentScene->HandleInput(event, key);
}

void SceneManager::OnMouse(Uint32 event, Uint8 button, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel)
{
	currentScene->HandleMouse(event, button, x, y, xrel, yrel);
}

void SceneManager::AddScene(GameScene *scene)
{
	SceneList.push_back(scene);
}

void SceneManager::SetScene(unsigned int sceneNumber) {
	//changes SceneNumber to desired scene number
	SceneNumber = sceneNumber;
	//sets current scene to desired scene number
	currentScene = SceneList.at(SceneNumber);
	if (!currentScene->IsStarted()) {
		//checks IsStarted in Base Scene.h onStart() only if the scene has not yet been started
		currentScene->onStart();
	}
}

GameScene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

void SceneManager::End() {

}

SceneManager::~SceneManager() {
	renderer->Destroy();
}

SceneManager::SceneManager() {

}