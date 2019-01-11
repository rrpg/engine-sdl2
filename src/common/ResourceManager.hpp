#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <fstream>
#include <map>

const long unsigned MAX_CHARS_PER_LINE = 1024;

template <class resourceType> class ResourceManager {
	private:
	std::map<int, resourceType> m_mResources = {};
	std::ifstream m_resourceFile;

	void _clean();

	public:
	ResourceManager();
	ResourceManager(const ResourceManager &r);
	~ResourceManager();
	bool setResourceFile(std::string resourceFile);
	void getResource(int index, resourceType &resource);
	std::map<int, resourceType> &getParsedResources();
	void parseBinaryFile();
	bool saveReadableFile(std::string fileOut, void (callback)(std::ofstream&, resourceType));

	/**
	 * Takes a readable file (text human created file)
	 * and saves it in a binary file.
	 */
	bool compileFile(
		std::string fileIn,
		std::string fileOut,
		bool (rowCallback)(char*, resourceType&)
	);
};

#include "ResourceManager.tpp"

#endif
