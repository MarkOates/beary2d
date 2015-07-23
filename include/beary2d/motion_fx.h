#ifndef __BEARY2D_MAP_HEADER
#define __BEARY2D_MAP_HEADER




#include <vector>
#include <allegro_flare/vec2d.h>
#include <allegro_flare/blender.h>
#include <allegro5/allegro.h>




class MotionFX
{
public:
	float x, y;
	bool finished;

	MotionFX(float x, float y);

	bool is_finished();
	virtual void start();
	virtual void update();
	virtual void draw();
};




class MotionFXManager
{
public:
	std::vector<MotionFX *> motion_fx;
	void update();
	void draw();
	void add_motion_fx(MotionFX *motion_fx);
};



#endif

