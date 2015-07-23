#ifndef __BEARY2D_MAP_HEADER
#define __BEARY2D_MAP_HEADER




#include <vector>
#include <allegro_flare/vec2d.h>
#include <beary2d/tile_layer.h>

class Map
{
public:
	std::vector<TileLayer> tile_layers;
	vec2d gravity; // rethink this, ultimately map forces should be zones or tiles
	Map();
};




#endif

