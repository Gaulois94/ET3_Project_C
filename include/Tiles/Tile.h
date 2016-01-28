#ifndef  TILE_INC
#define  TILE_INC

#include "Drawable/Drawable.h"
#include "Drawable/Sprite.h"

#define SCORE      0x01
#define DAMAGE     0x02
#define SOLID      0x04
#define CHECKPOINT 0x08
#define FINISH     0x10
#define BEGIN      0x20
#define ENNEMY     0x40

typedef enum
{
	GROUND,
	COIN
}EnumTile;

typedef struct Tile
{
	Drawable  base;
	Sprite* sprite;
	bool hasMove;
	bool hasDraw;

	uint32_t(*updateCollision)(struct Tile*);

	bool solid;
	bool doDamages;
	bool canDestroy;
	uint32_t info;

	void* data;
	void(*update)(struct Tile*, void*);
}Tile;

void     Tile_init(Tile* self, SDL_Texture* texture, const SDL_Rect* rect);
void     Tile_setPosition(Drawable* self, int32_t x, int32_t y);
void     Tile_setSize(Drawable* self, uint32_t width, uint32_t height);
void     Tile_setStatic(Drawable* self, bool isStatic);
void     Tile_draw(Drawable* self, Window* window);
void     Tile_destroy(Drawable* self);
uint32_t Tile_getInfo(Tile* tile);
uint32_t Tile_updateCollision(Tile* self);
void     Tile_setUpdate(Tile* tile, void(*update)(Tile*, void*), void* data);

#endif
