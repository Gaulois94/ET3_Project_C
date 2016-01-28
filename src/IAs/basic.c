#include "IAs/basic.h"
#include "Map.h"
#include "Contexts/InGame.h"
#include "Game.h"

void basicIA(Tile* tile, void* game)
{
	Ennemy* ennemy = (Ennemy*)tile;
	InGame* inGame = ((Game*)game)->inGameContext;

	if(tile->canDestroy)
	{
		Animation* spriteAnimation = (Animation*)tile->sprite;
		Animation_setInAnimation(spriteAnimation, false, true);
		return;
	}

	Drawable_move((Drawable*)tile, 0, ennemy->speedY);
	Tile* topLeftTile         = NULL;
	Tile* topRightTile        = NULL;
	Tile* bottomLeftTile      = NULL;
	Tile* bottomRightTile     = NULL;

	const SDL_Rect* pRect = Drawable_getRect((Drawable*)tile);

	bottomLeftTile  = Map_getTileInfo(inGame->map, pRect->x, pRect->y + pRect->h + 1); //+1 are here to check if we will be on collision if we move the ennemy by gravity of 1 pixel.
	bottomRightTile = Map_getTileInfo(inGame->map, pRect->x + pRect->w, pRect->y + pRect->h + 1);

	if(bottomLeftTile && (Tile_getInfo(bottomLeftTile) & SOLID) ||
	   bottomRightTile && (Tile_getInfo(bottomRightTile) & SOLID))
    {
		const SDL_Rect* tileRect;
		if(bottomRightTile)
		{
			bottomRightTile->updateCollision(bottomRightTile);
			tileRect = Drawable_getRect((Drawable*)bottomRightTile);
		}
		if(bottomLeftTile)
		{
			bottomLeftTile->updateCollision(bottomLeftTile);
			tileRect = Drawable_getRect((Drawable*)bottomLeftTile);
		}
		int32_t y = tileRect->y - 1;
		((Drawable*)tile)->setPosition((Drawable*)tile, pRect->x, y - pRect->h);
		ennemy->speedY = 0;
    }


	if(ennemy->speedY == 0)
	{
		if(ennemy->direction == DLEFT)
		{
			ennemy->moveX -= BASIC_SPEED;
			if(ennemy->moveX < -1)
				ennemy->moveX += 1;
			Drawable_move((Drawable*)tile, ennemy->moveX, 0);

			bottomLeftTile  = Map_getTileInfo(inGame->map, pRect->x, pRect->y + pRect->h + 1); //+1 are here to check if we will be on collision if we move the ennemy by gravity of 1 pixel.
			if(!bottomLeftTile || !(Tile_getInfo(bottomLeftTile) & SOLID))
			{
				Drawable_move((Drawable*)tile, 1, 0);
				ennemy->direction = DRIGHT;
			}
		}

		if(ennemy->direction == DRIGHT)
		{
			ennemy->moveX += BASIC_SPEED;
			if(ennemy->moveX > 1)
				ennemy->moveX -= 1;
			Drawable_move((Drawable*)tile, ennemy->moveX, 0);

			bottomRightTile = Map_getTileInfo(inGame->map, pRect->x + pRect->w, pRect->y + pRect->h + 1);
			if(!bottomRightTile || !(Tile_getInfo(bottomRightTile) & SOLID))
			{
				Drawable_move((Drawable*)tile, -1, 0);
				ennemy->direction = DLEFT;
			}
		}
	}

	ennemy->speedY += GRAVITY;
	if(ennemy->speedY > MAX_SPEED_GRAVITY)
		ennemy->speedY = MAX_SPEED_GRAVITY;
}
