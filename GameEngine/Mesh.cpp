#include "Mesh.h"
#include "FileReader.h"

Mesh::Mesh(vector<mVertex> _vertices, vector<GLuint> _indices, vector<Texture> _textures)
{
	vertices = _vertices;
	indices = _indices;
	textures = _textures;

	//shader = _shader;

	//ProcessVertices();
	SetupMesh();
}

Mesh::~Mesh()
{
}

//void Mesh::ProcessVertices()
//{
//	glm::vec3 newVertex;
//	glm::vec2 new2DVertex;
//	for (int i = 0; i < (int)vertices.size(); i++) { // Loop through all the vertices in the vector
//		switch (vertices[i].type)
//		{
//		case Vertex::POSITION: // If position, take only x,y,z values
//			newVertex = glm::vec3(vertices[i].values.x, vertices[i].values.y, vertices[i].values.z);
//			vertPos.push_back(newVertex);
//			break;
//		case Vertex::NORMAL:
//			newVertex = glm::vec3(vertices[i].values.x, vertices[i].values.y, vertices[i].values.z);
//			vertNormal.push_back(newVertex);
//			break;
//		case Vertex::TEXTURE:// If texture, take only x,y(UV) values
//			new2DVertex = glm::vec2(vertices[i].values.x, vertices[i].values.y);
//			vertUV.push_back(new2DVertex);
//			break;
//		}
//	}
//	printf("ProcessVertices() Size: %d\n",vertPos.size());
//}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(mVertex),
		&vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		&indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mVertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(mVertex),
		(GLvoid*)offsetof(mVertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(mVertex),
		(GLvoid*)offsetof(mVertex, TexCoords));

	glBindVertexArray(0);
	printf("SetupMesh()\n");
}

/*void Mesh::SetShader(Shader _shader)
{
	shader = _shader;
}*/

void Mesh::Render(Shader shader, OpenGLRenderer rend)
{
	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader.GetProgram(), (name + number).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	//glUniform1f(glGetUniformLocation(shader.GetProgram(), "material.shininess"), 16.0f);

	/*GLint matAmbientLoc = glGetUniformLocation(shader.GetProgram(), "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(shader.GetProgram(), "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(shader.GetProgram(), "material.specular");
	GLint matShineLoc = glGetUniformLocation(shader.GetProgram(), "material.shininess");

	glUniform3f(matAmbientLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(matDiffuseLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);
*/
	
	/*GLint lightALoc = glGetUniformLocation(shader.GetProgram(), "light.ambient");
	glUniform3f(lightALoc, 1.0f, 1.0f, 1.0f); 
	GLint lightDLoc = glGetUniformLocation(shader.GetProgram(), "light.diffuse");
	glUniform3f(lightALoc, 1.0f, 1.0f, 1.0f);
	GLint lightSLoc = glGetUniformLocation(shader.GetProgram(), "light.specular");
	glUniform3f(lightALoc, 1.0f, 1.0f, 1.0f);
	GLint lightPosLoc = glGetUniformLocation(shader.GetProgram(), "light.position");
	glUniform3f(lightPosLoc, 0.0f, 0.0f, 0.0f);

	GLint viewPosLoc = glGetUniformLocation(shader.GetProgram(), "viewPos");
	glUniform3f(viewPosLoc, rend.GetActiveCam()->GetPosition().x, rend.GetActiveCam()->GetPosition().y, rend.GetActiveCam()->GetPosition().z);*/

	glUniform3f(glGetUniformLocation(shader.GetProgram(), "diffuse_color"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader.GetProgram(), "specular_color"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(shader.GetProgram(), "light_position"), 0.0f, 0.0f, 0.0f);

	// Draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

