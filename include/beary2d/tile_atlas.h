#pragma once




#include <vector>
#include <allegro5/allegro.h>




class TileAtlas
{
private:
   ALLEGRO_BITMAP *atlas_bitmap;
   int tile_width, tile_height;
   std::vector<ALLEGRO_BITMAP *> tile_bitmaps;

public:
   TileAtlas();
   ~TileAtlas();

   void load(ALLEGRO_BITMAP *atlas_bitmap, int tile_width, int tile_height, int margin_x, int margin_y, int spacing_x, int spacing_y);
   bool save(std::string image_filename);

   bool draw_to_tile(int index, ALLEGRO_BITMAP *bitmap);
   ALLEGRO_BITMAP *get_tile(int index);

   int get_tile_width();
   int get_tile_height();
   int get_num_tiles();
};




