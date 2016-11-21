

#include <beary2d/entity.h>

#include <allegro5/allegro_primitives.h>
#include <allegro_flare/color.h>



BitmapBin *Entity::bitmap_bin = NULL;


Entity::Entity(Map *map, int type, float x, float y, ALLEGRO_BITMAP *bitmap)
	: map(map)
	, type(type)
	, bitmap(bitmap)
	, place(x, y, 16, 16)
	, velocity()
	, flags(0)
	//, anti_gravity(false)
	//, on_ground(false)
	//, on_ladder(false)
	//, in_water(false)
{
	if (!Entity::bitmap_bin) Entity::bitmap_bin = new BitmapBin("data/bitmaps");

	place.align.x = 0;
	place.align.y = 0;
	if (bitmap)
	{
		place.size.x = al_get_bitmap_width(bitmap);
		place.size.y = al_get_bitmap_height(bitmap);
	}
}

Entity::Entity(Map *map, int type, float x, float y, float w, float h)
	: map(map)
	, type(type)
	, bitmap(NULL)
	, place(x, y, w, h)
	, velocity()
	, flags(0)
	//, anti_gravity(false)
	//, on_ground(false)
	//, on_ladder(false)
	//, in_water(false)
{
	if (!Entity::bitmap_bin) Entity::bitmap_bin = new BitmapBin("data/bitmaps");

	place.align.x = 0;
	place.align.y = 0;
}

void Entity::set_bitmap(ALLEGRO_BITMAP *bitmap, bool fit)
{
	this->bitmap = bitmap;
	if (bitmap && fit)
	{
		place.size.x = al_get_bitmap_width(bitmap);
		place.size.y = al_get_bitmap_height(bitmap);
	}
}

void Entity::align_feet()
{
	place.align.x = 0.5;
	place.align.y = 1.0;
}

void Entity::align_center()
{
	place.align.x = 0.5;
	place.align.y = 0.5;
}

void Entity::draw_box()
{
	place.start_transform();
	al_draw_rectangle(0, 0, place.size.x, place.size.y, flags.has(0x01) ? color::red : color::green, 1.0); // 0x01 == on ground
	place.restore_transform();
	al_draw_filled_circle(place.position.x, place.position.y, 5, flags.has(0x02) ? color::red : color::green); // 0x02 == on ladder
}

void Entity::draw()
{
	if (bitmap) draw_sprite();
	else draw_box();
}

void Entity::draw_sprite()
{
	place.start_transform();
	if (bitmap) al_draw_bitmap(bitmap, 0, 0, ALLEGRO_FLAGS_EMPTY);
	place.restore_transform();
}

void Entity::update_place_with_velocity()
{
	place.position.x += velocity.x;
	place.position.y += velocity.y;
}

void Entity::move_horizontal(float unit_val)
{
	velocity.x = 10.0 * unit_val;
}

void Entity::move_vertical(float unit_val)
{
	velocity.y = 10.0 * unit_val;
}

void Entity::stop_moving()
{
	velocity.x = 0.0;
	velocity.y = 0.0; // this used to not be here; the function just stopped horizontal movement.
}

void Entity::activate_skill(std::string skill_str)
{
	if (flags.has(0x01) && skill_str == "jump") // hrmkay, mmmmmkay.. ;]
		// 0x01 == on_ground
	{
		velocity.y = 20.0;
		flags.unset(0x01); // take
	}
}






float Entity::get_top() const { return place.position.y-place.size.y*place.align.y; } // doesn't take scale, rotation, or anchor into account
float Entity::get_left() const { return place.position.x-place.size.x*place.align.x; }
float Entity::get_bottom() const { return get_top() + place.size.y; }
float Entity::get_right() const { return get_left() + place.size.x; }
float Entity::get_middle() const { return get_top() + place.size.y*0.5; }
float Entity::get_center() const { return get_left() + place.size.x*0.5; }


float Entity::get_next_top() const { return get_top() + velocity.y; }
float Entity::get_next_left() const { return get_left() + velocity.x; }
float Entity::get_next_bottom() const { return get_bottom() + velocity.y; }
float Entity::get_next_right() const { return get_right() + velocity.x; }
float Entity::get_next_middle() const { return get_middle() + velocity.y; }
float Entity::get_next_center() const { return get_center() + velocity.x; }


void Entity::set_top(float val) { place.position.y = -(- val + (-place.size.y) * place.align.y); }
void Entity::set_left(float val) { place.position.x = -(- val + (-place.size.x) * place.align.x); }
void Entity::set_bottom(float val) { place.position.y = -(- val + (-place.size.y) * place.align.y) - place.size.y; }
void Entity::set_right(float val) { place.position.x = -(- val + (-place.size.x) * place.align.x) - place.size.x; }
void Entity::set_middle(float val) { place.position.y = -(- val + (-place.size.y) * place.align.y) - place.size.y*0.5; }
void Entity::set_center(float val) { place.position.x = -(- val + (-place.size.x) * place.align.x) - place.size.x*0.5; }


void Entity::move_to(Map *map, float x, float y)
{
	this->map = map;
	place.position.x = x;
	place.position.y = y;
}





/*

float Entity::get_top() const { return place.y; }
float Entity::get_right() const { return place.x+place.w; }
float Entity::get_bottom() const { return place.y+place.h; }
float Entity::get_left() const { return place.x; }
float Entity::get_center() const { return place.x+place.w/2; }
float Entity::get_middle() const { return place.y+place.h/2; }


float Entity::get_next_top() const { return place.y+velocity.y; }
float Entity::get_next_right() const { return place.x+place.w+velocity.x; }
float Entity::get_next_bottom() const { return place.y+place.h+velocity.y; }
float Entity::get_next_left() const { return place.x+velocity.x; }
float Entity::get_next_center() const { return place.x+place.w/2+velocity.x; }
float Entity::get_next_middle() const { return place.y+place.h/2+velocity.y; }


void Entity::set_top(float val) { place.y = val; }
void Entity::set_left(float val) { place.x = val; }
void Entity::set_right(float val) { place.x = val-place.w; }
void Entity::set_bottom(float val) { place.y = val-place.h; }

*/






void Entity::on_collide_top()
{
	velocity.y = 0;
}

void Entity::on_collide_left()
{
	velocity.x = 0;
}

void Entity::on_collide_bottom()
{
	velocity.y = 0;
//	on_ground = true;
}

void Entity::on_collide_right()
{
	velocity.x = 0;
}






bool Entity::collides(float x, float y)
{
	if (x < get_left()) return false;
	if (x > get_right()) return false;
	if (y < get_top()) return false;
	if (y > get_bottom()) return false;
	return true;
}

bool Entity::collides_with_others_center(Entity *other)
{
	if (!other) return false;
	return collides(other->get_center(), other->get_middle());
}

bool Entity::collides_full(Entity *other)
{
	if (!other) return false;

	// (this could be optimized maybe a little)

	if (other->get_right() < get_left()) return false;
	if (other->get_left() > get_right()) return false;
	if (other->get_bottom() < get_top()) return false;
	if (other->get_top() > get_bottom()) return false;

	return true;
}





std::string Entity::get_world_position_str() const
{
	return place.position.get_string();
	//std::stringstream ss;
	//ss << "(" << place.position.x << ", " << place.position.y << ")";
	//return ss.str();
}



vec2d Entity::get_direction_of_rotation(float magnitude)
{
	return vec2d::polar_coords(place.rotation, magnitude);
}
