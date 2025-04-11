#include <windows.h>
#include <d3d11.h>
#include "Game.h"
#pragma comment(lib, "d3d11.lib")

Game* game = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	// Register window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0,
		hInstance, nullptr, nullptr, nullptr, nullptr,
		L"MyWindowClass", nullptr };
	RegisterClassEx(&wc);

	// Create Window
	HWND hwnd = CreateWindow(L"MyWindowClass", L"My DX11 Game Window",
		WS_OVERLAPPED, 100, 100, 1280, 720,
		nullptr, nullptr, wc.hInstance, nullptr);

	if (!hwnd) {
		MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK);
		return -1;
	}

	// Create device and swap chain
	DXGI_SWAP_CHAIN_DESC scd = {};
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 1;
	scd.Windowed = TRUE;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;

	D3D_FEATURE_LEVEL featureLevel;
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, 0, nullptr, 0,
		D3D11_SDK_VERSION, &scd, &swapChain, &device,
		&featureLevel, &context);

	// Get backbuffer and set render target
	ID3D11RenderTargetView* renderTarget = nullptr;
	ID3D11Texture2D* backBuffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	device->CreateRenderTargetView(backBuffer, nullptr, &renderTarget);
	backBuffer->Release();
	context->OMSetRenderTargets(1, &renderTarget, nullptr);

	// Show window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	game = new Game(hwnd);

	// Main loop
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->Update();
			game->Render();
		}
	}

	delete game;
	return 0;

	// Cleanup
	/*renderTarget->Release();
	swapChain->Release();
	context->Release();
	device->Release();

	UnregisterClass(L"MyWindowClass", hInstance);
	return 0;*/
}