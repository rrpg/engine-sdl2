#include "ResourceParser.hpp"
#include "SDL2_framework/TextureManager.h"
#include <iostream>

const int MAX_CHAR_RESOURCE_NAME = 32;
const int MAX_CHAR_RESOURCE_PATH = 255;

bool ResourceParser::_parseLine(const char *fileDir, const char *line) {
	bool result = true;
	char resourceName[MAX_CHAR_RESOURCE_NAME],
		resourcePath[MAX_CHAR_RESOURCE_PATH];
	std::cout << fileDir << std::endl;
	if (2 == sscanf(line, "%s %s\n", resourceName, resourcePath)) {
		std::cout << "Resource found: " << resourceName << " (" << resourcePath << ")\n";
		if (
			!TextureManager::Instance()->addTexture(
				std::string(fileDir) + "/" + resourcePath,
				resourceName
			)
		) {
			std::cout << "An error occured while loading the texture\n";
		}
	}
	else {
		std::cout << "Invalid line: \n" << line << "\n";
		result = false;
	}

	return result;
}
