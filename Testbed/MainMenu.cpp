#include "MainMenu.h"
#include "Skybox.h"


using namespace std;
float delta = -1.0f;

Skybox* skybox;
MainMenu::MainMenu(OpenGLRenderer *_renderer)
{
	renderer = _renderer;
	sceneGraph = new SceneGraph();
	modelManager = ResourceManager<Model>();
	fake = new Model();
	onCreate();
}

MainMenu::~MainMenu()
{
	//light is not a gameobject which destroyes its own models so destructor must be called
	light->~SimpleModel();
}

//*************PRE SCENE*************//

void MainMenu::onCreate()
{	
	fpsCamera = new FPS_Camera();
	fpsCamera->SetupProjection(120.0f, 800 / 600, 0.1f, 1000.0f);
	fpsCamera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	
	Shader shader = Shader(FileReader::ReadFromFile("model_shader.vert").c_str(), 
		FileReader::ReadFromFile("model_shader.frag").c_str());
	Shader sunShader = Shader(FileReader::ReadFromFile("model_shader_nolight.vert").c_str(), FileReader::ReadFromFile("model_shader.frag").c_str());
	
	//skyboxModel = new Model("assets/models/skybox.obj", sunShader, *renderer);


	skullModel = new Model("assets/models/skull.obj", shader, *renderer);
	modelManager.Put(std::string("skull"), skullModel);
	skullObject = new GameObject(*modelManager.Get(std::string("skull")));

	//skyboxObject = new GameObject(*skyboxModel);
	
}

void MainMenu::onStart()
{
	//use this to assign a camera to the renderer
	renderer->SetActiveCam(*fpsCamera);

	sceneGraph->AppendSceneNode(skullObject->GetSceneNode());
	//skyboxObject->SetPosition(glm::vec3(0.0f));
	skullObject->SetPosition(glm::vec3(0.0f, 0.0f, 30.0f));
	//skyboxObject->SetScale(glm::vec3(500.0f));
	started = true;
	
	std::vector<char*> images;
	images.push_back("assets/textures/right.jpg");
	images.push_back("assets/textures/left.jpg");
	images.push_back("assets/textures/top.jpg");
	images.push_back("assets/textures/bottom.jpg");
	images.push_back("assets/textures/back.jpg");
	images.push_back("assets/textures/front.jpg");
	skybox = new Skybox(*renderer, images);

	sceneState = SCENE_STATE::RUNNING;
}

//***********GAME STATES****************//

void MainMenu::onUpdate(float deltaTime)
{
	delta = deltaTime;

	skullObject->SetRotation(glm::vec3(0.0f, deltaTime, 0.0f));
	//For some reason this won't work unless there is two rendertext calls?
	renderer->RenderText("fillertext", 800.0f, 600.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	renderer->RenderText("MainMenu", 0.0f, 16.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	fpsCamera->Rotate(camRotation.x, camRotation.y, camRotation.z);

}

void MainMenu::onPause()
{
}

void MainMenu::onComplete()
{
}

void MainMenu::onQuit()
{
}


//*************RENDERING**************//

void MainMenu::preRender()
{
	renderer->PrepareToRender();	
	skybox->Render();
}

void MainMenu::render()
{	
	//skyboxObject->GetSceneNode()->RenderSceneNode();
	sceneGraph->RenderSceneGraph();
}
 
void MainMenu::postRender()
{
	//skybox->Render();
	renderer->PostRender();
}

//*************INPUT*****************//

//TODO::include in inpute manager
void MainMenu::HandleInput(Uint32 event, SDL_Keycode key)
{
	switch (event) {
	case SDL_KEYDOWN:
		switch (key) {
		case SDLK_a:
			fpsCamera->Strafe(-0.850f);
			break;
		case SDLK_d:
			fpsCamera->Strafe(0.850f);
			break;
		case SDLK_w:
			fpsCamera->Walk(0.850f);
			break;
		case SDLK_s:
			fpsCamera->Walk(-0.850f);
			break;
		case SDLK_e:
			fpsCamera->Lift(0.25f);
			break;
		case SDLK_c:
			fpsCamera->Lift(-0.25f);
			break;
	/////////////////************move child node**************////////////////////////
		case SDLK_f:
	
			break;
	//////////////////////////////////////////////////////
			//TESTSCENE STATE
		case SDLK_z:
			//test paused state
			sceneState=SCENE_STATE::PAUSED;
			break;
		case SDLK_x:
			//test running state
			sceneState = SCENE_STATE::RUNNING;
			break;
			////////////TEST CAMERA SWITCH
		case SDLK_g:
			
			break;
		case SDLK_v:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (key) {
		case SDLK_a:
			break;
		case SDLK_d:
			break;
		case SDLK_w:
			break;
		case SDLK_s:
			break;
		case SDLK_f:

			break;
		}
		break;
	}
}

void MainMenu::HandleMouse(Uint32 event, Uint8 button, Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel)
{
	switch (event) {
	case SDL_MOUSEBUTTONDOWN:
		if (button == SDL_BUTTON_LEFT) {

		}
		if (button == SDL_BUTTON_RIGHT) {

		}
		break;
	case SDL_MOUSEMOTION:
		camRotation.x += (xrel * 40.0f * delta) * -1.0f;
		camRotation.y += yrel * 40.0f * delta;
		break;
	}
}


//***********************************//