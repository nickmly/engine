#include "GeometricShapes.h"

 std::vector<Vertex> GeometricShapes::GetShape(SHAPES _shapeType) {

		std::vector<Vertex> verts;
		if (_shapeType == SHAPES::cube) {
			//Add 4 vertices to our vector
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
			return verts;
		}
		return verts;
}