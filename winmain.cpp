#include <windows.h>
#include "directx.h"
#include "sprites.h"

HINSTANCE hInst;				// holds the instance for this app
HWND wndHandle;					// global window handle

// this holds the DirectX Manager
DXInterface *dxMgr;

////////////////////////////////////////////// forward declarations
bool    initWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// call our function to init and create our window
	if (!initWindow(hInstance))
	{
		MessageBox(NULL, "Unable to create window", "ERROR", MB_OK);
		return false;
	}

	// create the directx manager
	dxMgr = new DXInterface();

	// init the directx manager
	if (!dxMgr->init(wndHandle))
	{
		MessageBox(NULL, "Unable to Init the DirectX Manager", "ERROR", MB_OK);
		return false;
	}
	
	initZombieSprites();

	// initialise the sprites
	if (!initZombieSprites())
	{
		MessageBox(NULL, "Unable to Init Sprites", "ERROR", MB_OK);
		return false;
	}

	initPlayerSprites();

	// initialise the sprites
	if (!initPlayerSprites())
	{
		MessageBox(NULL, "Unable to Init Sprites", "ERROR", MB_OK);
		return false;
	}

	// Main message loop:
	// Enter the message loop
    MSG msg; 
    ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
		// check for messages
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		// this is called when no messages are pending
		else
		{
			dxMgr->beginRender();
	
				
			
			for(int i=0; i < MAX_SPRITES; i++)
			{
				drawZombieSprite(i);	
			}
			for(int i=0; i < MAX_PLAYERS; i++)
			{
				drawPlayerSprite(i);
			}

			dxMgr->endRender();
		}
    }
	
	// shutdown the directX Manager
	dxMgr->shutdown();

	return (int) msg.wParam;
}

bool initWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
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

	wndHandle = CreateWindow("DirectXExample", 
							 "DirectX Example Window", 
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, 
							 CW_USEDEFAULT, 
							 SCRN_WIDTH, 
							 SCRN_HEIGHT, 
							 NULL, 
							 NULL, 
							 hInstance, 
							 NULL);
   if (!wndHandle)
      return false;
   
   ShowWindow(wndHandle, SW_SHOW);
   UpdateWindow(wndHandle);

   return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

