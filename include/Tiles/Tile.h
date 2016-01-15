#ifndef  TILE_INC
#define  TILE_INC

#include "Drawable/Drawable.h"
#include "Drawable/Sprite.h"
#define SCORE      0x01
#define DAMAGE     0x02
#define SOLID      0x04
#define CHECKPOINT 0x08
#define FINISH     0x10

typedef enum
{
	GROUND,
	COIN
}EnumTile;

typedef struct Tile
{
	Drawable  base;
	Sprite* sprite;

	uint32_t(*updateCollision)(struct Tile*);

	bool solid;
	bool doDamages;
}Tile;

void  Tile_init(Tile* self, SDL_Texture* texture, const SDL_Rect* subRect);
void  Tile_setPosition(Drawable* self, int32_t x, int32_t y);
void  Tile_setSize(Drawable* self, uint32_t width, uint32_t height);
void  Tile_setStatic(Drawable* self, bool isStatic);
void  Tile_draw(Drawable* self, Window* window);
void  Tile_destroy(Drawable* self);
uint32_t Tile_updateCollision(Tile* self);

#endif
