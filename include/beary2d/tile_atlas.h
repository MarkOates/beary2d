#ifndef __BEARY2D_TILE_ATLAS_HEADER
#define __BEARY2D_TILE_ATLAS_HEADER




#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <beary2d/tile.h>
#include <cstdint>

class TileAtlas
{
private:
	ALLEGRO_BITMAP *tile_atlas;	
	int tile_width, tile_height;

public:
	std::vector<Tile> tiles;

	TileAtlas();
	void clear();

	void load_from_atlas(ALLEGRO_BITMAP *tile_atlas, int tile_width, int tile_height, int margin_x, int margin_y, int spacing_x, int spacing_y);
		// ^ used to be just "load"

	bool export_atlas(std::string image_filename);

	Tile *set(int index, ALLEGRO_BITMAP *bitmap);
	Tile *set(int index, ALLEGRO_BITMAP *bitmap, int64_t flags);

	Tile *get_tile(int index);
	int get_tile_width();
	int get_tile_height();

	void lock_bitmap();
	void unlock_bitmap();
};




#endif

