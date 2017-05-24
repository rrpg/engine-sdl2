#ifndef __TYPES__
#define __TYPES__

#include <cstring>
#include <type_traits>
#include <functional>
#include <unordered_map>
#include <vector>

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
	int level1HP = 0;
	int level1Defence = 0;
	int level1Attack = 0;
	std::string tileset = "";
	int timePerFrame = 0;
	int spriteX = 0;
	int spriteY = 0;
};

#endif
