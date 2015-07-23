#ifndef __BEARY2D_MS_BACKGROUND_HEADER
#define __BEARY2D_MS_BACKGROUND_HEADER




#include <allegro5/allegro.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include <allegro_flare/useful.h>


class MSBackground
{
public:
	float x, y, align_x, align_y, rotation;
	int z_index;
	float scroll_x, scroll_y;
	ALLEGRO_BITMAP *bitmap;
	MSBackground()
		: x(0), y(0), align_x(0), align_y(0), rotation(0), scroll_x(0.75), scroll_y(0.75), bitmap(NULL)
	{}
	MSBackground(float x, float y, float align_x, float align_y, float rotation, float scroll_x, float scroll_y, ALLEGRO_BITMAP *bitmap)
		: x(x), y(y), align_x(align_x), align_y(align_y), rotation(rotation), scroll_x(scroll_x), scroll_y(scroll_y), bitmap(bitmap)
	{}
	void draw(float center_x, float center_y)
	{
		if (!bitmap) return;
		al_draw_scaled_rotated_bitmap(bitmap, al_get_bitmap_width(bitmap)*align_x, al_get_bitmap_height(bitmap)*align_y,
			(center_x-x)*scroll_x + x, (center_y-y)*scroll_y + y, 1, 1, rotation, ALLEGRO_FLAGS_EMPTY);
	}
	void draw_origin()
	{
		draw_crosshair(x, y);
	}
};


bool ms_background_sort_func(const MSBackground *b1, const MSBackground *b2);


class MSBackgroundManager
{
public:
	std::vector<MSBackground *> background;
	void sort()
	{
		std::sort(background.begin(), background.end(), ms_background_sort_func);
	}
	void draw(float center_x, float center_y)
	{
		for (unsigned i=0; i<background.size(); i++)
			background[i]->draw(center_x, center_y);
	}
	void add(MSBackground *background, int z_index)
	{
		this->background.push_back(background);
		background->z_index = z_index;
		sort();
	}
};





#endif

