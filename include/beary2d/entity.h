#ifndef __BEARY2D_NEW_ENTITY_HEADER
#define __BEARY2D_NEW_ENTITY_HEADER



#include <allegro_flare/placement2d.h>
#include <allegro_flare/vec2d.h>
#include <allegro5/allegro.h>

#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/bit_flags.h>

#include <cstdint>


class Map;

class Entity
{
protected:

public:
	static BitmapBin *bitmap_bin;

	int type;
	Map *map;

	ALLEGRO_BITMAP *bitmap;
	placement2d place;
	vec2d velocity;

	BitFlags<uint64_t> flags;
	//bool anti_gravity;
	//bool on_ground, on_ladder, in_water; // hmm not sure, this should be an entity-specific type?
										 // either that, or it should be like a generic bitmask
										 // and the user defines the masks

	Entity(Map *map, int type, float x, float y, ALLEGRO_BITMAP *bitmap);
	Entity(Map *map, int type, float x, float y, float w, float h);
	
	void set_bitmap(ALLEGRO_BITMAP *bitmap, bool fit=false);

	void align_feet();
	void align_center();

	void draw_box();
	virtual void draw();
	void draw_sprite();
	virtual void update_place_with_velocity(); // used to be update_velocity()

	virtual void move_horizontal(float unit_val);
	virtual void move_vertical(float unit_val);
	virtual void stop_moving();
	virtual void activate_skill(std::string skill_str);

	// positions

	float get_bottom() const;
	float get_right() const;
	float get_left() const;
	float get_top() const;
	float get_center() const;
	float get_middle() const;

	float get_next_top() const;
	float get_next_right() const;
	float get_next_bottom() const;
	float get_next_left() const;
	float get_next_center() const;
	float get_next_middle() const;

	void set_bottom(float val);
	void set_right(float val);
	void set_left(float val);
	void set_top(float val);
	void set_center(float val);
	void set_middle(float val);

	void move_to(Map *map, float x, float y);

	// callback on collision

	virtual void on_collide_top();
	virtual void on_collide_left();
	virtual void on_collide_bottom();
	virtual void on_collide_right();

	bool collides(float x, float y);
	bool collides_with_others_center(Entity *other);
	bool collides_full(Entity *other); // collides with the other bounding rectangle

	// useful

	std::string get_world_position_str() const;
	vec2d get_direction_of_rotation(float magnitude=1.0);
};





#endif

