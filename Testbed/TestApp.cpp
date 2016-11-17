//#include "TestApp.h"
//#include "GL\glew.h"
//#include <OpenGLRenderer.h>
//#include "ResourceManager.h"
//#include "SimpleModel.h"
//#include "Vertex.h"
//#include "GeometricShapes.h"
//#include "glm.hpp"
//#include "glut.h"
//#include "SDL.h"
//#include "FileReader.h"
//#include "GameObject.h"
//
//OpenGLRenderer* renderer;
//SimpleModel *square, *square2, *light;
//GameObject *player, *ball;
//using namespace std;
//
//void TestApp::onStart()
//{
//	renderer = new OpenGLRenderer();
//
//	//Create a model with these vertices and assign it to a renderer
//	square = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube),
//		*renderer,
//		"bluewall.jpg",
//		"shader.vert",
//		"shader.frag");
//	square2 = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube),
//		*renderer,
//		"container.jpg",
//		"shader2.vert",
//		"shader.frag");
//	light = new SimpleModel(GeometricShapes::GetShape(GeometricShapes::cube), *renderer, "wall.jpg", "lightShader.vert", "lightShader.frag");
//
//	square->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
//	square2->SetScale(glm::vec3(1.0f));
//	//TODO: move bounding box to gameobject class
//	BoundingBox playerBox = BoundingBox(glm::vec3(0.0f, 0.0f, 0.0f));
//	BoundingBox ballBox = BoundingBox(glm::vec3(0.0f, 0.0f, 0.0f));
//
//	player = new GameObject(square, playerBox, *renderer);
//	ball = new GameObject(square2, ballBox, *renderer);
//	
//	ball->SetPosition(glm::vec3(-6.0f, 0.0f, 0.0f));
//	ball->SetAngle(5.0f); // Rotate by 5.0 units each frame
//	
//	renderer->EnableOpenGL();
//}
//
//void TestApp::onEnd()
//{
//	renderer->Destroy();
//}
//
//void TestApp::preRender(double timeSinceLastFrame)
//{
//	renderer->PrepareToRender();
//}
//
//void TestApp::render()
//{
//	player->Render();
//	ball->Render();
//	light->RenderModel();
//	//For some reason this won't work unless there is two rendertext calls?
//	renderer->RenderText("fillertext", 800.0f, 600.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
//	renderer->RenderText("Testing", 0.0f, 16.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//}
//
//void TestApp::update(double deltaTime)
//{
//	//Handle movement
//	player->Update(deltaTime);
//	ball->Update(deltaTime);
//	bool intersecting = player->GetBoundingBox().BoxIntersects(ball->GetBoundingBox());
//	if (intersecting) {
//		player->SetInitialVelocity(-player->GetInitialVelocity());
//	}
//}
//
//void TestApp::postRender()
//{
//
//}
//
////Called from main.cpp
////Handles all input from a keyboard
//void TestApp::onInput(Uint32 event, SDL_Keycode key, int x, int y) {
//
//	switch (event) {
//	case SDL_KEYDOWN:
//		switch (key) {
//		case SDLK_a:
//			player->AddForce(glm::vec3(-15.0f, 0.0f, 0.0f));
//			break;
//		case SDLK_d:
//			player->AddForce(glm::vec3(15.0f, 0.0f, 0.0f));
//			break;
//		case SDLK_w:
//			player->AddForce(glm::vec3(0.0f, 15.0f, 0.0f));
//			break;
//		case SDLK_s:
//			player->AddForce(glm::vec3(0.0f, -15.0f, 0.0f));
//			break;
//		case SDLK_z:
//			glDisable(GL_DEPTH_TEST);
//			break;
//		case SDLK_x:
//			glEnable(GL_DEPTH_TEST);
//			break;
//		}
//		break;
//
//	case SDL_KEYUP:
//		switch (key) {
//		case SDLK_a:
//		case SDLK_d:
//			player->clearForces_X();
//			break;
//		case SDLK_w:
//		case SDLK_s:
//			player->clearForces_Y();
//			break;
//		}
//		break;
//	}
//}
//
//
//
////Called from main.cpp
////Handles all input from a mouse
//void TestApp::onMouse(int button, int state, int x, int y)
//{
//	switch (button) {
//	case GLUT_LEFT_BUTTON:
//		if (state == GLUT_DOWN) {
//
//		}
//		break;
//	}
//}
