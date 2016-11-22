


#include <iostream>

#include <allegro_flare/useful.h>
#include <allegro_flare/camera2d.h>

#include <beary2d/tile_layer.h>
#include <beary2d/tile_index.h>
#include <beary2d/tile.h>




TileLayer::TileLayer(TileAtlas *tile_atlas, int width, int height)
	: tile_atlas(tile_atlas)
	, width(width)
	, height(height)
	, tiles(width*height, 0)
{
	//__build_a_basic_construct();
}

void TileLayer::resize(int new_width, int new_height, int default_value)
{
	// create a new one and fill it with the default_value
	std::vector<int> new_tiles(new_width*new_height);
	for (unsigned i=0; i<new_tiles.size(); i++)
		new_tiles[i] = default_value;

	// fill the new tiles with the old tiles (cropping if necessairy)
	int smaller_width = std::min(new_width, width);
	int smaller_height = std::min(new_height, height);
	for (int tile_y=0; tile_y<smaller_height; tile_y++)
		for (int tile_x=0; tile_x<smaller_width; tile_x++)
			new_tiles[tile_x + tile_y * smaller_width] = tiles[tile_x + tile_y * smaller_width];

	width = new_width;
	height = new_height;

	tiles = new_tiles;
}

	
void TileLayer::set_tile(int tile_x, int tile_y, int tile)
{
	tiles[tile_x + tile_y * width] = tile;
}

int TileLayer::get_tile(int tile_x, int tile_y)
{
	return tiles[tile_x + tile_y * width];
}

int TileLayer::get_tile_bc(int tile_x, int tile_y)
{
	int index = tile_x + tile_y * width;
	if (index < 0 || index >= tiles.size()) return -1;
	return tiles[index];
}

Tile *TileLayer::c_get_tile(float world_x, float world_y)
{
	if (!tile_atlas) return NULL;
	int tile_x = world_x/tile_atlas->get_tile_width();
	int tile_y = world_y/tile_atlas->get_tile_height();
	return tile_atlas->get_tile(tiles[tile_x + tile_y * width]);
}

bool TileLayer::draw()
{
	//return true;
	return draw(0, 0, width, height);
}

void TileLayer::str_dump()
{
	std::cout << std::endl;
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
			std::cout << get_tile(x, y);
		std::cout << std::endl;
	}
}

bool TileLayer::draw(int tile_left, int tile_top, int tile_right, int tile_bottom)
{
	if (!tile_atlas || width==0 || height==0) return false;

	Tile *tile = NULL;

	tile_left = std::max(tile_left, 0);
	tile_top = std::max(tile_top, 0);
	tile_right = std::min(tile_right, width-1);
	tile_bottom = std::min(tile_bottom, height-1);

	int tile_width = tile_atlas->get_tile_width();
	int tile_height = tile_atlas->get_tile_height();
	//std::cout << tile_width << "x" << tile_height << std::endl;

	tile_atlas->lock_bitmap();
	al_hold_bitmap_drawing(true);
	for (int y=tile_top; y<=tile_bottom; y++)
		for (int x=tile_left; x<=tile_right; x++)
		{
			int this_tile_index_num = get_tile(x, y);
			if (this_tile_index_num == 0 || this_tile_index_num >= (int)tile_atlas->tiles.size()) continue;
			//if (this_tile_index_num >= tile_index->tiles.size()) continue;
			
			tile = tile_atlas->get_tile(this_tile_index_num);
			if (tile && tile->bitmap) al_draw_bitmap(tile->bitmap, x*tile_width, y*tile_height, 0);
		}
	al_hold_bitmap_drawing(false);
	tile_atlas->unlock_bitmap();

	return true;
}

bool TileLayer::draw(Camera2D *camera)
{
	float inset = 0; // this number should normally be set to 0, and will thus set the clip just at the edge of the screen
							// make this a positive number (200) to watch the clipping rectangle in action

	vec2d camera_world_tl = vec2d(0+inset,0+inset);
	vec2d camera_world_tr = vec2d(camera->placement.size.x-inset,0+inset);
	vec2d camera_world_br = vec2d(camera->placement.size.x-inset,camera->placement.size.y-inset);
	vec2d camera_world_bl = vec2d(0+inset,camera->placement.size.y-inset);

	camera->translate_screen_to_world(&camera_world_tl);
	camera->translate_screen_to_world(&camera_world_tr);
	camera->translate_screen_to_world(&camera_world_br);
	camera->translate_screen_to_world(&camera_world_bl);

	// get the clipping rectangle
	float world_clip_left = std::min(std::min(camera_world_tr.x, camera_world_br.x), std::min(camera_world_tl.x, camera_world_bl.x));
	float world_clip_right = std::max(std::max(camera_world_tr.x, camera_world_br.x), std::max(camera_world_tl.x, camera_world_bl.x));
	float world_clip_top = std::min(std::min(camera_world_tr.y, camera_world_br.y), std::min(camera_world_tl.y, camera_world_bl.y));
	float world_clip_bottom = std::max(std::max(camera_world_tr.y, camera_world_br.y), std::max(camera_world_tl.y, camera_world_bl.y));

	return draw(get_tile_col(world_clip_left), get_tile_row(world_clip_top), get_tile_col(world_clip_right), get_tile_row(world_clip_bottom));
}


float TileLayer::get_left_edge(int tile_x)
{
	return tile_x * tile_atlas->get_tile_width();
}

float TileLayer::get_top_edge(int tile_y)
{
	return tile_y * tile_atlas->get_tile_height();
}

float TileLayer::get_right_edge(int tile_x)
{
	return tile_x * tile_atlas->get_tile_width() + tile_atlas->get_tile_width();
}

float TileLayer::get_bottom_edge(int tile_y)
{
	return tile_y * tile_atlas->get_tile_height() + tile_atlas->get_tile_height();
}

float TileLayer::get_center(int tile_x)
{
	return tile_x * tile_atlas->get_tile_width() + tile_atlas->get_tile_width() * 0.5;
}

float TileLayer::get_middle(int tile_y)
{
	return tile_y * tile_atlas->get_tile_height() + tile_atlas->get_tile_height() * 0.5;
}


int TileLayer::get_tile_col(float world_x)
{
	return limit<int>(0, width-1, (int)(world_x / tile_atlas->get_tile_width()));
}

int TileLayer::get_tile_row(float world_y)
{
	return limit<int>(0, height-1, (int)(world_y / tile_atlas->get_tile_height()));
}

void TileLayer::__build_a_basic_construct() {}



