#pragma once
#include <d3d11.h>
#include <vector>
#include "Vertex.h"

class Mesh {
public:
	Mesh(ID3D11Device* device, const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices);
	~Mesh();

	void Draw(ID3D11DeviceContext* context);

private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int indexCount;
};