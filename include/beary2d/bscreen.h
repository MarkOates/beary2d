#ifndef ___BEARY2D_BSCREEN_HEADER
#define ___BEARY2D_BSCREEN_HEADER






#include <allegro_flare/allegro_flare.h>


class BScreen : public Screen
{
public:
	bool updating;
	bool input_active;
	bool drawing;
	std::string id_name;

	BScreen(Display *display, std::string id_name);
	~BScreen();
	virtual void on_switch_in();
	virtual void on_switch_out();

public:
	static BScreen *get_bscreen_by_id_name(std::string id_name);
	static std::vector<BScreen *> bscreens;
};






#endif

