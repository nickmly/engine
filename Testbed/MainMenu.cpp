#include "MainMenu.h"
using namespace std;

MainMenu::MainMenu(OpenGLRenderer *_renderer)
{
	renderer = _renderer;
	//oncreate happens on creation and stores all models and shaders on the heap
	//doing this before the game loop begins should provide a more efficient runtime
	onCreate();
}

MainMenu::~MainMenu()
{
	//light is not a gameobject which destroyes its own models so destructor must be called
	light->~SimpleModel();
}

void MainMenu::onCreate()
{
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
}

void MainMenu::onStart()
{
	//renderer = new OpenGLRenderer();
	square->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	square2->SetScale(glm::vec3(1.0f));
	light->SetScale(glm::vec3(1.0f));

	//TODO: move bounding box to gameobject class
    playerBox = new BoundingBox(square->GetScale());
	ballBox = new BoundingBox(square->GetScale());

	//creates a game object using the previously initialized Models5
	//TODO:: move the above bounding box to GameObject a construction option
	player = new GameObject(*square, *playerBox, *renderer);
	ball = new GameObject(*square2, *ballBox, *renderer);

	ball->SetPosition(glm::vec3(-6.0f, 0.0f, 0.0f));
	ball->SetAngle(5.0f); // Rotate by 5.0 units each frame

	started = true;
}

void MainMenu::onEnd()
{
	renderer->Destroy();
}

void MainMenu::preRender(float timeSinceLastFrame)
{
	renderer->PrepareToRender();
}

void MainMenu::render()
{
	renderer->PrepareToRender();
	
	player->Render();
	ball->Render();
	light->RenderModel();
	//For some reason this won't work unless there is two rendertext calls?
	renderer->RenderText("fillertext", 800.0f, 600.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	renderer->RenderText("Testing", 0.0f, 16.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void MainMenu::update(float deltaTime)
{
	//Handle movement
	player->Update(deltaTime);
	ball->Update(deltaTime);
	bool intersecting = player->GetBoundingBox()->BoxIntersects(*ball->GetBoundingBox());
	if (intersecting) {
		player->SetInitialVelocity(-player->GetInitialVelocity());
	}
}

void MainMenu::postRender()
{

}
//Handles all input from a keyboard
//TODO:: creat input manager class and place it into SceneManager to delegate scene recieving input
void MainMenu::onInput(Uint32 event, SDL_Keycode key, int x, int y) {

	switch (event) {
	case SDL_KEYDOWN:
		switch (key) {
		case SDLK_a:
			player->AddForce(glm::vec3(-15.0f, 0.0f, 0.0f));
			break;
		case SDLK_d:
			player->AddForce(glm::vec3(15.0f, 0.0f, 0.0f));
			break;
		case SDLK_w:
			player->AddForce(glm::vec3(0.0f, 15.0f, 0.0f));
			break;
		case SDLK_s:
			player->AddForce(glm::vec3(0.0f, -15.0f, 0.0f));
			break;
		case SDLK_z:
			glDisable(GL_DEPTH_TEST);
			break;
		case SDLK_x:
			glEnable(GL_DEPTH_TEST);
			break;
		}
		break;

	case SDL_KEYUP:
		switch (key) {
		case SDLK_a:
		case SDLK_d:
			player->clearForces_X();
			break;
		case SDLK_w:
		case SDLK_s:
			player->clearForces_Y();
			break;
		}
		break;
	}
}



//Called from main.cpp
//Handles all input from a mouse
//TODO::include in inpute manager
void MainMenu::onMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

		}
		break;
	}
}
