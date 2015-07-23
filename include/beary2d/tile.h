#ifndef __BEARY2D_TILE_HEADER
#define __BEARY2D_TILE_HEADER




#include <allegro5/allegro.h>
#include <cstdint>
#include <allegro_flare/bit_flags.h>

class Tile
{
public:
	ALLEGRO_BITMAP *bitmap;
	BitFlags<uint32_t> flags;

	Tile(ALLEGRO_BITMAP *bitmap, int64_t flags=0);
};





#endif

