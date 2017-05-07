#include "Utils.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "globals.hpp"
#include <sys/stat.h>

std::string Utils::getDataPath() {
	char filePath[255];
	std::string ret;

	sprintf(
		filePath,
		"%s/%s",
		getenv("HOME"),
		GAME_DATA_FOLDER
	);

	ret = filePath;
	return ret;
}

void Utils::createFolder(const char *path) {
	struct stat st;
	if (stat(path, &st) == -1) {
		if (mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
			std::cerr << "An error occured while trying to create the folder "
				<< path << "\n";
		}
	}
}
