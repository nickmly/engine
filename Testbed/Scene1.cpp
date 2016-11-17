#include "Scene1.h"

#include "GL\glew.h"
#include <OpenGLRenderer.h>
#include "ResourceManager.h"
#include "SimpleModel.h"
#include "Vertex.h"
#include "GeometricShapes.h"
#include "glm.hpp"
#include "glut.h"
#include "SDL.h"
#include "FileReader.h"
#include "GameObject.h"


using namespace std;


Scene1::Scene1(OpenGLRenderer *_renderer)
{
	renderer = _renderer;
	onCreate();
}

Scene1::~Scene1()
{
	light->~SimpleModel();
}

void Scene1::onCreate()
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
	//square2 = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube),
	//	*renderer,
	//	"container.jpg",
	//	"shader2.vert",
	//	"shader.frag"
	//);
	light = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube), *renderer, "wall.jpg", "lightShader.vert", "lightShader.frag");
}

void Scene1::onStart()
{
	//	renderer = new OpenGLRenderer();
	square->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
	//square2->SetScale(glm::vec3(1.0f));
	light->SetScale(glm::vec3(1.0f));
	//TODO: move bounding box to gameobject class
	playerBox = new BoundingBox(square->GetScale());
	//ballBox = new BoundingBox(square->GetScale());

	//creates a game object using the previously initialized Models5
	//TODO:: move the above bounding box to GameObject a construction option
	player = new GameObject(*square, *playerBox, *renderer);
	//ball = new GameObject(*square2, *ballBox, *renderer);

	//ball->SetPosition(glm::vec3(-6.0f, 0.0f, 0.0f));
	//ball->SetAngle(5.0f); // Rotate by 5.0 units each frame
	//renderer->EnableOpenGL();
	started = true;
}

void Scene1::onEnd()
{
	renderer->Destroy();
}

void Scene1::preRender(float timeSinceLastFrame)
{
	renderer->PrepareToRender();
}

void Scene1::render()
{
	player->Render();
	//ball->Render();
	light->RenderModel();
	//For some reason this won't work unless there is two rendertext calls?
	renderer->RenderText("fillertext", 800.0f, 600.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
	renderer->RenderText("Scene1", 0.0f, 16.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Scene1::update(float deltaTime)
{
	//Handle movement
	player->Update(deltaTime);
	//ball->Update(deltaTime);
	//bool intersecting = player->GetBoundingBox()->BoxIntersects(*ball->GetBoundingBox());
	//if (intersecting) {
	//	player->SetInitialVelocity(-player->GetInitialVelocity());
	//}
}
void Scene1::postRender()
{

}

//Called from main.cpp
//Handles all input from a keyboard
void Scene1::onInput(Uint32 event, SDL_Keycode key) {

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
void Scene1::onMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

		}
		break;
	}
}
