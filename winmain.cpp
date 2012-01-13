#include <windows.h>

HINSTANCE hInst;
HWND wndHandle;

//forward Declarations
bool initWindow( HINSTANCE hInstance );
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

//main entry point for windows Apps
int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	//initalize the window
	if( !initWindow( hInstance ) )
		return false;

	//main msg window
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while (GetMessage(&msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	return (int) msg.wParam;
}


bool initWindow( HINSTANCE hInstance )
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