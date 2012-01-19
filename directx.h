#include <windows.h>
#include <d3d9.h>

class DXInterface
{
private:
	HINSTANCE				hInstance;
	HWND					wndHandle;
	LPDIRECT3D9             pD3D;
	LPDIRECT3DDEVICE9       pd3dDevice;

public:
	DXInterface(){};
	virtual ~DXInterface(){};
	virtual bool initWindow(HINSTANCE hInstance);
	virtual bool initDirect3D();
	virtual void render();
	virtual void cleanup();

};