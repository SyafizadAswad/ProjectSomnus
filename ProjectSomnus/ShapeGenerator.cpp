#include "ShapeGenerator.h"

void ShapeGenerator::CreateCube(std::vector<Vertex>& outVertices, std::vector<unsigned short>& outIndices)
{
	outVertices = {
		{{-0.5f, -0.5f, -0.5f}, {1, 0, 0}},
		{{-0.5f, +0.5f, -0.5f}, {0, 1, 0}},
		{{+0.5f, +0.5f, -0.5f}, {0, 0, 1}},
		{{+0.5f, -0.5f, -0.5f}, {1, 1, 0}},
		{{-0.5f, -0.5f, +0.5f}, {1, 0, 1}},
		{{-0.5f, +0.5f, +0.5f}, {0, 1, 1}},
		{{+0.5f, +0.5f, +0.5f}, {1, 1, 1}},
		{{+0.5f, -0.5f, +0.5f}, {0.5f, 0.5f, 0.5f}},
	};

	outIndices = {
		0,1,2, 0,2,3,
		4,6,5, 4,7,6,
		4,5,1, 4,1,0,
		3,2,6, 3,6,7,
		1,5,6, 1,6,2,
		4,0,3, 4,3,7
	};
}