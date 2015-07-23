

#include <beary2d/beary2d.h>



class Project : public NewWorldScreen
{
public:
	BitmapBin bitmaps;
	Motion motion;

	Project(Display *display, Player *player)
		: NewWorldScreen(display, player)
		, bitmaps("data")
		, motion()
	{
		level = new Level();
		current_map = new Map();
		level->maps.push_back(current_map);

		TileIndex *tile_index = new TileIndex();
		tile_index->load_from_atlas(bitmaps["spritesheet.png"], 21, 21, 2, 2, 1, 1);
		current_map->tile_layers.push_back(TileLayer(tile_index, 60, 60));

		// fill our map with random tiles
		for (unsigned x=0; x<current_map->tile_layers.back().width; x++)
			for (unsigned y=0; y<current_map->tile_layers.back().height; y++)
				current_map->tile_layers.back().set_tile(x, y, random_int(0, 200));
	}

	float reposition_timer;
	void reposition_camera()
	{
		// initiate motion with the camera
		motion.cmove_to(&camera.placement.position.x, random_float(0, 40*21), 3, interpolator::doubleSlowInOut);
		motion.cmove_to(&camera.placement.position.y, random_float(0, 20*21), 3, interpolator::doubleSlowInOut);
	}

	void primary_timer_func() override
	{
		motion.update(af::time_now);


		// update the camera's scale and rotation
		camera.placement.scale.x = sin(al_get_time())*0.1 + 2;
		camera.placement.scale.y = camera.placement.scale.x;
		camera.placement.rotation = sin(al_get_time())*TAU * 0.03;


		reposition_timer -= 1/60.0;
		if (reposition_timer <= 0)
		{
			reposition_timer = 3;
			reposition_camera();
		}

		
		NewWorldScreen::primary_timer_func();
	}
};



int main(int argc, char *argv[])
{
	af::initialize();
	Display *display = af::create_display(800, 600);

	NewWorldScreen *world_screen = new Project(display, NULL);

	af::run_loop();

	return 0;
}


