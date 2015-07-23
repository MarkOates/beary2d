#ifndef __BEARY2D_NEW_PLAYER_INVENTORY_HEADER
#define __BEARY2D_NEW_PLAYER_INVENTORY_HEADER




#include <string>
#include <vector>

class Inventory
{
public:
	std::vector<int> items;

public:
	Inventory();

	void pickup_item(int item_type);
	bool use_item(int item_type);
	bool has_item(int item_type);
	virtual std::string get_string();
};




#endif

