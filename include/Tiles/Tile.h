#ifndef  TILE_INC
#define  TILE_INC

#include "Drawable/Drawable.h"
#define SCORE      0x01
#define DAMAGE     0x02
#define SOLID      0x04
#define CHECKPOINT 0x08
#define FINISH     0x10

typedef struct Tile
{
	Drawable* drawable;

	uint32_t(*updateCollision)(struct Tile*);

	uint8_t solid;
	uint8_t doDamages;
}Tile;

void  Tile_init(Tile* self, const SDL_Rect* destRect);
void  Tile_draw(Tile* self);
uint32_t Tile_updateCollision(Tile* self);

#endif
