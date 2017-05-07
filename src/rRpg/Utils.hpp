#ifndef __UTILS__
#define __UTILS__

#include <string>

class Utils {
	public:
	static std::string getDataPath();
	static void createFolder(const char *path);
};

#endif
