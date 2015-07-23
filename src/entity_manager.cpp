#include <beary2d/entity_manager.h>

#include <beary2d/entity.h>





bool EntityManager::include_entity(Entity *entity)
{
	if (has_entity(entity)) return false;
	entities.push_back(entity);
	return true;
}

bool EntityManager::remove_entity(Entity *entity)
{
	for (unsigned i=0; i<entities.size(); i++)
		if (entities[i] == entity)
		{
			entities.erase(entities.begin()+i);
			return true;
		}
	return false;
}

bool EntityManager::has_entity(Entity *entity)
{
	for (unsigned i=0; i<entities.size(); i++)
		if (entities[i] == entity) return true;
	return false;
}

bool EntityManager::delete_entity(Entity *entity)
{
	bool found = false;
	for (unsigned i=0; i<entities.size(); i++)
		if (entities[i] == entity)
		{
			delete entity;
			entities.erase(entities.begin() + i);
			i--;
			found = true;
		}
	return found;
}

bool EntityManager::delete_all()
{
	for (unsigned i=0; i<entities.size(); i++)
		delete entities[i];
	entities.clear();
	return true;
}

void EntityManager::clear()
{
	entities.clear();
}


void EntityManager::update_all()
{
	for(unsigned i=0; i<entities.size(); i++)
		entities[i]->update_place_with_velocity();
}



void EntityManager::draw_all()
{
	for(unsigned i=0; i<entities.size(); i++)
		entities[i]->draw();
}


void EntityManager::draw_all_in_map(Map *map)
{
	for(unsigned i=0; i<entities.size(); i++)
	{
		if (entities[i]->map == map) entities[i]->draw();
		//if (entities[i]->map == map) entities[i]->draw_box();
	}
}

std::vector<Entity *> EntityManager::get_all_of_type(int type)
{
	std::vector<Entity *> e;
	for (unsigned i=0; i<entities.size(); i++)
	{
		if (entities[i]->type == type)
			e.push_back(entities[i]);
	}
	return e;
}

std::vector<Entity *> EntityManager::get_all_in_map_of_type(Map *map, int type)
{
	std::vector<Entity *> e;
	for (unsigned i=0; i<entities.size(); i++)
	{
		if (entities[i]->map == map && entities[i]->type == type)
			e.push_back(entities[i]);
	}
	return e;
}
