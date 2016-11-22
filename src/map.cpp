

#include <beary2d/map.h>

#include <beary2d/tile_layer.h>


Map::Map()
	: tile_layer(NULL, 0, 0)
	, gravity(0, 0.18f) // rethink this, ultimately map forces should be zones or tiles
{}



