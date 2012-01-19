#include "directx.h"

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

DXInterface *dxInterface=NULL;

void Render(){
	dxInterface->render();
}

//main entry point for windows Apps
int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	dxInterface = new DXInterface();

	//initalize the window
	if(!dxInterface->initWindow( hInstance ) )
	{
		MessageBox(NULL, "Unable to create window", "ERROR", MB_OK);
		return false;
	}

	//called after creating the window
	if(!dxInterface->initDirect3D())
	{
		MessageBox(NULL, "Unable to create Device", "ERROR", MB_OK);
		return false;
	}

	//main msg window
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while( msg.message!=WM_QUIT )
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			Render();
		}
	}
	//dxInterface->cleanup();
	//delete dxInterface;
	return (int) msg.wParam;
	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//check and acailable msg from the queue
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}
	//Always return a message to the default window procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}
