#ifndef __BEARY2D_PLAYER_HEADER
#define __BEARY2D_PLAYER_HEADER




#include <beary2d/inventory.h>
#include <allegro_flare/screen.h>


class Entity;

class Player : public Screen
{
public:
	Inventory *inventory;
	Entity *controlling_entity;

	Player(Display *display, Inventory *inventory, Entity *controlling_entity);

	virtual void primary_timer_func() override; // <instead of joy_axis_func.  Joy axis func only moves on_change
	void joy_down_func();
	void joy_up_func();
	void key_down_func() override;
	virtual void joy_axis_func() override;

	void control_entity(Entity *entity_to_control);
};





#endif

