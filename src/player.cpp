

#include <beary2d/player.h>

#include <allegro_flare/allegro_flare.h>


#include <beary2d/globals.h>

#include <beary2d/entity.h>



Player::Player(Display *display, Inventory *inventory, Entity *controlling_entity)
	: Screen(display)
	, inventory(inventory)
	, controlling_entity(controlling_entity)
{}


void Player::primary_timer_func()
{
	if (!controlling_entity) return;



	float joy_sensitivity = 20;

	ALLEGRO_JOYSTICK *joystick = af::joystick;//al_get_joystick(0);
	if (joystick)
	{
		ALLEGRO_JOYSTICK_STATE joystick_state;
		al_get_joystick_state(joystick, &joystick_state);

		// ghetto change control state for jetpack
		if (inventory && inventory->has_item(1)) // ITEM_JETPACK
		{
			controlling_entity->flags.set(0x08);// = true; ENTITY_STATE_ANTI_GRAVITY = 0x08
			float x_val = 0;
			float y_val = 0;
			if (fabs(joystick_state.stick[0].axis[0]) > 0.05) x_val = joystick_state.stick[0].axis[0];
			if (fabs(joystick_state.stick[0].axis[1]) > 0.05) y_val = joystick_state.stick[0].axis[1];

			vec2d vec(x_val, y_val);
			if (fabs(x_val) > 0.01 || fabs(y_val) > 0.01)
			{
				float angle = vec.get_angle();
				float mag = std::min(1.0f, vec.get_magnitude()) * 0.8;
				vec = vec2d::PolarCoords(angle, mag);
				//vec = vec.Normalized();
			}
			controlling_entity->move_horizontal(vec.x);
			controlling_entity->move_vertical(vec.y);
		}
		if (controlling_entity && controlling_entity->flags.has(0x02)) //ENTITY_STATE_ON_LADDER = 0x02
		{
			float y_val = 0;
			if (fabs(joystick_state.stick[0].axis[1]) > 0.05) y_val = joystick_state.stick[0].axis[1];
			controlling_entity->move_horizontal(0);
			controlling_entity->move_vertical(y_val * 0.25);
		}
		else
		{
			if (fabs(joystick_state.stick[0].axis[0]) > 0.05) controlling_entity->move_horizontal(joystick_state.stick[0].axis[0]);
			else { controlling_entity->stop_moving(); }
		}
	}


	ALLEGRO_KEYBOARD_STATE keyboard_state;
	al_get_keyboard_state(&keyboard_state);



	// ghetto keyboard

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_RIGHT)) controlling_entity->move_horizontal(1);
	else if (al_key_down(&keyboard_state, ALLEGRO_KEY_LEFT)) controlling_entity->move_horizontal(-1);
	else if (!joystick) { controlling_entity->stop_moving(); }

}

void Player::joy_down_func()
{
	if (!controlling_entity) return;

	controlling_entity->activate_skill("jump");
}

void Player::joy_up_func()
{
	if (!controlling_entity) return;
}

void Player::key_down_func()
{
	if (!controlling_entity) return;

	if (af::current_event->keyboard.keycode == ALLEGRO_KEY_SPACE)
		controlling_entity->activate_skill("jump");
}

void Player::joy_axis_func()
{
}




void Player::control_entity(Entity *entity_to_control)
{
	controlling_entity = entity_to_control;
}

