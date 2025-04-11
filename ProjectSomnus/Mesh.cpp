#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices)
	: vertexBuffer(nullptr), indexBuffer(nullptr), indexCount((int)indices.size()) {
	
	D3D11_BUFFER_DESC vbd = {};
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = (UINT)(sizeof(Vertex) * vertices.size());
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA initData = { vertices.data() };
	device->CreateBuffer(&vbd, &initData, &vertexBuffer);

	D3D11_BUFFER_DESC ibd = {};
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = (UINT)(sizeof(unsigned short) * indices.size());
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA iData = { indices.data() };
	device->CreateBuffer(&ibd, &iData, &indexBuffer);
}

Mesh::~Mesh() {
	if (vertexBuffer) vertexBuffer->Release();
	if (indexBuffer) indexBuffer->Release();
}

void Mesh::Draw(ID3D11DeviceContext* context) {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IAGetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	context->DrawIndexed(indexCount, 0, 0);
}