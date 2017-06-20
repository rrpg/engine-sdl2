#ifndef __TYPES__
#define __TYPES__

#include <cstring>
#include <type_traits>
#include <functional>
#include <unordered_map>
#include <vector>

#include "dataTypes.hpp"

#define MAX_LENGTH_MAP_NAME 128
#define MAX_LENGTH_TILESET_NAME 32
#define MAX_CHAR_RESOURCE_PATH 255

struct EnumClassHash {
	template <typename T>
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};
template <typename Key>
using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

template <typename Key, typename T>
using MyUnorderedMap = std::unordered_map<Key, T, HashType<Key>>;

struct S_TileData {
	char tileset[MAX_LENGTH_TILESET_NAME];
	int width;
	int height;
	int x;
	int y;
};

struct S_TilesetMapping {
	char tileset[MAX_LENGTH_TILESET_NAME];
	char filePath[MAX_CHAR_RESOURCE_PATH];
};

struct S_ActorRaceData {
	char tileset[MAX_LENGTH_TILESET_NAME];
	int level1HP;
	int level1Defence;
	int level1Attack;
	int timePerFrame;
	int spriteX;
	int spriteY;
};

struct S_ObjectData {
	char tileset[MAX_LENGTH_TILESET_NAME];
	int spriteX;
	int spriteY;
};

struct S_MapChangeEventData {
	char mapName[MAX_LENGTH_MAP_NAME];
	int mapLevel;
};

enum E_Object {
	OBJECT_STAIR_UP,
	OBJECT_STAIR_DOWN
};

// int is the perthousand of chance of encounter
struct S_EnemyProbability {
	E_ActorRaces race;
	int probaRangeFrom;
	int probaRangeTo;
};

typedef std::pair<int, int> t_coordinates;

enum E_MapType {DEFAULT, CAVE};

#endif
