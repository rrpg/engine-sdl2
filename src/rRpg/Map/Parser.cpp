#include "Map.hpp"
#include "Utils.hpp"
#include "Map/Parser.hpp"
#include <string.h>
#include <libgen.h>

MapParser::MapParser(Map &map) : m_map(map) {
}

MapParser::~MapParser() {
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
		case 'n':
			char mapName[128];
			sscanfResult = sscanf(line, "%s\n", mapName);
			if (sscanfResult != 1) {
				retValue = false;
			}
			m_map.setName(mapName);
			break;
		case 'l':
			int mapLevel;
			sscanfResult = sscanf(line, "%d\n", &mapLevel);
			if (sscanfResult != 1) {
				retValue = false;
			}
			m_map.setLevel(mapLevel);
			break;
		case 't':
			int mapType;
			sscanfResult = sscanf(line, "%d\n", &mapType);
			if (sscanfResult != 1) {
				retValue = false;
			}
			m_map.setType((E_MapType) mapType);
			break;
		case 'd':
			int w, h;
			sscanfResult = sscanf(line, "%d %d\n", &w, &h);
			if (sscanfResult != 2) {
				retValue = false;
			}
			m_map.setDimensions(w, h);
			break;
		case 'c':
			_parseMapContent(line);
			break;

		case 'E':
			int xEvent, yEvent;
			sscanfResult = sscanf(
				line,
				"%d %d \n",
				&xEvent, &yEvent
			);
			if (sscanfResult != 2) {
				retValue = false;
			}
			else {
				S_MapChangeEventData event;
				strncpy(event.mapName, m_map.getName().c_str(), MAX_LENGTH_MAP_NAME);
				event.mapLevel = m_map.getLevel() + 1;
				m_map.addEvent((char) xEvent, (char) yEvent, event);
			}
			break;

		case 'e':
			int xEnemy, yEnemy;
			sscanfResult = sscanf(
				line,
				"%d %d\n",
				&xEnemy, &yEnemy
			);
			if (sscanfResult != 2) {
				retValue = false;
			}
			else {
				m_map.addEnemySpawnableCell((char) xEnemy, (char) yEnemy);
			}
			break;

		case 'o':
			int xObject, yObject, objectType;
			sscanfResult = sscanf(
				line,
				"%d %d %d\n",
				&xObject, &yObject, &objectType
			);
			if (sscanfResult != 3) {
				retValue = false;
			}
			else {
				m_map.addObject(xObject, yObject, (E_Object) objectType);
			}
			break;

		case 'g':
			int tileWidth, tileHeight;
			sscanfResult = sscanf(
				line,
				"%d %d\n",
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
		short cellTile = *line;
		m_map.getGrid()->push_back((E_TerrainType) cellTile);
		++line;
	}
}

bool MapParser::saveMap(const char *filePath) {
	Utils::createFolder(dirname(strdup(filePath)));
	FILE *mapFile = fopen(filePath, "w");
	if (mapFile == NULL) {
		return false;
	}

	fprintf(mapFile, "n %s\n", m_map.getName().c_str());
	fprintf(mapFile, "l %d\n", m_map.getLevel());
	fprintf(mapFile, "t %d\n", m_map.getType());

	fprintf(
		mapFile,
		"d %d %d\ng %d %d\ns %d %d\n",
		m_map.getWidth(), m_map.getHeight(),
		m_map.getDisplayTileWidth(), m_map.getDisplayTileHeight(),
		(int) m_map.getStartPoint().getX(), (int) m_map.getStartPoint().getY()
	);

	for (auto enemyPlace : m_map.getEnemySpawnableCells()) {
		fprintf(mapFile, "e %d %d\n", enemyPlace.first, enemyPlace.second);
	}

	for (auto event : m_map.getEvents()) {
		t_coordinates coords = event.second.first;
		fprintf(mapFile, "E %d %d\n", coords.first, coords.second);
	}

	for (auto object : m_map.getObjects()) {
		 t_coordinates coords = object.second.first;
		fprintf(
			mapFile,
			"o %d %d %d\n",
			coords.first, coords.second, object.second.second
		);
	}

	bool newLine = true;
	int cellCount = 0;
	for (auto cell : *(m_map.getGrid())) {
		if (newLine) {
			fprintf(mapFile, "c ");
			newLine = false;
		}

		fputc(cell, mapFile);

		if (++cellCount == 100) {
			newLine = true;
			cellCount = 0;
			fprintf(mapFile, "\n");
		}
	}

	fclose(mapFile);
	return true;
}
