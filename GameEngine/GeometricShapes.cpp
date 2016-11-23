#include "GeometricShapes.h"

std::vector<Vertex> GeometricShapes::GetShape(SHAPES _shapeType) {

	std::vector<Vertex> verts;
	if (_shapeType == SHAPES::cube) {
		bool res = FileReader::LoadOBJ("box.obj", verts);
		if (res)
			printf("File loaded properly\n");
		else
			printf("file did not load \n");
		//Add colors to our vector
		int size = verts.size();
		for (int i = 0; i < size; i++) {
			verts.push_back(Vertex(1, 1, 1, 0, Vertex::COLOR));
			verts.push_back(Vertex(1, 1, 1, 0, Vertex::COLOR));
			verts.push_back(Vertex(1, 1, 1, 0, Vertex::COLOR));
		}
		////Add 4 vertices to our vector
		////Left
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//

		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

		//																			  //Right
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));//

		//																			 //Back
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//

		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));//

		//																			  //Front
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//


		//																			  //Bottom
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//triangle 1
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//

		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, -1.0f, 0.0f, Vertex::POSITION));//triangle 2
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, -1.0f, 0.0f, Vertex::POSITION));//

		//																			 //Top
		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 1
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(-1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));//

		//verts.insert(verts.end(), Vertex(-1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//triangle 2
		//verts.insert(verts.end(), Vertex(1.0f, -1.0f, 1.0f, 0.0f, Vertex::POSITION));
		//verts.insert(verts.end(), Vertex(1.0f, 1.0f, 1.0f, 0.0f, Vertex::POSITION));//



		////Add colors to our vector
		//for (int i = 0; i < 12; i++) {
		//	verts.insert(verts.end(), Vertex(1, 1, 1, 0, Vertex::COLOR));
		//	verts.insert(verts.end(), Vertex(1, 1, 1, 0, Vertex::COLOR));
		//	verts.insert(verts.end(), Vertex(1, 1, 1, 0, Vertex::COLOR));
		//}


		////Add normals to our vector
		//for (int i = 0; i < 12; i++) {
		//	verts.insert(verts.end(), Vertex(0, 0, -1, 0, Vertex::NORMAL));
		//	verts.insert(verts.end(), Vertex(0, 0, -1, 0, Vertex::NORMAL));
		//	verts.insert(verts.end(), Vertex(0, 0, -1, 0, Vertex::NORMAL));
		//}

		//verts.insert(verts.end(), Vertex(0.0f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.0f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.0f, 1.0f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.0f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.33f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.33f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.66f, 0.66f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(0.66f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(1.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));

		//verts.insert(verts.end(), Vertex(1.0f, 0.33f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(1.0f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		//verts.insert(verts.end(), Vertex(0.66f, 0.0f, 0.0f, 0.0f, Vertex::TEXTURE));
		return verts;
	}
	if (_shapeType == SHAPES::sphere) {
		bool res = FileReader::LoadOBJ("sphere.obj", verts);
		if (res)
			printf("File loaded properly\n");
		//Add colors to our vector
		for (int i = 0; i < 482; i++) {
			verts.push_back(Vertex(1, 1, 1, 0, Vertex::COLOR));
		}

		return verts;
	}
	return verts;
}