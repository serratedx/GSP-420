#pragma once

#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>

#define SCRN_WIDTH 640			// the width of the screen
#define SCRN_HEIGHT 480			// the height of the screen

class DXInterface
{
private:
	HRESULT                 lastResult;
	LPDIRECT3D9             pD3D;
	LPDIRECT3DDEVICE9       pd3dDevice;
public:
	DXInterface(void);
	~DXInterface(void);
	bool init(HWND hwnd);
	void shutdown(void);
	void beginRender(void);
	void endRender(void);
	IDirect3DSurface9* getSurfaceFromBitmap(std::string filename);

	IDirect3DSurface9* getBackBuffer(void);
	void blitToSurface(IDirect3DSurface9* srcSurface, const RECT *srcRect, const RECT *destRect);
};
