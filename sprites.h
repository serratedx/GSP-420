#include "directx.h"
#include <string.h>

#define MAX_PLAYERS 1			// this is the number of players
#define MAX_SPRITES 4			// this is the number of sprites we want
#define SPRITE_WIDTH 96			// the width of each sprite
#define SPRITE_HEIGHT 128		// the height of each sprite

// this is the sprite structure
extern DXInterface			*dxMgr;
IDirect3DSurface9*	playerSurface;
IDirect3DSurface9*	zombieSurface;
extern LPDIRECT3DDEVICE9	pd3dDevice;

struct {
	RECT srcRect;				// holds the location of this sprite
								// in the source bitmap
	int posX;					// the sprites X position
	int posY;					// the sprites Y position

	// movement
	int moveX;
	int moveY;

	// animation
	int numFrames;				// number of frames this animation has
	int curFrame;				// the current frame of animation
} spriteStruct[MAX_SPRITES], playerStruct[MAX_PLAYERS];

bool initZombieSprites()
{

	zombieSurface = dxMgr->getSurfaceFromBitmap("zWalkStrip.bmp");
	if (zombieSurface == NULL)
		return false;

	for (int i=0; i < MAX_SPRITES; i++)
	{
		spriteStruct[i].srcRect.top = 0;
		spriteStruct[i].srcRect.left = i * SPRITE_WIDTH;
		spriteStruct[i].srcRect.right = spriteStruct[i].srcRect.left + SPRITE_WIDTH;
		spriteStruct[i].srcRect.bottom = SPRITE_HEIGHT;
		spriteStruct[i].posX = rand()% SCRN_WIDTH - SPRITE_WIDTH;
		spriteStruct[i].posY = rand()% SCRN_HEIGHT - SPRITE_HEIGHT;

		// set the animation data
		spriteStruct[i].curFrame = 0;
		spriteStruct[i].numFrames = 4;

		// set the move data
		spriteStruct[i].moveX = 1;
		spriteStruct[i].moveY = 1;
	}

	return true;
}

bool initPlayerSprites()
{
	playerSurface = dxMgr->getSurfaceFromBitmap("GSP420walkstrip.bmp");
	if (playerSurface == NULL)
		return false;

	for (int i=0; i < MAX_PLAYERS; i++)
	{
		playerStruct[i].srcRect.top = 0;
		playerStruct[i].srcRect.left = i * SPRITE_WIDTH;
		playerStruct[i].srcRect.right = playerStruct[i].srcRect.left + SPRITE_WIDTH;
		playerStruct[i].srcRect.bottom = SPRITE_HEIGHT;
		playerStruct[i].posX = rand()% SCRN_WIDTH - SPRITE_WIDTH;
		playerStruct[i].posY = rand()% SCRN_HEIGHT - SPRITE_HEIGHT;

		// set the animation data
		playerStruct[i].curFrame = 0;
		playerStruct[i].numFrames = 4;

		// set the move data
		playerStruct[i].moveX = 1;
		playerStruct[i].moveY = 1;
	}

	return true;
}

bool changePlayerSprites(std::string fileName)
{
	playerSurface = dxMgr->getSurfaceFromBitmap(fileName);
	if (playerSurface == NULL)
		return false;

	for (int i=0; i < MAX_PLAYERS; i++)
	{
		playerStruct[i].srcRect.top = 0;
		playerStruct[i].srcRect.left = i * SPRITE_WIDTH;
		playerStruct[i].srcRect.right = playerStruct[i].srcRect.left + SPRITE_WIDTH;
		playerStruct[i].srcRect.bottom = SPRITE_HEIGHT;

		// set the animation data
		playerStruct[i].curFrame = 0;
		playerStruct[i].numFrames = 4;
	}
	return true;
}

void drawZombieSprite(int whichOne)
{
	// make the sprite animation through the frames
	if (spriteStruct[whichOne].curFrame < spriteStruct[whichOne].numFrames-1)
		spriteStruct[whichOne].curFrame++;
	else
		spriteStruct[whichOne].curFrame = 0;
	
	// set the source rect to the correct frame position
	spriteStruct[whichOne].srcRect.left = spriteStruct[whichOne].curFrame * SPRITE_WIDTH;
	spriteStruct[whichOne].srcRect.right = spriteStruct[whichOne].srcRect.left + SPRITE_WIDTH;

	// move the sprite by it's movement rate
	spriteStruct[whichOne].posX += spriteStruct[whichOne].moveX;

	// make sure that this sprite is not going off the screen
	if (spriteStruct[whichOne].posX > SCRN_WIDTH - SPRITE_WIDTH)
		spriteStruct[whichOne].moveX = -1;
	else if (spriteStruct[whichOne].posX < 0)
		spriteStruct[whichOne].moveX = 1;

	// set the destination for this sprite
	RECT destRect;
	destRect.left = spriteStruct[whichOne].posX;
	destRect.top = spriteStruct[whichOne].posY;
	destRect.bottom = destRect.top + SPRITE_HEIGHT;
	destRect.right = destRect.left + SPRITE_WIDTH;

	// draw the sprite to the back buffer
	dxMgr->blitToSurface(zombieSurface, &spriteStruct[whichOne].srcRect, &destRect);	
	
}

void drawPlayerSprite(int whichOne)
{
	// make the sprite animation through the frames
	if (playerStruct[whichOne].curFrame < playerStruct[whichOne].numFrames-1)
		playerStruct[whichOne].curFrame++;
	else
		playerStruct[whichOne].curFrame = 0;
	
	// set the source rect to the correct frame position
	playerStruct[whichOne].srcRect.left = playerStruct[whichOne].curFrame * SPRITE_WIDTH;
	playerStruct[whichOne].srcRect.right = playerStruct[whichOne].srcRect.left + SPRITE_WIDTH;

	// move the sprite by it's movement rate
	playerStruct[whichOne].posX += playerStruct[whichOne].moveX;

	// make sure that this sprite is not going off the screen
	if (playerStruct[whichOne].posX > SCRN_WIDTH - SPRITE_WIDTH)
	{	
		playerStruct[whichOne].moveX = -1;
		changePlayerSprites("zWalkStrip.bmp");
	}
	else if (playerStruct[whichOne].posX < 0)
	{
		playerStruct[whichOne].moveX = 1;
		changePlayerSprites("GSP420walkstrip.bmp");
	}

	// set the destination for this sprite
	RECT destRect;
	destRect.left = playerStruct[whichOne].posX;
	destRect.top = playerStruct[whichOne].posY;
	destRect.bottom = destRect.top + SPRITE_HEIGHT;
	destRect.right = destRect.left + SPRITE_WIDTH;

	// draw the sprite to the back buffer
	dxMgr->blitToSurface(playerSurface, &playerStruct[whichOne].srcRect, &destRect);	
	
}