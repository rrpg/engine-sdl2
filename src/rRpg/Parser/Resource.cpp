#include "Resource.hpp"
#include "SDL2_framework/TextureManager.h"
#include <iostream>

bool ResourceParser::_parseLine(const char *line) {
	bool result = true;
	char resourceName[MAX_CHAR_RESOURCE_NAME],
		resourcePath[MAX_CHAR_RESOURCE_PATH];
	if (2 == sscanf(line, "%s %s\n", resourceName, resourcePath)) {
		std::cout << "Resource found: " << resourceName << " (" << resourcePath << ")\n";
		if (
			!TextureManager::Instance()->addTexture(
				std::string(m_sFileDir) + "/" + resourcePath,
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
