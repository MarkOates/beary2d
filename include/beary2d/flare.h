#ifndef __BEARY2D_FLAIR_HEADER
#define __BEARY2D_FLAIR_HEADER


#include <allegro5/allegro.h>
#include <vector>
#include <allegro_flare/motion.h>


#include <allegro_flare/blender.h>



class FlareManager
{
public:
	class Flare
	{
	public:
		ALLEGRO_BITMAP *bitmap;
		float lifespan;
		float x, y, w, h, align_x, align_y, scale, rotation, opacity;
		blender_t blending_mode;
		void (*draw_func)(Flare *);
		bool (*update_func)(Flare *);
		float counter;

		Flare(float x, float y, float lifespan);
		void set_bitmap(ALLEGRO_BITMAP *bitmap);
		void draw();
		bool update();
		static bool __default_update(Flare *flare);
		static void __default_draw(Flare *flare);
	};

	Motion *motion_manager;
	std::vector<Flare *> flare;

	FlareManager();
	void update(float time_now);
	void draw();
	void add_flare(Flare *f);
};




#endif

