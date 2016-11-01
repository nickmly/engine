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

OpenGLRenderer renderer;
SimpleModel square;
using namespace std;

void TestApp::onStart()
{
	//TODO: Move this to renderer
	//Load shaders
	ShaderLoader shaderLoader = ShaderLoader();
	shaderLoader.LoadShader(GL_VERTEX_SHADER,
		FileReader::ReadFromFile("shader.vert"));
	shaderLoader.LoadShader(GL_FRAGMENT_SHADER,
		FileReader::ReadFromFile("shader.frag"));
	renderer.UseProgram(shaderLoader.GetProgram());
	//
	
	//Add 4 vertices to our vector
	vector<Vertex> verts;

	//////Front
	//verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(-0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));

	////Right
	//verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));

	////Back
	//verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(-0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));

	////Left
	//verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(-0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));
	//verts.insert(verts.end(), Vertex(-0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));


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
		verts.insert(verts.end(), Vertex(1, 0, 0, 0, Vertex::COLOR));
		verts.insert(verts.end(), Vertex(0, 1, 0, 0, Vertex::COLOR));
		verts.insert(verts.end(), Vertex(0, 0, 1, 0, Vertex::COLOR));
	}
	
	//Add texture coords to our vector
	/*for (int i = 0; i < 12; i++) 
	{
		verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		verts.insert(verts.end(), Vertex(1.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		verts.insert(verts.end(), Vertex(1.0f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));
	}*/
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
	square = SimpleModel(verts, renderer);
}

void TestApp::onEnd()
{
	renderer.Destroy();
}

void TestApp::preRender(double timeSinceLastFrame)
{
}

void TestApp::render()
{
	//Render square	
	square.RenderModel();
}

void TestApp::update(double deltaTime)
{
	//Handle movement
	square.transform = glm::translate(square.transform, glm::vec3(square.movement.x * deltaTime,
																	square.movement.y * deltaTime,
																	square.movement.z * deltaTime));
}

void TestApp::postRender()
{
}

//Called from main.cpp
//Handles all input from a keyboard
void TestApp::onInput(Uint32 event, SDL_Keycode key, int x, int y) {
	switch (event) {
	case SDL_KEYDOWN:
		switch (key) {
		case SDLK_a:
			square.movement.x = -6.0f;
			break;
		case SDLK_d:
			square.movement.x = 6.0f;
			break;
		case SDLK_w:
			square.movement.y = 6.0f;
			break;
		case SDLK_s:
			square.movement.y = -6.0f;
			break;
		}
		break;

	case SDL_KEYUP:
		switch (key) {
		case SDLK_a:
		case SDLK_d:
			square.movement.x = 0.0f;
			break;
		case SDLK_w:
		case SDLK_s:
			square.movement.y = 0.0f;
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
