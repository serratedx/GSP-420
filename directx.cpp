#include <windows.h>
#include <d3d9.h>
#include "directx.h"

extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

///////////////window creation

bool DXInterface::initWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "DirectXExample";
	wcex.hIconSm		= 0;
	RegisterClassEx(&wcex);

	//create the window
	wndHandle = CreateWindow(
				"DirectXExample",									//Window class to use
				"This is a test window for DirectX work",			//The titlebar text
				WS_OVERLAPPEDWINDOW,								//The window Style
				CW_USEDEFAULT,										//The start x coordinate
				CW_USEDEFAULT,										//The start y coordinate
				640,												//Width
				480,												//Height
				NULL,												//Parent window
				NULL,												//Menu Used for this app
				hInstance,											//Application instance
				NULL);												//No values passed to the window

	//Make sure that the window created is valid
	if (!wndHandle)
		return false;

	//display the window
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}



//////////////////initDirect3D

bool DXInterface::initDirect3D(void)
{
	//Create DirectX object
	if( NULL == (pD3D = Direct3DCreate9 (D3D_SDK_VERSION)))
	{
		return false;
	}

	//Fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory (&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = 480;
	d3dpp.BackBufferWidth = 640;
	d3dpp.hDeviceWindow = wndHandle;

	//Create a default DirectX device
	if(FAILED(pD3D->CreateDevice(	D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									wndHandle,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpp,
									&pd3dDevice)))
	{
		return false;
	}
	return true;
}

/////////////render()

void DXInterface::render(void)
{
	//Check to make sure you have a valid Direct3D Device
	if(NULL == pd3dDevice)
		return;
	//Clear the back buffer to a blue color
	pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

	//present the back buffer contents to the display
	pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

void DXInterface::cleanup(void)
{
	//Release the device and the direct3d object
	if(pd3dDevice != NULL)
		pd3dDevice->Release();

	if(pD3D != NULL)
		pD3D->Release();
}