


#include <beary2d/beary2d.h>

#include <cmath>



class Project : public NewWorldScreen
{
public:
   BitmapBin bitmaps;
   Motion motion;
   TileIndex tile_index;

   Project(Display *display, Player *player)
      : NewWorldScreen(display, player)
      , bitmaps("data")
      , motion()
      , tile_index()
   {
      level = new Level();
      current_map = new Map();
      level->maps.push_back(current_map);

      tile_index.load_from_atlas(bitmaps["spritesheet.png"], 21, 21, 2, 2, 1, 1);
      current_map->tile_layer = TileLayer(&tile_index, 60, 60);

      random_map_fill();
   }

   void random_map_fill()
   {
      // fill our map with random tiles
      for (unsigned x=0; x<current_map->tile_layer.width; x++)
         for (unsigned y=0; y<current_map->tile_layer.height; y++)
            current_map->tile_layer.set_tile(x, y, random_int(0, 200));
   }

   void update_reposition_camera()
   {
      static float reposition_timer = 0;
      // update the camera's scale and rotation

      // initiate motion with the camera
      reposition_timer -= 1/60.0;
      if (reposition_timer <= 0)
      {
         reposition_timer = 3;
         motion.cmove_to(&camera.placement.position.x, random_float(0, 40*21), 3, interpolator::double_slow_in_out);
         motion.cmove_to(&camera.placement.position.y, random_float(0, 20*21), 3, interpolator::double_slow_in_out);
      }

      camera.placement.scale.x = sin(al_get_time())*0.1 + 2;
      camera.placement.scale.y = camera.placement.scale.x;
      camera.placement.rotation = sin(al_get_time())*TAU * 0.03;
   }

   void primary_timer_func() override
   {
      motion.update(Framework::time_now);

      update_reposition_camera();

      NewWorldScreen::primary_timer_func();
   }
};



int main(int argc, char *argv[])
{
   Framework::initialize();
   Display *display = Framework::create_display(800*2, 600*2);

   NewWorldScreen *world_screen = new Project(display, NULL);

   Framework::run_loop();

   return 0;
}


