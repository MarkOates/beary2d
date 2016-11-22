


#include <allegro_flare/color.h>
#include <beary2d/tile_atlas.h>

#include <iostream>
#include <beary2d/tile.h>



TileAtlas::TileAtlas()
	: tile_atlas(NULL)	
	, tiles()
	, tile_width(16)
	, tile_height(16)
{}

void TileAtlas::load_from_atlas(ALLEGRO_BITMAP *tile_atlas, int tile_width, int tile_height, int margin_x, int margin_y, int tile_padding_x, int tile_padding_y)
{
	tiles.clear();

	this->tile_atlas = tile_atlas;
	this->tile_width = tile_width;
	this->tile_height = tile_height;

	int num_rows = (al_get_bitmap_width(tile_atlas) - margin_x*2) / (tile_width + tile_padding_x);
	int num_cols = (al_get_bitmap_height(tile_atlas) - margin_y*2) / (tile_height + tile_padding_y);

	if (tile_padding_x > 0) num_rows++;
	if (tile_padding_y > 0) num_cols++;

	std::cout << "loading tileset " << num_cols << "x" << num_rows << std::endl;

	for (int row=0; row<num_rows; row++)
		for (int col=0; col<num_cols; col++)
			tiles.push_back(al_create_sub_bitmap(tile_atlas,
				margin_x + col*(tile_width) + col*(tile_padding_x*2) + tile_padding_x,
				margin_y + row*(tile_height) + row*(tile_padding_y*2) + tile_padding_y,
				tile_width,
				tile_height));

	std::cout << "num tiles: " << tiles.size() << std::endl;
}


bool TileAtlas::export_atlas(std::string image_filename)
	// exports with no padding and no margins
{
	int num_cols = 8;
	int num_rows = (tiles.size() / num_cols);

	if (num_rows % num_cols > 0) num_rows++;

	int atlas_width = num_cols * tile_width;
	int atlas_height = num_rows * tile_height;

	ALLEGRO_STATE previous_state;
	al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);

	ALLEGRO_BITMAP *atlas_for_export = al_create_bitmap(atlas_width, atlas_height);
	al_set_target_bitmap(atlas_for_export);
	al_clear_to_color(color::transparent);

	for (int i=0; i<(int)tiles.size(); i++)
	{
		int row = i / num_cols;
		int col = i % num_cols;
		Tile *t = get_tile(i);
		if (t && t->bitmap)
			al_draw_bitmap(t->bitmap, col*tile_width, row*tile_height, 0);
	}

	al_save_bitmap(image_filename.c_str(), atlas_for_export);

	al_restore_state(&previous_state);

	al_destroy_bitmap(atlas_for_export);

	return true;
}


Tile *TileAtlas::set(int index, ALLEGRO_BITMAP *bitmap)
{
	if ((int)tiles.size() <= index) tiles.resize((index+1), NULL);
	else
	{
		// clear the existing tile bitmap data
		if (tiles[index].bitmap) al_destroy_bitmap(tiles[index].bitmap);
	}
	tiles[index].bitmap = bitmap;
	return &tiles[index];
	//return NULL;
}


Tile *TileAtlas::set(int index, ALLEGRO_BITMAP *bitmap, int64_t flags)
{
	if ((int)tiles.size() >= index) tiles.resize(index, NULL);
	else
	{
		// clear the existing tile bitmap data
		if (tiles[index].bitmap) al_destroy_bitmap(tiles[index].bitmap);
	}
	tiles[index].bitmap = bitmap;
	tiles[index].flags = flags;
	return &tiles[index];
}


Tile *TileAtlas::get_tile(int index)
{
	//if (index < 0  || tiles.empty() || index >= (int)tiles.size()) return NULL; // want to avoid this at all costs
	return &tiles[index];
}

void TileAtlas::clear() { tiles.clear(); }

int TileAtlas::get_tile_width() { return tile_width; }

int TileAtlas::get_tile_height() { return tile_height; }

void TileAtlas::set_tile_height(int height) { tile_height = height; }

void TileAtlas::set_tile_width(int width) { tile_width = width; }


void TileAtlas::lock_bitmap()
{
	al_lock_bitmap(this->tile_atlas, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
}


void TileAtlas::unlock_bitmap()
{
	al_unlock_bitmap(this->tile_atlas);
}




