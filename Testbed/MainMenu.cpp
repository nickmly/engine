#include "MainMenu.h"

using namespace std;

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
	
	mainCamera = Camera(Camera::PROJECTION, 800, 600); // Setup our camera
	mainCamera.fov = 120.0f;
	mainCamera.SetPositionVector(0.0f, -10.0f, 4.0f); // Put camera at this position
	mainCamera.SetTargetVector(0.0f, 0.0f, 0.0f); // Look at this position
	mainCamera.SetUpVector(0.0f, 1.0f, 0.0f); // Camera is pointing up (0,-1,0) for down
	mainCamera.ResizeFrustum(1.0f, 0.1f, 100.0f); // Set up frustum

	
	secondCamera = Camera(Camera::PROJECTION, 800, 600);
	secondCamera.fov = 120.0f;
	secondCamera.SetPositionVector(-15.0f, -10.0f, 4.0f); 
	secondCamera.SetTargetVector(0.0f, 0.0f, 0.0f); 
	secondCamera.SetUpVector(0.0f, 1.0f, 0.0f); 
	secondCamera.ResizeFrustum(1.0f, 0.1f, 100.0f);

	Shader shader = Shader(FileReader::ReadFromFile("shader.vert").c_str(), FileReader::ReadFromFile("shader.frag").c_str());
	customModel = new Model("box2.obj", shader);
	//Create a model with these vertices and assign it to a renderer
	//Models should be initialized when the game is loaded doing this in 
	//loading models in OnStart() would require the creation of possibly really complex models at runtime
	square = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube),
		*renderer,
		"bluewall.jpg",
		"shader.vert",
		"shader.frag"
	);
	square2 = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube),
		*renderer,
		"container.jpg",
		"shader2.vert",
		"shader.frag"
	);
	light = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube), *renderer, "wall.jpg", "lightShader.vert", "lightShader.frag");

	cube = new GameObject(*square);
	cube2 = new GameObject(*square2);
	
}

void MainMenu::onStart()
{
	//use this to assign a camera to the renderer
	renderer->SetActiveCamera(mainCamera);

	// gameObject to scene
	sceneGraph->GetRootSceneNode()->AppendChild(cube->GetSceneNode());
	
	//append 2nd cube to first cube 
	cube->GetSceneNode()->AppendChild(cube2->GetSceneNode());

	//sets local position relative to its parent node
	cube->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	cube2->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));

	started = true;
	
	sceneState = SCENE_STATE::RUNNING;
}

//***********GAME STATES****************//

void MainMenu::onUpdate(float deltaTime)
{
	//sets rotation only on x for parent cube
	cube->SetRotation(glm::vec3(0.0025, 0.0f, 0.0f));
	//sets rotation only on y for child cube which will inherit the rotation of its parent as well
	cube2->SetRotation(glm::vec3(0.0f, 0.0025, 0.0f));

	//For some reason this won't work unless there is two rendertext calls?
	renderer->RenderText("fillertext", 800.0f, 600.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	renderer->RenderText("MainMenu", 0.0f, 16.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
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
}

void MainMenu::render()
{
	//sceneGraph->RenderSceneGraph();
	customModel->Render();
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
			cube->SetPosition(glm::vec3(-0.25f, 0.0f, 0.0f));
			break;
		case SDLK_d:
			cube->SetPosition(glm::vec3(0.25f, 0.0f, 0.0f));
			break;
		case SDLK_w:
			cube->SetPosition(glm::vec3( 0.0f, 0.25f, 0.0f));
			break;
		case SDLK_s:
			cube->SetPosition(glm::vec3( 0.0f, -0.25f, 0.0f));
			break;

	/////////////////************move child node**************////////////////////////
		case SDLK_f:
			cube2->SetPosition(glm::vec3(0.25f, 0.0f, 0.0f));
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
		case SDLK_c:
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
void MainMenu::onMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

		}
		break;
	}
}

//***********************************//