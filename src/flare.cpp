#include <beary2d/flare.h>
#include <allegro5/allegro_primitives.h>




FlareManager::Flare::Flare(float x, float y, float lifespan)
	: x(x), y(y), align_x(0.5), align_y(0.5), w(0), h(0), rotation(0), scale(1), opacity(1), counter(1), bitmap(NULL),
	draw_func(__default_draw), update_func(__default_update), lifespan(lifespan), blending_mode(BLENDER_NORMAL)
{ }


void FlareManager::Flare::draw()
{
	if (draw_func) draw_func(this);
}


// todo take a look at the cooperation between the update function, method, and lifespan

bool FlareManager::Flare::update()
{
	lifespan -= 0.01; // figure this out
	if (update_func) update_func(this);
	return !(lifespan < 0);
}


void FlareManager::Flare::set_bitmap(ALLEGRO_BITMAP *bitmap)
{
	this->bitmap = bitmap;
	w = al_get_bitmap_width(bitmap);
	h = al_get_bitmap_height(bitmap);
}


bool FlareManager::Flare::__default_update(Flare *flare)
{
	flare->counter -= 0.01;
	if (flare->counter < 0) return false;
	return true;
}


void FlareManager::Flare::__default_draw(Flare *flare)
{
	float inverse_counter = 1.0 - flare->counter;
	if (flare->bitmap)
	{
		if (flare->blending_mode == BLENDER_ADDITIVE)
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);

		al_draw_tinted_scaled_rotated_bitmap(flare->bitmap, al_map_rgba_f(flare->opacity,flare->opacity,flare->opacity,flare->opacity),
			al_get_bitmap_width(flare->bitmap)*flare->align_x, al_get_bitmap_height(flare->bitmap)*flare->align_y,
			flare->x, flare->y, flare->scale, flare->scale, flare->rotation, 0);

		if (flare->blending_mode == BLENDER_ADDITIVE)
			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	}
	else
	{
		al_draw_circle(flare->x, flare->y, 30*inverse_counter,
			al_map_rgba_f(flare->counter, flare->counter, flare->counter, flare->counter), 2);
	}
}






#include <iostream>

FlareManager::FlareManager()
	: motion_manager(new Motion())
{ }


void FlareManager::update(float time_now)
{
	motion_manager->update(time_now);
	for (unsigned i=0; i<flare.size(); i++)
	{
		if (!flare[i]->update())
		{
			delete flare[i];
			flare.erase(flare.begin()+i);
			i--;
		}
	}
}


void FlareManager::draw()
{
	for (unsigned i=0; i<flare.size(); i++)
		flare[i]->draw();
}


void FlareManager::add_flare(Flare *f)
{
	flare.push_back(f);
}


