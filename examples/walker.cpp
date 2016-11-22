



class Player : public Object
{
public:
	int health;
	Player()
		: health(3)
	{ type=0; }
};




class Item : public Object
{
public:
	Item() { type=1; }
};





class MyProject : public Screen
{
public:
	TileMap map;
	Player player;
	std::vector<Object> objects;

	std::vector<Object *> get_all_matching_type(std::vector<int> types_to_match)
	{
		std::vector<Object *> return_objects;
		for (Object &obj : objects)
		{
			if (std::find(types_to_match.begin(), types_to_match.end(), obj.type) != types_to_match.end())
				return_objects.push_back(&obj);
		}
	}

	MyProject(Display *display)
		: Screen(display)
		, map()
		, player()
		, objects()
	{
		map.resize(30, 20);
		for (int y=0; y<map.get_height(); y++)
			for (int x=0; x<map.get_width(); x++)
				map.set_tile(x, y, random_int({0, 0, 0, 1}));

		player.x = random_float(30, 120);
		player.y = random_float(30, 120);
		player.w = 8;
		player.h = 8;

		objects.reserve(6);
		for (int i=0; i<6; i++)
		{
			objects.push_back(Item());
			objects.back().x = random_float(30, 120);
			objects.back().y = random_float(30, 120);
			objects.back().w = 8;
			objects.back().h = 8;
		}
	}
	void primary_timer_func() override
	{
		//
		// update everything
		//

		//player.velocity_y += GRAVITY;
		TileMapCollisions::update_with_world(map, player);

		for (Object &obj : objects)
			TileMapCollisions::update_with_world(map, obj);

		// test for player<->object collisions
		for (int i=0; i<(int)objects.size(); i++)
		{
			TileMapCollisions::update_with_world(map, objects[i]);
			if (player.collides(objects[i]))
			{
				switch(objects[i].type)
				{
					case 0:
						break;
					case 1:
						player.health++;
						objects.erase(objects.begin()+i);
						i--;
						break;
				}
			}
		}


		//
		// draw everything
		//

		// draw the tile map
		for (int y=0; y<map.get_height(); y++)
			for (int x=0; x<map.get_width(); x++)
			{
				int t = map.get_tile(x, y);
				if (t == 1) al_draw_filled_rounded_rectangle(x*16, y*16, (x+1)*16, (y+1)*16, 4, 4, color::dodgerblue);
			}

		// draw the objects
		for (Object &obj : objects)
		{
			switch (obj.type)
			{
				case 1:
					al_draw_filled_rounded_rectangle(obj.x, obj.y, obj.x+obj.w, obj.y+obj.h, 4, 4, color::white);
					break;
			}
		}

		// draw the player
		al_draw_filled_rounded_rectangle(player.x, player.y, player.x+player.w, player.y+player.h, 4, 4, color::orange);

		// draw the hud
		al_draw_textf(af::fonts["DroidSans.ttf 16"], color::black, 5, 5, 0, "Health: %d", player.health);
	}
	void key_down_func() override
	{
		switch(af::current_event->keyboard.keycode)
		{
			case ALLEGRO_KEY_RIGHT: player.velocity_x = 2; break;
			case ALLEGRO_KEY_LEFT: player.velocity_x = -2; break;
			case ALLEGRO_KEY_UP: player.velocity_y = -2; break;
			/*
			case ALLEGRO_KEY_UP:
			{
				if (TileMapCollisions::ajacent_to_bottom_edge(map, player))
					player.velocity_y = -8;
				break;
			}
			*/
			case ALLEGRO_KEY_DOWN: player.velocity_y = 2; break;
		}
	}
	void key_up_func() override
	{
		switch(af::current_event->keyboard.keycode)
		{
			case ALLEGRO_KEY_RIGHT: player.velocity_x = 0; break;
			case ALLEGRO_KEY_LEFT: player.velocity_x = 0; break;
			case ALLEGRO_KEY_UP: player.velocity_y = 0; break;
			case ALLEGRO_KEY_DOWN: player.velocity_y = 0; break;
		}
	}
};



int main(int argc, char **argv)
{
	af::initialize();
	Display *display = af::create_display();
	MyProject project(display);
	af::run_loop();
}



