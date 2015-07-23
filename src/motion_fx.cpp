

#include <beary2d/motion_fx.h>


#include <allegro_flare/useful.h>
#include <allegro_flare/interpolators.h>





MotionFX::MotionFX(float x, float y)
	: x(x)
	, y(y)
	, finished(false)
{}


bool MotionFX::is_finished() { return finished; }


void MotionFX::start() {}


void MotionFX::update() {}


void MotionFX::draw() {}






void MotionFXManager::update()
{
	for (unsigned i=0; i<motion_fx.size(); i++)
	{
		motion_fx[i]->update();
		if (motion_fx[i]->is_finished())
		{
			delete motion_fx[i];
			motion_fx.erase(motion_fx.begin()+i);
			i--;
		}
	}
}


void MotionFXManager::draw()
{
	for (unsigned i=0; i<motion_fx.size(); i++)
		motion_fx[i]->draw();
}


void MotionFXManager::add_motion_fx(MotionFX *motion_fx)
{
	this->motion_fx.push_back(motion_fx);
}










