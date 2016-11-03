#include "TestApp.h"
#include "GL\glew.h"
#include <OpenGLRenderer.h>
#include "ResourceManager.h"
#include "SimpleModel.h"
#include "Vertex.h"
#include "ShaderLoader.h"
#include "FileReader.h"
#include "glm.hpp"
#include "glut.h"
#include "GameObject.h"

OpenGLRenderer* renderer;
SimpleModel *square, *square2;

GameObject player, ball;
using namespace std;

void TestApp::onStart()
{
	renderer = new OpenGLRenderer();
	//TODO: Move this to renderer
	//Load shaders
	ShaderLoader shaderLoader = ShaderLoader();
	shaderLoader.LoadShader(GL_VERTEX_SHADER,
		FileReader::ReadFromFile("shader.vert"));
	shaderLoader.LoadShader(GL_FRAGMENT_SHADER,
		FileReader::ReadFromFile("shader.frag"));
	renderer->UseProgram(shaderLoader.GetProgram());
	//
	
	//Add 4 vertices to our vector
	vector<Vertex> verts;

	//Left
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//

	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

	//Right
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

	verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));//

	//Back
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//

	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));//

	//Front
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

	verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//


	//Bottom
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//triangle 1
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//

	verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//triangle 2
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));//

	//Top
	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

	verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
	verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//



	//Add colors to our vector
	for (int i = 0; i < 12; i++) {
		verts.insert(verts.end(), Vertex(1, 1, 1, 0, Vertex::COLOR));
		verts.insert(verts.end(), Vertex(1, 1, 0, 0, Vertex::COLOR));
		verts.insert(verts.end(), Vertex(1, 1, 1, 0, Vertex::COLOR));
	}
	
	//TODO: store texture info into a simple model so renderer doesn't have to do it
	verts.insert(verts.end(), Vertex(0.0f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.0f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.0f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.0f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.33f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.66f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE)); 

	verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(1.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

	verts.insert(verts.end(), Vertex(1.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(1.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));

	//Create a model with these vertices and assign it to a renderer
	square = new SimpleModel(verts, *renderer);
	square2 = new SimpleModel(verts, *renderer);


	// don't know how to update these over time?
	BoundingSphere playerSphere = BoundingSphere(glm::vec3(0.0f), 1.5f);
	BoundingSphere ballSphere = BoundingSphere(glm::vec3(0.0f), 1.5f);

	player = GameObject(square, playerSphere, *renderer);
	ball = GameObject(square2, ballSphere, *renderer);

	ball.SetPosition(glm::vec3(-4.0f, 0.0f, 0.0f));

	ball.SetAngle(5.0f); // Rotate by 5.0 units each frame
	renderer->EnableOpenGL();
}

void TestApp::onEnd()
{
	renderer->Destroy();
}

void TestApp::preRender(double timeSinceLastFrame)
{
	renderer->PrepareToRender();
}

void TestApp::render()
{
	player.Render();
	ball.Render();	
}

void TestApp::update(double deltaTime)
{
	//Handle movement
	player.Update(deltaTime);
	ball.Update(deltaTime);

	if (player.GetSphere().Intersect(ball.GetSphere())) {
		printf("Collision\n");
	}
}

void TestApp::postRender()
{
	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

//Called from main.cpp
//Handles all input from a keyboard
void TestApp::onInput(Uint32 event, SDL_Keycode key, int x, int y) {
	glm::vec3 newAcceleration;
	switch (event) {
	case SDL_KEYDOWN:
		switch (key) {
		case SDLK_a:
			newAcceleration = player.GetAcceleration();
			newAcceleration.x = -12.0f;
			player.SetAcceleration(newAcceleration);
			break;
		case SDLK_d:
			newAcceleration = player.GetAcceleration();
			newAcceleration.x = 12.0f;
			player.SetAcceleration(newAcceleration);
			break;
		case SDLK_w:
			newAcceleration = player.GetAcceleration();
			newAcceleration.y = 12.0f;
			player.SetAcceleration(newAcceleration);
			break;
		case SDLK_s:
			newAcceleration = player.GetAcceleration();
			newAcceleration.y = -12.0f;
			player.SetAcceleration(newAcceleration);
			break;
		}
		break;

	case SDL_KEYUP:
		switch (key) {
		case SDLK_a:
		case SDLK_d:
			newAcceleration = player.GetAcceleration();
			newAcceleration.x = 0.0f;
			player.SetAcceleration(newAcceleration);
			break;
		case SDLK_w:
		case SDLK_s:
			newAcceleration = player.GetAcceleration();
			newAcceleration.y = 0.0f;
			player.SetAcceleration(newAcceleration);
			break;
		}
		break;
	}

}

//Called from main.cpp
//Handles all input from a mouse
void TestApp::onMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

		}
		break;
	}
}
