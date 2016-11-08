#pragma once
#include <iostream>
#include <vector>
#include "glm.hpp"
#include "Vertex.h"

using namespace std;
class FileReader {
public:
	static char* ReadFromFile(char* filename) {
		FILE* file;
		fopen_s(&file, filename, "rb");
		fseek(file, 0, SEEK_END);
		int length = ftell(file);
		fseek(file, 0, SEEK_SET);
		char* src = new char[length + 1];
		fread(src, 1, length, file);
		fclose(file);
		return src;
	}
	static bool LoadOBJ(const char* fname, std::vector<Vertex> &vertices) {
		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> tempVerts, tempUVs, tempNormals; // Used to store contents of OBJ file
		//std::vector<Vertex> vertices;

		FILE * file = fopen(fname, "r");
		if (file == NULL) {
			std::cout << "Failed to open OBJ file" << std::endl;
			return false;
		}
		while (1) {
			char lineHeader[128];
			//Read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // End of file
			if (strcmp(lineHeader, "v") == 0) { // If first char is a v (vertex position)
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); // Take 3 floats from line and push them into vertex X,Y,Z values
				//tempVerts.push_back(vertex);
				vertices.push_back(Vertex(vertex.x, vertex.y, vertex.z, 0.0f, Vertex::POSITION));
				printf("Vertex:%f,%f,%f (New Size: %d)\n", vertex.x, vertex.y, vertex.z, vertices.size());
			}
			else if (strcmp(lineHeader, "vt") == 0) { // If texture coordinate
				glm::vec3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y); // Take x and y values
				//tempUVs.push_back(uv);
				vertices.push_back(Vertex(uv.x, uv.y, 0.0f, 0.0f, Vertex::TEXTURE));
				printf("Texture:%f,%f (New Size: %d)\n", uv.x, uv.y, vertices.size());
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				//glm::vec3 normal;
				//fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z); // Take x and y values
				//tempNormals.push_back(normal);
			}
			//else if (strcmp(lineHeader, "f") == 0) {
			//	std::string vertex1, vertex2, vertex3;
			//	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			//	int matches = fscanf(file, "%d %d %d %d %d %d %d %d %d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
			//		&vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			//	if (matches != 9) {
			//		std::cout << "File too complex for parser" << std::endl;
			//		//return;
			//	}
			//	for (int i = 0; i < 3; i++) {
			//		vertexIndices.push_back(vertexIndex[i]);
			//		uvIndices.push_back(uvIndex[i]);
			//		normalIndices.push_back(normalIndex[i]);
			//	}
			//}
			else {
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}


			//for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			//	unsigned int vertexIndex = vertexIndices[i];
			//	glm::vec3 vertex = tempVerts[vertexIndex - 1]; // Subtract one because obj indexing starts at 1, not 0
			//	vertices.push_back(Vertex(vertex.x, vertex.y, vertex.z, 0.0f, Vertex::POSITION));
			//	//outVerts.push_back(vertex);
			//}


			//for (unsigned int i = 0; i < uvIndices.size(); i++) {
			//	unsigned int uvIndex = uvIndices[i];
			//	glm::vec3 vertex = tempUVs[uvIndex - 1]; // Subtract one because obj indexing starts at 1, not 0
			//	vertices.push_back(Vertex(vertex.x, vertex.y, 0.0f, 0.0f, Vertex::TEXTURE));
			//	//outUVs.push_back(vertex);
			//}

			//for (unsigned int i = 0; i < normalIndices.size(); i++) {
			//	unsigned int normalIndex = normalIndices[i];
			//	glm::vec3 vertex = tempNormals[normalIndex - 1]; // Subtract one because obj indexing starts at 1, not 0
			//	//vertices.push_back(Vertex(vertex.x, vertex.y, 0.0f, 0.0f, Vertex::NORMAL));
			//	//outNormals.push_back(vertex);
			//}
		}
		fclose(file);
		return true;
	}
};