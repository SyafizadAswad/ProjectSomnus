#pragma once
#include <vector>
#include "Vertex.h"

class ShapeGenerator {
public:
	static void CreateCube(std::vector<Vertex>& outVertices, std::vector<unsigned short>& outIndices);
};