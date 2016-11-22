#ifndef __BEARY2D_LEVEL_HEADER
#define __BEARY2D_LEVEL_HEADER




#include <vector>
#include <beary2d/map.h>


class Level
{
public:
	std::vector<Map *> maps;

	Level();
	void clear();
};




#endif

