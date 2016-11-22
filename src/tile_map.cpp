



#include <beary2d/tile_map.h>

#include <cmath>
#include <beary2d/globals.h>




void TileMap::resize(int w, int h)
{
   width = w;
   height = h;
   tiles.assign(width * height, 0);
}




int TileMap::get_width() { return width; }




int TileMap::get_height() { return height; }




float TileMap::get_left_edge(int tile_x) { return tile_x * 16; }




float TileMap::get_right_edge(int tile_x) { return (tile_x+1) * 16; }




float TileMap::get_top_edge(int tile_y) { return tile_y * 16; }




float TileMap::get_bottom_edge(int tile_y) { return (tile_y+1) * 16; }




bool TileMap::set_tile(int tile_x, int tile_y, int value)
{
   if (tile_x < 0) return false;
   if (tile_y < 0) return false;
   if (tile_x >= width) return false;
   if (tile_y >= height) return false;
   tiles[tile_x + tile_y*width] = value;
   return true;
}




int TileMap::get_tile(int tile_x, int tile_y)
{
   if (tile_x < 0) return 0;
   if (tile_y < 0) return 0;
   if (tile_x >= width) return 0;
   if (tile_y >= height) return 0;
   return tiles[tile_x + tile_y*width];
}




int TileMap::world_to_tile(float world_pos)
{
   return (int)(world_pos / 16);
}




int2 TileMap::world_to_tile_coords(float world_x, float world_y)
{
   int2 result((int)(world_x / 16), (int)(world_y / 16));
   return result;
}




std::vector<int2> TileMap::get_next_collided_tile_coords(float x, float y, float velocity, float depth_of_body, float length_of_edge)
   // returns the set of tile coordinates that will be collided with after the velocity is applied
{
   std::vector<int2> collided_tiles;

   if (velocity > 0) x += depth_of_body;

   int now = world_to_tile(x);
   int next = world_to_tile(x + velocity);

   if (now != next)
   {
      // new tiles have been entered
      int start_y = world_to_tile(y);
      float inset_y = fmod(y, 16.0);
      int num_tiles_along_edge = std::max(1, (int)ceil((length_of_edge + inset_y) / 16));
      collided_tiles.reserve(num_tiles_along_edge);

      // add a list of tiles to the thing
      for (int i=0; i<num_tiles_along_edge; i++)
         collided_tiles.push_back(int2(next, start_y+i));
   }

   return collided_tiles;
}




