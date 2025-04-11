#pragma once
#include <memory>
#include "Mesh.h"

class Game {
public:
	Game(HWND hwnd);
	~Game();

	void Update();
	void Render();

private:
	void InitD3D(HWND hwnd);
	void LoadContent();

	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;

	std::shared_ptr<Mesh> cubeMesh;
};