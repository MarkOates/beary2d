#pragma once




#include <vector>




class TileMap;
class Object;
class int2;

class TileMapCollisionHelper
{
public:
   static void update_with_world(TileMap &map, Object& obj);
   static bool ajacent_to_bottom_edge(TileMap &map, Object &obj);
	static std::vector<int2> get_next_collided_tile_coords(float x, float y, float velocity, float depth_of_body, float length_of_edge);
};




