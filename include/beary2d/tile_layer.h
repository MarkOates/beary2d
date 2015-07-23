#ifndef __BEARY2D_TILE_LAYER_HEADER
#define __BEARY2D_TILE_LAYER_HEADER




class TileIndex;
class Tile;
class Camera2D;
#include <vector>

class TileLayer
{
public:
	TileIndex *tile_index;
	int width, height;
	std::vector<int> tiles;
	
	TileLayer(TileIndex *tile_index, int width, int height);
	
	void resize(int new_width, int new_height, int default_value=0);
	void set_tile(int tile_x, int tile_y, int tile);
	int get_tile(int tile_x, int tile_y);
	int get_tile_bc(int tile_x, int tile_y); // does a bounds check, returns -1 if out of bounds
	Tile *c_get_tile(float world_x, float world_y);

	// note!
	// when using the draw() functions, the tile.at(0) will always be skipped.
	// this feature might be changed in future versions, one reason it's like this
	// is because Mappy doesn't zero-index or something like that.
	// Also NULL==0, so that makes sense, too.
	// on the flip side, if the user wants a blank tile... but then it would do the operation
	// of drawing a full blank tile... etc.  The way it is now may be the best option.

	bool draw();
	bool draw(int tile_left, int tile_top, int tile_right, int tile_bottom);
	bool draw(Camera2D *camera);

	void str_dump();
	virtual void __build_a_basic_construct();

	float get_left_edge(int tile_x);
	float get_top_edge(int tile_y);
	float get_right_edge(int tile_x);
	float get_bottom_edge(int tile_y);
	float get_center(int tile_x);
	float get_middle(int tile_y);

	int get_tile_col(float world_x);
	int get_tile_row(float world_y);
};





#endif

