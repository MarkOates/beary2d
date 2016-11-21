#pragma once




class TileMap
{
private:
	int width = 0;
	int height = 0;
	std::vector<int> tiles;

public:
	void resize(int w, int h);

	int get_width();
	int get_height();

	float get_left_edge(int tile_x);
	float get_right_edge(int tile_x);
	float get_top_edge(int tile_y);
	float get_bottom_edge(int tile_y);

	bool set_tile(int tile_x, int tile_y, int value);

	int get_tile(int tile_x, int tile_y);

	static int world_to_tile(float world_pos);

	static int2 world_to_tile_coords(float world_x, float world_y);
};




