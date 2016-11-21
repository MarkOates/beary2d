#ifndef __BEARY2D_GLOBALS_HEADER
#define __BEARY2D_GLOBALS_HEADER




/************************************
/************************************
/************************************

basically, we're trying to get rid of needing all the stuff in here

namespace global is the namespace of shame for all the things that
should be used in a more proper manner.

*************************************
*************************************
************************************/



struct int2
{
public:
	int x = 0;
	int y = 0;
	int2(int x, int y)
		: x(x)
		, y(y)
	{}
	void rotate()
	{
		int s = x;
		x = y;
		y = s;
	}
};




//extern int SCREEN_W;
//extern int SCREEN_H;

#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>


//#include <allegro5/allegro.h>


#include <allegro_flare/screen.h>
#include <allegro_flare/bins/bitmap_bin.h>
#include <allegro_flare/bins/sample_bin.h>
#include <allegro_flare/bins/font_bin.h>
#include <allegro_flare/motion.h>



#include <allegro_flare/camera2d.h>



namespace global
{
	//class Display;
	//class WorldScreen;
	//class TitleMenuScreen;
	//class InventoryScreen;
	//class GlobalAssetsScreen;



	extern int JOY_BUTTON_A;  // these are const because switch statements require const
	extern int JOY_BUTTON_B;
	extern int JOY_BUTTON_X;
	extern int JOY_BUTTON_Y;

	extern int JOY_BUTTON_R;
	extern int JOY_BUTTON_L;

	extern int JOY_BUTTON_START;
	extern int JOY_BUTTON_SELECT;




	/*
	void initialize_master_motion_control();
	void animate_OLD(float *val, float start_time, float end_time, float start_val, float end_val, float (*interpolator_func)(float), void (*callback_func)(void *));
	void update_master_motion_control(float time_now);
	void clear_animations_on(float *val);
	*/





	class AssetsScreen : public Screen
		// this screen is not intended for display, only for a
		// global, always active motion control
	{
	public:
		Camera2D camera;
		Motion motion;
		FontBin fonts;
		BitmapBin bitmaps;
		SampleBin samples;

		AssetsScreen(Display *display);
		void primary_timer_func() override;
	};




	//extern Display *display;
	extern AssetsScreen *assets_screen;


	void play_sample(std::string sample_filename);

	ALLEGRO_BITMAP *get_bitmap(std::string filename);


	bool activate_screen(std::string screen_id_name, bool bring_to_front=false);




	class GameFonts
	{
	private:
		static GameFonts *instance;
		ALLEGRO_FONT *h2_font;
		ALLEGRO_FONT *player_lives_font;
		ALLEGRO_FONT *switch_block_font;
		GameFonts();
	public:
		static GameFonts *get_instance();
		static ALLEGRO_FONT *get_h2_font();
		static ALLEGRO_FONT *get_switch_block_font();
		static ALLEGRO_FONT *get_player_lives_font();
		static void initialize();
	};

}

//void activate_world_screen();





#endif

