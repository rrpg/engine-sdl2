#include "Map.hpp"
#include "Resource.hpp"
#include "SDL2_framework/TextureManager.h"
#include "SDL2_framework/Game.h"
#include <string.h>

MapParser::MapParser(Map &map) : m_map(map) {
}

bool MapParser::_parseLine(const char *line) {
	bool retValue = true;
	int sscanfResult;
	char type;

	if (strlen(line) < 3) {
		return false;
	}

	type = *line;
	line += 2;
	switch (type) {
		case 'd':
			unsigned int w, h;
			sscanfResult = sscanf(line, "%u %u\n", &w, &h);
			if (sscanfResult != 2) {
				retValue = false;
			}
			m_map.setDimensions(w, h);
			break;
		case 'c':
			_parseMapContent(line);
			break;
		case 'g':
			unsigned int tileWidth, tileHeight;
			sscanfResult = sscanf(
				line,
				"%u %u\n",
				&tileWidth, &tileHeight
			);
			if (sscanfResult != 2) {
				retValue = false;
			}
			else {
				m_map.setDisplayTileDimensions(tileWidth, tileHeight);
			}
			break;

		case 's':
			int x, y;
			sscanfResult = sscanf(
				line,
				"%d %d\n",
				&x, &y
			);
			if (sscanfResult != 2) {
				retValue = false;
			}
			m_map.setStartPoint((float) x, (float) y);
			break;
		default:
			break;
	}

	return retValue;
}

void MapParser::_parseMapContent(const char *line) {
	while (*line != '\n' && *line != '\0') {
		uint32_t cellInfo = *line - '0';
		bool canSpawnEnemy = cellInfo & 0x1;
		uint8_t cellTile = (cellInfo >> 0x1) & 255;
		// the an enemy can spawn on the cell
		if (canSpawnEnemy) {
			m_map.addEnemySpawnableCell((int) m_map.getGrid()->size());
		}

		m_map.getGrid()->push_back((E_TerrainType) cellTile);
		++line;
	}
}
