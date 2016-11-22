



#include <beary2d/tile_map_collision_helper.h>

#include <cmath>
#include <beary2d/object.h>
#include <beary2d/tile_map.h>
#include <beary2d/tile_map_collision_helper.h>




void TileMapCollisionHelper::update_with_world(TileMap &map, Object& obj)
{
   // test horizontal first
   std::vector<int2> horizontal_collided_blocks = map.get_next_collided_tile_coords(obj.x, obj.y, obj.velocity_x, obj.w, obj.h);
   if (!horizontal_collided_blocks.empty())
   {
      for (int2 &t : horizontal_collided_blocks)
      {
         if (map.get_tile(t.x, t.y) == 1) // tile is solid
         {
            if (obj.velocity_x > 0)
            {
               obj.set_right_edge(map.get_left_edge(t.x) - 0.0001);
               obj.velocity_x = 0.0;
            }
            else if (obj.velocity_x < 0)
            {
               obj.set_left_edge(map.get_right_edge(t.x) + 0.0001);
               obj.velocity_x = 0.0;
            }
         }
      }
   }
   obj.x += obj.velocity_x;

   // test vertical second
   std::vector<int2> vertical_collided_blocks = map.get_next_collided_tile_coords(obj.y, obj.x, obj.velocity_y, obj.h, obj.w);
   for(int2 &tile_coord : vertical_collided_blocks) tile_coord.rotate();
   if (!vertical_collided_blocks.empty())
   {
      for (int2 &t : vertical_collided_blocks)
      {
         if (map.get_tile(t.x, t.y) == 1) // tile is solid
         {
            if (obj.velocity_y > 0)
            {
               obj.set_bottom_edge(map.get_top_edge(t.y) - 0.0001);
               obj.velocity_y = 0.0;
            }
            else if (obj.velocity_y < 0)
            {
               obj.set_top_edge(map.get_bottom_edge(t.y) + 0.0001);
               obj.velocity_y = 0.0;
            }
         }
      }
   }
   obj.y += obj.velocity_y;
}




bool TileMapCollisionHelper::ajacent_to_bottom_edge(TileMap &map, Object &obj)
{
   std::vector<int2> tiles = TileMapCollisionHelper::get_next_collided_tile_coords(obj.y, obj.x, 0.0004, obj.h, obj.w);
   if (tiles.empty()) return false;

   for (auto &t : tiles)
   {
      t.rotate();
      if (map.get_tile(t.x, t.y) == 1) return true;
   }
   return false;
}




std::vector<int2> TileMapCollisionHelper::get_next_collided_tile_coords(float x, float y, float velocity, float depth_of_body, float length_of_edge)
   // returns the set of tile coordinates that will be collided with after the velocity is applied
{
   std::vector<int2> collided_tiles;

   if (velocity > 0) x += depth_of_body;

   int now = TileMap::world_to_tile(x);
   int next = TileMap::world_to_tile(x + velocity);

   if (now != next)
   {
      // new tiles have been entered
      int start_y = TileMap::world_to_tile(y);
      float inset_y = fmod(y, 16.0);
      int num_tiles_along_edge = std::max(1, (int)ceil((length_of_edge + inset_y) / 16));
      collided_tiles.reserve(num_tiles_along_edge);

      // add a list of tiles to the thing
      for (int i=0; i<num_tiles_along_edge; i++)
         collided_tiles.push_back(int2(next, start_y+i));
   }

   return collided_tiles;
}




