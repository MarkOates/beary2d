#ifndef __BEARY2D_WORLD_SCREEN_HEADER
#define __BEARY2D_WORLD_SCREEN_HEADER




//class BScreen;

#include <beary2d/bscreen.h>
#include <beary2d/level.h>
#include <allegro_flare/camera2d.h>
class Map;
class Player;
class Entity;
#include <beary2d/entity_manager.h>


class NewWorldScreen : public BScreen
{
public:
	Level *level;
	Camera2D camera;
	Entity *camera_target;
	Map *current_map;
	Player *player;
	EntityManager entity_manager;
	void (*entity_map_move_func)(Entity *entity, Map *map);
	
	NewWorldScreen(Display *display, Player *player);
	virtual void render_scene();
	virtual void update_collisions_and_positions();
	virtual void update_scene();

	void primary_timer_func() override;

	virtual void init_world();
};





#endif

