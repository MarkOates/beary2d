
#include <beary2d/world_screen.h>

#include <beary2d/map.h>
#include <beary2d/player.h>
#include <beary2d/entity.h>
#include <beary2d/tile_layer.h>



NewWorldScreen::NewWorldScreen(Display *display, Player *player)
	: BScreen(display, "world_screen")
	, level(NULL)
	, camera(0, 0, display->width(), display->height())
	, current_map(NULL)
	, player(player)
	, entity_manager()
	, entity_map_move_func(NULL)
	, camera_target(NULL)
{
	//camera_target = entity_manager.entities[0];
}
	
void NewWorldScreen::render_scene()
{
	/*
	static ALLEGRO_BITMAP *background_bitmap = al_load_bitmap("data/backgrounds/magic_line.jpg");
	BitmapObject bitmap(background_bitmap);
	bitmap.stretch_to_fit(display->width(), display->height());
	bitmap.align(0, 0);
	bitmap.draw();
	*/

	al_clear_to_color(color::darkblue);

	camera.start_transform();

	if (current_map)
	{
		for (unsigned i=0; i<current_map->tile_layers.size(); i++)
		{
			//int tile_width = current_map->tile_layers[i].tile_index->get_tile_width();
			//int tile_height = current_map->tile_layers[i].tile_index->get_tile_height();
			//int left = (camera.x+camera.w/2)/tile_width - 8;
			//int top = (camera.y+camera.h/2)/tile_height - 5;
			//int right = (camera.x+camera.w/2)/tile_width + 12;
			//int bottom = (camera.y+camera.h/2)/tile_height + 7;
			//std::cout << "(" << camera.x << " " << camera.y << " " << camera.w << " " << camera.h << " - " << camera.align_x << " " << camera.align_y << " - " << camera.scale_x << " " << camera.scale_y << ")";

			//int left = (camera.x-camera.w*camera.align_x)/tile_width;
			//int top = (camera.y+camera.h/2)/tile_height;
			//int right = (camera.x+camera.w/2)/tile_width;
			//int bottom = (camera.y+camera.h/2)/tile_height;

			current_map->tile_layers[i].draw(); // for now
			// TODO: a newer version of the beary engine has clip calculations that account for zooming and rotations.
			// that will need to be updated into this part.

		}
	}
	 
	entity_manager.draw_all_in_map(current_map);

	camera.restore_transform();
}

void NewWorldScreen::update_collisions_and_positions()
{
	if (entity_map_move_func)
	{
		for (unsigned i=0; i<entity_manager.entities.size(); i++)
		{
			entity_map_move_func(entity_manager.entities[i], current_map);
		}
	}

	entity_manager.update_all();
}

void NewWorldScreen::update_scene()
{
	update_collisions_and_positions();

	if (camera_target)
	{
		camera.placement.position.x = camera_target->place.position.x - camera.placement.size.x/2 - camera_target->place.size.x;
		camera.placement.position.y = camera_target->place.position.y - camera.placement.size.y/2 - camera_target->place.size.y-100;
	}
}

void NewWorldScreen::primary_timer_func()
{
	update_scene();
	render_scene();
}

void NewWorldScreen::init_world()
{
	// eeeeeehhhh.... the content of this function is like it's a user function.  Might want to clean it up.
	camera.placement.scale.x = 1.0;
	camera.placement.scale.y = 1.0;
	camera.placement.align.x = 0;
	camera.placement.align.y = 0;

	//level.maps.push_back(Map());
	//level.tile_index.load(al_load_bitmap("data/tiles/awesome_tiles-04.png"), 64, 64, 0, 0, 0, 0);

	//current_map = &level.maps[0];

	//current_map->tile_layers.push_back(TileLayer(&level.tile_index, 18, 10));
}


