#ifndef __BEARY2D_ENTITY_MANAGER_HEADER
#define __BEARY2D_ENTITY_MANAGER_HEADER




#include <beary2d/entity.h>



class EntityManager
{
public:
	std::vector<Entity *> entities;

	std::vector<Entity *> get_all_of_type(int type);
	std::vector<Entity *> get_all_in_map_of_type(Map *map, int type);

	bool include_entity(Entity *entity);
	bool has_entity(Entity *entity);
	bool remove_entity(Entity *entity);
	bool delete_entity(Entity *entity);

	bool delete_all(); // deletes and clears the list
	void clear(); // just clears the list

	void draw_all();
	void draw_all_in_map(Map *map); // used to be draw_in_map();
	void update_all(); // revisit this
};




#endif

