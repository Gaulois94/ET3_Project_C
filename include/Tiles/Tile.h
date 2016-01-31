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

/** \brief get the information about the tile. The object is SCORE, DAMAGE, etc. or a mix of them.
 * \param tile the Tile itself
 * \return the information. Use the logical and to get the information you want (for exemple getInfo() \& SCORE to get the SCORE characteristic of the Tile*/
uint32_t Tile_getInfo(Tile* tile);

/** \brief update the tile collsion
 * \param the Tile itself
 * \return the info of the tile*/
uint32_t Tile_updateCollision(Tile* self);

/** \brief set the update function of the Tile. We use this because different tile can have the same update function.
 * \param tile the Tile itself
 * \param update the update function
 * \param data the data passed to the update function*/
void     Tile_setUpdate(Tile* tile, void(*update)(Tile*, void*), void* data);

#endif
