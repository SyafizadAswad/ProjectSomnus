#include "Game.h"
#include "ShapeGenerator.h"
#include <vector>
#include <d3dcompiler.h>
#include <stdexcept>
#include <iostream>

void Game::InitD3D(HWND hwnd) {
	//describe the swap chain
	DXGI_SWAP_CHAIN_DESC scDesc = {};
	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = 800;
	scDesc.BufferDesc.Height = 600;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = hwnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		creationFlags,
		nullptr, 0,
		D3D11_SDK_VERSION,
		&scDesc,
		&swapChain,
		&device,
		nullptr,
		&context
	);

	if (FAILED(hr)) {
		MessageBox(nullptr, L"Failed to create D3D device and swap chain", L"Error", MB_OK);
		throw std::runtime_error("D3D11CreateDeviceAndSwapChain failed");
	}

	// get backbuffer
	ID3D11Texture2D* backBuffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

	// create render target view
	device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
	backBuffer->Release();

	// set the render target
	context->OMSetRenderTargets(1, &rtv, nullptr);

	// set the viewport
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewport);
}

Game::Game(HWND hwnd) {
	InitD3D(hwnd);
	LoadContent();
}

Game::~Game() {
	if (rtv) rtv->Release();
	if (swapChain) swapChain->Release();
	if (context) context->Release();
	if (device) device->Release();
}

void Game::LoadContent() {
	std::vector<Vertex> verts;
	std::vector<unsigned short> inds;
	ShapeGenerator::CreateCube(verts, inds);
	cubeMesh = std::make_shared<Mesh>(device, verts, inds);
}

void Game::Update() {

}

void Game::Render() {
	float color[] = { 0.1f, 0.1f, 0.2f, 1.0f };
	context->ClearRenderTargetView(rtv, color);

	cubeMesh->Draw(context);

	swapChain->Present(1, 0);
}