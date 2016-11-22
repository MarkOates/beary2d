
#
# Makefile for Beary2D
# ==========================
#


BEARY2D_VER=0.0.0

INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -I./include

CORE_ITEMS=bscreen entity entity_manager flare globals inventory level map motion_fx ms_background object player tile tile_index tile_layer tile_map tile_map_collision_helper world_screen

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)

ALLEGRO_FLARE_DIR=/Users/markoates/Repos/allegro_flare

ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro



#
# Targets
#

core: $(CORE_OBJ_FILES)
	ar rvs lib/libbeary2d-$(BEARY2D_VER) $^

$(CORE_OBJ_FILES): obj/%.o : src/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS) -I$(ALLEGRO_FLARE_DIR)/include

clean:
	-rm obj/*.o
	-rm lib/*.a
	-rm bin/*.exe

all: core examples


#
# Example Programs
# ==========================
#


EXAMPLES=$(wildcard examples/*.cpp)
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%.exe)

examples: $(EXAMPLE_OBJS)

bin/%.exe: examples/%.cpp lib/libbeary2d-$(BEARY2D_VER)
	g++ -std=gnu++11 $< -o $@ -IE:/allegro_flare/include -I./include -IE:/allegro-5.1.11-mingw-edgar/include -LE:/beary2d/lib -lbeary2d-$(BEARY2D_VER) -LE:/allegro_flare/lib -lallegro_flare-0.8.6-mingw-4.8.1 -LE:/allegro-5.1.11-mingw-edgar/lib $(ALLEGRO_LIBS)



