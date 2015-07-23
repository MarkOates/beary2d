

#include <beary2d/inventory.h>
#include <sstream>


Inventory::Inventory()
	: items()
{}

void Inventory::pickup_item(int item_type)
{
	items.push_back(item_type);
}

bool Inventory::use_item(int item_type)
{
	for (unsigned i=0; i<items.size(); i++)
	{
		if (items[i] == item_type)
		{
			items.erase(items.begin() + i);
			return true;
		}
	}
	return false;
}

bool Inventory::has_item(int item_type)
{
	for (unsigned i=0; i<items.size(); i++)
	{
		if (items[i] == item_type) return true;
	}
	return false;
}

std::string Inventory::get_string()
{
	std::stringstream ss;
	for (unsigned i=0; i<items.size(); i++)
	{
		ss << items[i] << " ";
	}
	return ss.str();
}


