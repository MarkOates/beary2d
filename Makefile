
#
# Makefile for Beary2D
# ==========================
#


BEARY2D_VER=0.0.0
BEARY2D_LIB=beary2d-$(BEARY2D_VER)

INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -I./include

CORE_ITEMS=bscreen entity entity_manager flare globals inventory level map motion_fx ms_background object player tile tile_index tile_layer tile_map tile_map_collision_helper world_screen

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)

ROOT_DIR=/Users/markoates/Repos
ALLEGRO_FLARE_DIR=$(ROOT_DIR)/allegro_flare
ALLEGRO_DIR=$(ROOT_DIR)/allegro5
ALLEGRO_FLARE_LIB=allegro_flare-0.8.8wip

ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro_main -lallegro



#
# Targets
#

core: $(CORE_OBJ_FILES)
	ar rvs lib/lib$(BEARY2D_LIB).a $^

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
EXAMPLE_OBJS=$(EXAMPLES:examples/%.cpp=bin/%$(EXE_EXTENSION))

examples: $(EXAMPLE_OBJS)

bin/main: examples/main.cpp
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I./include -I$(ALLEGRO_DIR)/include -L$(ROOT_DIR)/beary2d/lib -l$(BEARY2D_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -l$(ALLEGRO_FLARE_LIB) -L$(ALLEGRO_DIR)/build/lib $(ALLEGRO_LIBS)

bin/walker: examples/walker.cpp
	g++ -std=gnu++11 $< -o $@ -I$(ALLEGRO_FLARE_DIR)/include -I./include -I$(ALLEGRO_DIR)/include -L$(ROOT_DIR)/beary2d/lib -l$(BEARY2D_LIB) -L$(ALLEGRO_FLARE_DIR)/lib -l$(ALLEGRO_FLARE_LIB) -L$(ALLEGRO_DIR)/build/lib $(ALLEGRO_LIBS)



