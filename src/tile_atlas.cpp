



#include <beary2d/tile_atlas.h>

#include <allegro_flare/color.h>
#include <iostream>




TileAtlas::TileAtlas()
   : atlas_bitmap(NULL)
   , tile_width(16)
   , tile_height(16)
   , tile_bitmaps()
{}




TileAtlas::~TileAtlas()
{
   for (auto &bmp : tile_bitmaps) al_destroy_bitmap(bmp);
   if (atlas_bitmap) al_destroy_bitmap(atlas_bitmap);
}




void TileAtlas::load(ALLEGRO_BITMAP *atlas_bitmap, int tile_width, int tile_height, int margin_x, int margin_y, int tile_padding_x, int tile_padding_y)
{
   this->atlas_bitmap = al_clone_bitmap(atlas_bitmap);
   this->tile_width = tile_width;
   this->tile_height = tile_height;

   int num_rows = (al_get_bitmap_width(atlas_bitmap) - margin_x*2) / (tile_width + tile_padding_x);
   int num_cols = (al_get_bitmap_height(atlas_bitmap) - margin_y*2) / (tile_height + tile_padding_y);

   if (tile_padding_x > 0) num_rows++;
   if (tile_padding_y > 0) num_cols++;

   std::cout << "loading tileset " << num_cols << "x" << num_rows << std::endl;

   for (int row=0; row<num_rows; row++)
      for (int col=0; col<num_cols; col++)
         tile_bitmaps.push_back(al_create_sub_bitmap(atlas_bitmap,
                  margin_x + col*(tile_width) + col*(tile_padding_x*2) + tile_padding_x,
                  margin_y + row*(tile_height) + row*(tile_padding_y*2) + tile_padding_y,
                  tile_width,
                  tile_height));

   std::cout << "num tiles: " << tile_bitmaps.size() << std::endl;
}




bool TileAtlas::save(std::string image_filename)
   // exports with no padding and no margins
{
   int num_cols = 8;
   int num_rows = (tile_bitmaps.size() / num_cols);

   if (num_rows % num_cols > 0) num_rows++;

   int atlas_width = num_cols * tile_width;
   int atlas_height = num_rows * tile_height;

   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);

   ALLEGRO_BITMAP *atlas_for_export = al_create_bitmap(atlas_width, atlas_height);
   al_set_target_bitmap(atlas_for_export);
   al_clear_to_color(color::transparent);

   for (int i=0; i<(int)tile_bitmaps.size(); i++)
   {
      int row = i / num_cols;
      int col = i % num_cols;
      ALLEGRO_BITMAP *bitmap = get_tile(i);
      if (bitmap) al_draw_bitmap(bitmap, col*tile_width, row*tile_height, 0);
   }

   al_save_bitmap(image_filename.c_str(), atlas_for_export);

   al_restore_state(&previous_state);

   al_destroy_bitmap(atlas_for_export);

   return true;
}




bool TileAtlas::draw_to_tile(int index, ALLEGRO_BITMAP *bitmap)
{
   if (index < 0) return false;
   if (index >= tile_bitmaps.size()) return false;

   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(tile_bitmaps[index]);
   al_clear_to_color(color::transparent);
   al_draw_bitmap(bitmap, 0, 0, 0);

   al_restore_state(&previous_state);

   return true;
}




ALLEGRO_BITMAP *TileAtlas::get_tile(int index)
{
   if (index < 0 || index >= tile_bitmaps.size()) return nullptr;
   return tile_bitmaps[index];
}




int TileAtlas::get_tile_width()
{
   return tile_width;
}




int TileAtlas::get_tile_height()
{
   return tile_height;
}




int TileAtlas::get_num_tiles()
{
   return tile_bitmaps.size();
}




