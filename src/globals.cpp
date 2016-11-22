#include <beary2d/globals.h>
#include <beary2d/bscreen.h>

//int SCREEN_W = 960; int SCREEN_H = 540; // thunderbolt
//int SCREEN_W = 1024; int SCREEN_H = 768;
//int SCREEN_W = 800; int SCREEN_H = 600;

#include <allegro_flare/bins/bitmap_bin.h>




int2::int2(int x, int y)
   : x(x)
   , y(y)
{}




void int2::rotate()
{
   int s = x;
   x = y;
   y = s;
}




namespace global
{








int JOY_BUTTON_A = 2;
int JOY_BUTTON_B = 1;
int JOY_BUTTON_X = 3;
int JOY_BUTTON_Y = 0;

int JOY_BUTTON_R = 5;
int JOY_BUTTON_L = 4;

int JOY_BUTTON_START = 9;
int JOY_BUTTON_SELECT = 8;










AssetsScreen *assets_screen;




AssetsScreen::AssetsScreen(Display *display)
	: Screen(display)
	, samples()
	, bitmaps()
	, fonts()
	, camera(0, 0, display->width(), display->height())
{
	camera.placement.scale.x = 1.0;
	camera.placement.scale.y = 1.0;
	camera.placement.align.x = 0.5;
	camera.placement.align.y = 0.5;
	camera.placement.position.x = display->width()/2;
	camera.placement.position.y = display->height()/2;
}



void AssetsScreen::primary_timer_func()
{
	motion.update(Framework::time_now);

	//update_master_motion_control(af::time_now);

	
	/*
	ALLEGRO_TRANSFORM t;
	al_identity_transform(&t);
	al_use_transform(&t);
	camera.start_transform();
	*/
}







void play_sample(std::string sample_filename)
{
	static SampleBin *samples = new SampleBin("data/samples");
	al_play_sample((*samples)[sample_filename], 1.0, 0.5, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}




ALLEGRO_BITMAP *get_bitmap(std::string filename)
{
	static BitmapBin *bitmaps = new BitmapBin();
	return (*bitmaps)[filename];
}





bool activate_screen(std::string screen_id_name, bool bring_to_front)
{
	BScreen *bscreen = BScreen::get_bscreen_by_id_name(screen_id_name);
	if (!bscreen)
	{
		std::cout << "could not active screen \"" << screen_id_name << "\"" << std::endl;
		return false;
	}
	
	// deactivate all but the selected one

	for (auto it=BScreen::bscreens.begin(); it!=BScreen::bscreens.end(); it++)
	{
		if ((*it) == bscreen) continue;

		(*it)->updating = false;
		(*it)->input_active = false;
		(*it)->drawing = false;
		(*it)->on_switch_out();
	}

	// activate the bscreen

	bscreen->updating = true;
	bscreen->input_active = true;
	bscreen->drawing = true;
	bscreen->on_switch_in();

	if (bring_to_front) Screen::bring_to_front(bscreen);

	return true;
}












GameFonts::GameFonts() : h2_font(NULL), switch_block_font(NULL)
{}


GameFonts *GameFonts::get_instance()
{
	if (!instance) instance = new GameFonts;
	return instance;
}

ALLEGRO_FONT *GameFonts::get_h2_font()
{
	return get_instance()->h2_font;
}

ALLEGRO_FONT *GameFonts::get_switch_block_font()
{
	return get_instance()->switch_block_font;
}

ALLEGRO_FONT *GameFonts::get_player_lives_font()
{
	return get_instance()->player_lives_font;
}

void GameFonts::initialize()
{
	get_instance()->h2_font = al_load_font("data/fonts/ARNORG_.TTF", -50, 0);
	get_instance()->switch_block_font = al_load_font("data/fonts/04B_03B_.TTF", -24, 0);
	get_instance()->player_lives_font = al_load_font("data/fonts/ARNORG_.TTF", -36, 0);
}

GameFonts *GameFonts::instance = NULL;











/*
static std::vector<MotionControl *> motion_control;
static int last_index = 0;
static unsigned num_reserved = 100;



static int get_new_index()
{
	last_index++;
	last_index = last_index % num_reserved;
	return last_index;
}



void animate_OLD(float *val, float start_time, float end_time, float start_val, float end_val, float (*interpolator_func)(float), void (*callback_func)(void *))
{
	int new_index = get_new_index();
	motion_control[new_index]->clear();
	//motion_control[new_index]->set(val, start_time, end_time, start_val, end_val, interpolator_func, callback_func, NULL);
	motion_control[new_index]->set(val, start_time, end_time, start_val, end_val, interpolator_func, callback_func, NULL);
}



void clear_animations_on(float *val)
{
	for (unsigned i=0; i<num_reserved; i++)
		if (motion_control[i]->val == val) motion_control[i]->clear();
}



void update_master_motion_control(float time_now)
{
	for (unsigned i=0; i<num_reserved; i++)
		motion_control[i]->update(time_now);
}



void initialize_master_motion_control()
{
	for (unsigned i=0; i<num_reserved; i++)
		motion_control.push_back(new MotionControl());
}
*/













}
