
#
# Makefile for Beary2D
# ==========================
#


BEARY2D_VER=0.0.0

INCLUDE_FLAGS=-IE:/allegro-5.1.11-mingw-edgar/include -IE:/allegro_flare/include -IE:/beary2d/include



CORE_ITEMS=bscreen entity entity_manager flare globals inventory level map motion_fx ms_background player tile tile_index tile_layer tile_map tile_map_collision_helper world_screen

CORE_OBJ_FILES=$(CORE_ITEMS:%=obj/%.o)



#
# Targets
#

core: $(CORE_OBJ_FILES)
	ar rvs lib/libbeary2d-$(BEARY2D_VER)-mingw-4.8.1.a $^

$(CORE_OBJ_FILES): obj/%.o : src/%.cpp
	g++ -c -std=gnu++11 -o obj/$(notdir $@) $< $(INCLUDE_FLAGS)

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

bin/%.exe: examples/%.cpp lib/libbeary2d-$(BEARY2D_VER)-mingw-4.8.1.a
	g++ -std=gnu++11 $< -o $@ -IE:/allegro_flare/include -IE:/beary2d/include -IE:/allegro-5.1.11-mingw-edgar/include -LE:/beary2d/lib -lbeary2d-$(BEARY2D_VER)-mingw-4.8.1 -LE:/allegro_flare/lib -lallegro_flare-0.8.6-mingw-4.8.1 -LE:/allegro-5.1.11-mingw-edgar/lib -lallegro_monolith-debug.dll



