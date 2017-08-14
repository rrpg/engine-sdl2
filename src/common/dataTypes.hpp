#ifndef __DATA_TYPES__
#define __DATA_TYPES__

enum E_ActorRaces {RACE_HUMAN, RACE_DEMON, RACE_RAT, NB_RACES};

enum E_TerrainType {
	TERRAIN_GRASS_NORMAL,
	TERRAIN_SOIL_NORMAL,
	TERRAIN_ROCK_NORMAL
};

enum E_TerrainTile {
	// floors
	// grass normal
	TERRAIN_GRASS_NORMAL_TOPLEFT, TERRAIN_GRASS_NORMAL_TOP,
	TERRAIN_GRASS_NORMAL_TOPRIGHT, TERRAIN_GRASS_NORMAL_LEFT,
	TERRAIN_GRASS_NORMAL_CENTER, TERRAIN_GRASS_NORMAL_RIGHT,
	TERRAIN_GRASS_NORMAL_BOTTOMLEFT, TERRAIN_GRASS_NORMAL_BOTTOM,
	TERRAIN_GRASS_NORMAL_BOTTOMRIGHT,
	TERRAIN_GRASS_NORMAL_VERT_TOP, TERRAIN_GRASS_NORMAL_VERT, TERRAIN_GRASS_NORMAL_VERT_BOTTOM,
	TERRAIN_GRASS_NORMAL_SINGLE,
	TERRAIN_GRASS_NORMAL_HORIZ_LEFT, TERRAIN_GRASS_NORMAL_HORIZ, TERRAIN_GRASS_NORMAL_HORIZ_RIGHT,
	// soil normal
	TERRAIN_SOIL_NORMAL_TOPLEFT, TERRAIN_SOIL_NORMAL_TOP,
	TERRAIN_SOIL_NORMAL_TOPRIGHT, TERRAIN_SOIL_NORMAL_LEFT,
	TERRAIN_SOIL_NORMAL_CENTER, TERRAIN_SOIL_NORMAL_RIGHT,
	TERRAIN_SOIL_NORMAL_BOTTOMLEFT, TERRAIN_SOIL_NORMAL_BOTTOM,
	TERRAIN_SOIL_NORMAL_BOTTOMRIGHT,
	TERRAIN_SOIL_NORMAL_VERT_TOP, TERRAIN_SOIL_NORMAL_VERT, TERRAIN_SOIL_NORMAL_VERT_BOTTOM,
	TERRAIN_SOIL_NORMAL_SINGLE,
	TERRAIN_SOIL_NORMAL_HORIZ_LEFT, TERRAIN_SOIL_NORMAL_HORIZ, TERRAIN_SOIL_NORMAL_HORIZ_RIGHT,
	// rock normal
	TERRAIN_ROCK_NORMAL_TOPLEFT, TERRAIN_ROCK_NORMAL_TOP,
	TERRAIN_ROCK_NORMAL_TOPRIGHT, TERRAIN_ROCK_NORMAL_LEFT,
	TERRAIN_ROCK_NORMAL_CENTER, TERRAIN_ROCK_NORMAL_RIGHT,
	TERRAIN_ROCK_NORMAL_BOTTOMLEFT, TERRAIN_ROCK_NORMAL_BOTTOM,
	TERRAIN_ROCK_NORMAL_BOTTOMRIGHT,
	TERRAIN_ROCK_NORMAL_VERT_TOP, TERRAIN_ROCK_NORMAL_VERT, TERRAIN_ROCK_NORMAL_VERT_BOTTOM,
	TERRAIN_ROCK_NORMAL_SINGLE,
	TERRAIN_ROCK_NORMAL_HORIZ_LEFT, TERRAIN_ROCK_NORMAL_HORIZ, TERRAIN_ROCK_NORMAL_HORIZ_RIGHT
};

enum E_Object {
	OBJECT_STAIR_UP,
	OBJECT_STAIR_DOWN
};


#endif
