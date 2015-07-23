#ifndef ___BEARY2D_EDITOR_HEADER
#define ___BEARY2D_EDITOR_HEADER




#include <vector>
#include <beary2d/bscreen.h>
class Map;
class Camera;


class EditorScreen : public BScreen
{
private:
	class pattern_t
	{
	public:
		int width, height;
		std::vector<int> tiles;
		pattern_t(int width, int height, std::vector<int> tiles)
			: width(width)
			, height(height)
			, tiles(tiles)
		{}
	};
	enum tool_t
	{
		TOOL_BRUSH = 0,
		TOOL_SELECTION_BOX,
		TOOL_CAMERA_CONTROL,
		TOOL_LAST
	};
	FontBin fonts;
	bool mouse_b1_down;
	bool mouse_b2_down;
	float mouse_screen_x, mouse_screen_y;
	float mouse_world_x, mouse_world_y;
	int current_tile_col, current_tile_row;
	int current_tile_layer;
	int current_brush_tile_index;
	vec2d selection_rect_world_start, selection_rect_world_end;
	bool selection_rect_active;
	tool_t tool;
	Camera2D internal_editor_camera; // maybe should not be used?  just use the camera from the world_screen

public:
	Map *map;
	Camera *camera;
	
	EditorScreen(Display *display);
	~EditorScreen();
	void set_camera(Camera *external_cam=NULL);
	bool set_camera_to_internal_editor_camera();
	bool set_camera_to_world_screen_camera();
	bool is_using_internal_camera();
	void primary_timer_func() override;
	std::string _get_tool_name(tool_t t);
	int pick_tool(tool_t t);
	void mouse_axes_func() override;
	void _place_tile(int tile_index_num);
	void mouse_down_func() override;
	void mouse_up_func() override;
	int next_tile_brush();
	int previous_tile_brush();
	int next_tool();
	int previous_tool();
	int next_tile_layer();
	int previous_tile_layer();
	void key_char_func() override;
	void save_map(std::string filename);

	void load_map(std::string filename);
};




#endif

