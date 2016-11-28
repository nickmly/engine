#include "Mesh.h"
#include "FileReader.h"

Mesh::Mesh(vector<Vertex> _vertices, vector<GLuint> _indices, vector<Texture> _textures, char* _vertShader, char* _fragShader)
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	shader = Shader(FileReader::ReadFromFile(_vertShader).c_str(), FileReader::ReadFromFile(_fragShader).c_str());

	ProcessVertices();
	SetupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::ProcessVertices()
{
	glm::vec3 newVertex;
	glm::vec2 new2DVertex;
	for (int i = 0; i < (int)vertices.size(); i++) { // Loop through all the vertices in the vector
		switch (vertices[i].type)
		{
		case Vertex::POSITION: // If position, take only x,y,z values
			newVertex = glm::vec3(vertices[i].values.x, vertices[i].values.y, vertices[i].values.z);
			vertPos.push_back(newVertex);
			break;
		case Vertex::NORMAL:
			newVertex = glm::vec3(vertices[i].values.x, vertices[i].values.y, vertices[i].values.z);
			vertNormal.push_back(newVertex);
			break;
		case Vertex::TEXTURE:// If texture, take only x,y(UV) values
			new2DVertex = glm::vec2(vertices[i].values.x, vertices[i].values.y);
			vertUV.push_back(new2DVertex);
			break;
		}
	}
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO); // Generate 1 vertex array

	glGenBuffers(3, VBO); // Generate vertex buffer object
	glGenBuffers(1, &EBO); // Generate element buffer object

	glBindVertexArray(VAO);

	//Bind vertex positions
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertPos.size() * sizeof(glm::vec3), &vertPos.at(0), GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Bind UV coordinates
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, vertUV.size() * sizeof(glm::vec2), &vertUV.at(0), GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 0, "vTexCoord");
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	//Bind normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, vertNormal.size() * sizeof(glm::vec3), &vertNormal.at(0), GL_STATIC_DRAW);
	glBindAttribLocation(shader.GetProgram(), 3, "vNormal");
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);

	//Bind indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices.at(0), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Render()
{
	GLuint diffuseNr = 1; // Number of diffuse textures
	GLuint specNr = 1; // Number of specular textures
	for (GLuint i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		stringstream ss;
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++;
		else if (name == "texture_specular")
			ss << specNr++;
		number = ss.str();

		glUniform1f(glGetUniformLocation(shader.GetProgram(), ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

