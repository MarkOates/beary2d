


#include <beary2d/bscreen.h>





BScreen::BScreen(Display *display, std::string id_name)
	: Screen(display)
	, updating(false)
	, input_active(false)
	, drawing(false)
	, id_name(id_name)
{
	bscreens.push_back(this);
}



BScreen::~BScreen()
{
	for (unsigned i=0; i<bscreens.size(); i++)
		if (bscreens[i]->id_name == this->id_name)
		{
			bscreens.erase(bscreens.begin() + i);
			i--;
		}
}



void BScreen::on_switch_in() { }



void BScreen::on_switch_out() { }



BScreen *BScreen::get_bscreen_by_id_name(std::string id_name)
{
	for (unsigned i=0; i<bscreens.size(); i++)
		if (bscreens[i]->id_name == id_name) return bscreens[i];
	return NULL;
}



std::vector<BScreen *> BScreen::bscreens;

