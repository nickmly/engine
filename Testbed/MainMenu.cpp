#include "MainMenu.h"

using namespace std;
float delta = -1.0f;
MainMenu::MainMenu(OpenGLRenderer *_renderer)
{
	renderer = _renderer;
	sceneGraph = new SceneGraph();

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
	
	//mainCamera = Camera(Camera::PROJECTION, 800, 600); // Setup our camera
	//mainCamera.fov = 120.0f;
	//mainCamera.SetPositionVector(0.0f, -10.0f, 4.0f); // Put camera at this position
	//mainCamera.SetTargetVector(0.0f, 0.0f, 0.0f); // Look at this position
	//mainCamera.SetUpVector(0.0f, 1.0f, 0.0f); // Camera is pointing up (0,-1,0) for down
	//mainCamera.ResizeFrustum(1.0f, 0.1f, 100.0f); // Set up frustum
	
	//
	//secondCamera = Camera(Camera::PROJECTION, 800, 600);
	//secondCamera.fov = 120.0f;
	//secondCamera.SetPositionVector(0.0f, 20.0f, 4.0f); 
	//secondCamera.SetTargetVector(0.0f, 0.0f, 0.0f); 
	//secondCamera.SetUpVector(0.0f, 1.0f, 0.0f); 
	//secondCamera.ResizeFrustum(1.0f, 0.1f, 100.0f);

	fpsCamera = new FPS_Camera();
	fpsCamera->SetupProjection(120.0f, 800 / 600, 0.1f, 1000.0f);
	fpsCamera->SetPosition(glm::vec3(0.0f, 1, -10));

	Shader shader = Shader(FileReader::ReadFromFile("newshader.vert").c_str(), FileReader::ReadFromFile("newshader.frag").c_str());
	
	earthModel = new Model("assets/planets/earth.obj", shader, *renderer);
	earthObject = new GameObject(*earthModel);
	marsModel = new Model("assets/planets/mars.obj", shader, *renderer);
	marsObject = new GameObject(*marsModel);
	scope = new Model("box.obj", shader, *renderer);
	light = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube), *renderer, "wall.jpg", "lightShader.vert", "lightShader.frag");
	

	Shader spriteShader = Shader(FileReader::ReadFromFile("UI_shader.vert").c_str(), FileReader::ReadFromFile("UI_shader.frag").c_str());
	space = new SpriteRenderer(spriteShader, "assets/planets/space.png");
}

void MainMenu::onStart()
{
	//use this to assign a camera to the renderer
	//renderer->SetActiveCamera(mainCamera);
	renderer->SetActiveCam(*fpsCamera);
	
	// gameObject to scene
	sceneGraph->GetRootSceneNode()->AppendChild(earthObject->GetSceneNode());
	
	//append 2nd cube to first cube 
	earthObject->GetSceneNode()->AppendChild(marsObject->GetSceneNode());

	//sets local position relative to its parent node
	earthObject->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	marsObject->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));

	started = true;
	
	sceneState = SCENE_STATE::RUNNING;	
}

//***********GAME STATES****************//

void MainMenu::onUpdate(float deltaTime)
{
	delta = deltaTime;
	//sets rotation only on x for parent cube
	earthObject->SetRotation(glm::vec3(0.0025, 0.0f, 0.0f));
	//sets rotation only on y for child cube which will inherit the rotation of its parent as well
	marsObject->SetRotation(glm::vec3(0.0f,0.0025f, 0.0f));
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
	space->DrawSprite(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f);
}

void MainMenu::render()
{	
	sceneGraph->RenderSceneGraph();
}

void MainMenu::postRender()
{
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
			//earthObject->SetPosition(glm::vec3(-0.25f, 0.0f, 0.0f));
			fpsCamera->Strafe(-1.0f);
			break;
		case SDLK_d:
			//earthObject->SetPosition(glm::vec3(0.25f, 0.0f, 0.0f));
			fpsCamera->Strafe(1.0f);
			break;
		case SDLK_w:
			//earthObject->SetPosition(glm::vec3( 0.0f, 0.25f, 0.0f));
			fpsCamera->Walk(1.0f);
			break;
		case SDLK_s:
			//earthObject->SetPosition(glm::vec3( 0.0f, -0.25f, 0.0f));
			fpsCamera->Walk(-1.0f);
			break;
		case SDLK_e:
			fpsCamera->Lift(0.25f);
			break;
		case SDLK_c:
			fpsCamera->Lift(-0.25f);
			break;
	/////////////////************move child node**************////////////////////////
		case SDLK_f:
			marsObject->SetPosition(glm::vec3(0.25f, 0.0f, 0.0f));
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
			renderer->SetActiveCamera(secondCamera);
			break;
		case SDLK_v:
			renderer->SetActiveCamera(mainCamera);
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
		camRotation.x += (xrel * 50.0f * delta) * -1.0f;
		camRotation.y += yrel * 50.0f * delta;		
		break;
	}
}


//***********************************//