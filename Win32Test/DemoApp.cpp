#include "DemoApp.h"
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
void DemoApp::onStart()
{
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
	
	////Front
	verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));

	//Right
	verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));

	//Back
	verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));

	//Left
	verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-0.5f, 0.5f, -0.5f, 0.0f, Vertex::POSITION));
	verts.insert(verts.end(), Vertex(-0.5f, -0.5f, -0.5f, 0.0f, Vertex::POSITION));

	//Add colors to our vector
	verts.insert(verts.end(), Vertex(1, 0, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 1, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 0, 1, 0, Vertex::COLOR));

	verts.insert(verts.end(), Vertex(1, 0, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 1, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 0, 1, 0, Vertex::COLOR));

	verts.insert(verts.end(), Vertex(1, 0, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 1, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 0, 1, 0, Vertex::COLOR));

	verts.insert(verts.end(), Vertex(1, 0, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 1, 0, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(0, 0, 1, 0, Vertex::COLOR));
	verts.insert(verts.end(), Vertex(1, 1, 1, 0, Vertex::COLOR));

	//Create a model with these vertices and assign it to a renderer
	square = SimpleModel(verts, renderer);
}

void DemoApp::onEnd()
{
	renderer.Destroy();
}

void DemoApp::preRender(double timeSinceLastFrame)
{
}

void DemoApp::render()
{
	//Render square
	square.RenderModel();
}

void DemoApp::postRender()
{
}

//TODO: move all input to input manager class
//Called from main.cpp
void DemoApp::onInput(WPARAM keyParam, int x, int y) {
	int key = (int)keyParam;
	switch (key) {
	case VK_LEFT:
		logManager->Info(string("left was pressed"), __FILE__, __LINE__);
		break;
	}
}

//Called from main.cpp
void DemoApp::onMouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			logManager->Info(string("Left mouse was pressed"), __FILE__, __LINE__);
		}
		break;
	}
}
