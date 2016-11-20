#include "BoundingBox.h"
#include <vector>
#include "Shader.h"
#include "FileReader.h"

BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}

BoundingBox::BoundingBox(glm::vec3 &_center) { 
	center = &_center;
}

bool BoundingBox::BoxIntersects(const BoundingBox & otherBox) {
	if (Xmax > otherBox.Xmin &&
		Xmin < otherBox.Xmax &&
		Ymax > otherBox.Ymin &&
		Ymin < otherBox.Ymax &&
		Zmax > otherBox.Zmin &&
		Zmin < otherBox.Zmax) {
		return true;
	}
	else {
		return false;
	}
}

//TODO: OPTIMIZE THIS CRAP CODE
void BoundingBox::Draw(glm::mat4 transform, OpenGLRenderer* renderer)
{
	Shader shader = Shader(FileReader::ReadFromFile("shader.vert").c_str(), FileReader::ReadFromFile("basicShader.frag").c_str());
	std::vector<glm::vec3> verts, color;
	//front
	verts.push_back(glm::vec3(Xmin, Ymax, Zmin));
	verts.push_back(glm::vec3(Xmin, Ymin, Zmin));
	verts.push_back(glm::vec3(Xmax, Ymin, Zmin));
	verts.push_back(glm::vec3(Xmax, Ymax, Zmin));
	//top
	verts.push_back(glm::vec3(Xmin, Ymax, Zmin));
	verts.push_back(glm::vec3(Xmin, Ymax, Zmax));
	verts.push_back(glm::vec3(Xmax, Ymax, Zmax));
	verts.push_back(glm::vec3(Xmax, Ymax, Zmin));

	//right
	verts.push_back(glm::vec3(Xmax, Ymax, Zmin));
	verts.push_back(glm::vec3(Xmax, Ymin, Zmax));
	verts.push_back(glm::vec3(Xmax, Ymin, Zmax));
	verts.push_back(glm::vec3(Xmax, Ymax, Zmax));

	//bottom
	verts.push_back(glm::vec3(Xmin, Ymin, Zmin));
	verts.push_back(glm::vec3(Xmin, Ymin, Zmax));
	verts.push_back(glm::vec3(Xmax, Ymin, Zmax));
	verts.push_back(glm::vec3(Xmax, Ymin, Zmin));

	//left
	verts.push_back(glm::vec3(Xmin, Ymin, Zmin));
	verts.push_back(glm::vec3(Xmin, Ymax, Zmax));
	verts.push_back(glm::vec3(Xmin, Ymax, Zmax));
	verts.push_back(glm::vec3(Xmin, Ymin, Zmax));


	
	GLuint vao, ibo;
	GLuint buffers[1];
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(glm::vec3), &verts[0], GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	shader.Use();
	renderer->SetProgram(shader.GetProgram());
	renderer->RenderTransform(transform);

	glDrawArrays(GL_LINE_STRIP, 0, verts.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void BoundingBox::SetCenter(glm::vec3 &_center) {
	center = &_center;
	Xmin = center->x - (scale.x);
	Xmax = center->x + (scale.x);
	Ymin = center->y - (scale.y);
	Ymax = center->y + (scale.y);
	Zmin = center->z - (scale.z);
	Zmax = center->z + (scale.z);
}			

void BoundingBox::SetScale(glm::vec3 &_scale) {
	scale = _scale;
}




